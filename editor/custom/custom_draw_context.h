#ifndef CUSTOM_DRAW_CONTEXT_H
#define CUSTOM_DRAW_CONTEXT_H

//QTextLayout

#include <qpainter.h>
#include <qscrollbar.h>
#include <qmath.h>
#include <qhash.h>
#include <qdebug.h>

#include "misc/defines.h"
#include "custom_iblock.h"
#include "custom_visualization.h"
#include "highlighter/highlight_format_factory.h"
#include "custom_editor_searcher.h"
#include "custom_cursor.h"

namespace Custom {
    struct LineAttrs {
        QRectF rect; qint32 left_offset; qint32 width; int letter_with_pad_width; qreal pad;

        QRectF partRect(const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length) const {
            if (rect.isNull() || pos + length <= left_offset || pos >= left_offset + width)
                return QRectF();

            QRectF res(rect);

            if (pos < left_offset) {
                EDITOR_LEN_TYPE len = (pos - left_offset) + length;

                res.setLeft(res.left() - 10);
                res.setRight(res.left() + 10 + letter_with_pad_width * len);
            } else {
                res.setLeft(res.left() + (letter_with_pad_width * (pos - left_offset) - pad));

                EDITOR_LEN_TYPE len = (left_offset + width) - (pos + length);

                if (len > 0) {
                    res.setWidth(length * letter_with_pad_width);
                }
            }

            return res;
        }
    };

    struct DrawContext {
        QHash<IBlock *, LineAttrs> _on_screen;

        const LineAttrs _default_line_attrs = { QRectF(), 0, 0, 0, 0 };

        EditorSearcher * _searcher;

        QScrollBar * _vscroll;
        QScrollBar * _hscroll;

        QList<Cursor> * _cursors;
        bool _show_cursors;

        QPalette * _line_num_section_pal;
        QPalette * _content_section_pal;

        QPainter * _painter;
        QSize _screen_size;
        QFont _font;
        QFontMetricsF * _fmetrics;
        QPointF _pos;

        CharVisualization _visualization;

        qreal _cursor_width;
        qreal _letter_spacing;
        qint32 _left_padding;
        qint32 _left_margin;
        qint32 _right_margin;

        qint32 __left_str_pad;
        qint32 __max_str_length;
        qint32 __line_height;
        qreal __symbol_width;
        qreal __content_width;
        int __letter_with_pad_width;


        const LineAttrs & blockRect(IBlock * block) {
            return blockLineAttrs(block);
        }

        qint64 mouseXToCharPos(const qreal & mouse_x) {
            qreal res = (mouse_x - contentAreaRect().left());

            if (res <= 0)
                return 0;

            return qRound(res / __letter_with_pad_width);
        }

//        qint64 mouseToBlockCharPos(IBlock * block, const qint64 & char_pos) {
//            QString txt = block -> text();

//            if ()
//        }


        QRectF textRect(IBlock * block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length) {
            const LineAttrs attrs = blockRect(block);

            return attrs.partRect(pos, length);
        }

        void drawTextOverlay(const UID_TYPE & draw_uid, QPainter & painter, IBlock * block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length) {
            drawTextOverlay(draw_uid, painter, textRect(block, pos, length));
        }

        void drawTextOverlay(const UID_TYPE & draw_uid, QPainter & painter, const QRectF & fold_rect) {
            painter.save();
            painter.setCompositionMode(QPainter::CompositionMode_Multiply);
            painter.setRenderHint(QPainter::Antialiasing);

            const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(static_cast<Identifier>(draw_uid));

            painter.setPen(format.foreground().color());
            painter.setBrush(format.background().color());

            painter.drawRoundedRect(fold_rect.adjusted(1, 1, -1, -1), 3, 3);
            painter.restore();
        }


        void ensureVisibleCursorAfterMoveRight() {
            if (contentAreaRect().right() < _cursors -> operator[](0).rect().right() + __letter_with_pad_width)
                _hscroll -> setValue(_hscroll -> value() + 1);
        }

        void ensureVisibleCursorAfterMoveLeft() {
            if (contentAreaRect().left() > _cursors -> operator[](0).rect().left() - __letter_with_pad_width)
                _hscroll -> setValue(_hscroll -> value() - 1);
        }

        void ensureVisibleCursorAfterMoveUp(const bool & to_begin = false) {
            if (contentAreaRect().top() > _cursors -> operator[](0).rect().top() - __line_height)
                _vscroll -> setValue(_vscroll -> value() - 1);

            if (to_begin)
                _hscroll -> setValue(_cursors -> operator[](0).block() -> text().length() - (__max_str_length - 6));
        }

        void ensureVisibleCursorAfterMoveDown(const bool & to_begin = false) {
            if (contentAreaRect().bottom() < _cursors -> operator[](0).rect().bottom() + __line_height)
                _vscroll -> setValue(_vscroll -> value() + 1);

            if (to_begin)
                _hscroll -> setValue(0);
        }


        const LineAttrs & blockLineAttrs(IBlock * block) {
            if (!_on_screen.contains(block))
                return _default_line_attrs;

            return _on_screen[block];
        }

        void drawGrid() {
            _painter -> save();
            _painter -> setPen(Qt::red);

            for(int i = 0; i < __max_str_length; i++) {
                qreal r = i * (__symbol_width + _letter_spacing);
                _painter -> drawLine(r, 0, r, _screen_size.height());
            }
            _painter -> restore();
        }

        void drawCursors(QPainter * curr_painter) {
            if (!_show_cursors) return;

            curr_painter -> save();

            curr_painter -> setPen(Qt::black);
            curr_painter -> setBrush(Qt::black);
            QList<Cursor>::Iterator it = _cursors -> begin();

            for(; it != _cursors -> end(); it++) {
                if (!_on_screen.contains((*it).block()))
                    continue;

                const LineAttrs & attrs = _on_screen[(*it).block()];

                int left_offset =
                    attrs.rect.left() - _cursor_width + (((*it).posInBlock() - _hscroll -> value()) * __letter_with_pad_width);

                QRectF rect(left_offset, attrs.rect.top(), _cursor_width, __line_height);
                (*it).drawInRect(rect);

                curr_painter -> drawRect(rect);
            }

            curr_painter -> restore();
        }

        void draw(QPainter * curr_painter, const QSize & screen_size, IBlock * _top_block, const quint32 & top_block_number = 1) {
            prepare(curr_painter, screen_size);

            qDebug() << "-------------------------------";

            bool search_draw_requires = _searcher && _searcher -> isActive() && _searcher -> isOpened() && _searcher -> hasResults();

            IBlock * it = _top_block;
            int c = 0;
            quint32 block_num = top_block_number;

            _painter -> setPen(_content_section_pal -> color(QPalette::Foreground));
            _painter -> fillRect(numbersAreaRect(), _line_num_section_pal -> background());
            _painter -> setClipRect(contentAreaRect());

            while(it) {
                it -> draw(this);
                ++c;

                _pos.ry() += __line_height;

                _painter -> save();

                _painter -> setClipping(false);
                _painter -> setPen(_line_num_section_pal -> color(QPalette::Foreground));
                _painter -> drawText(1, qint32(_pos.y()), QString::number(++block_num));
                _painter -> setClipping(true);

                _painter -> restore();


                if (search_draw_requires) {
                    TextParts & mappings = _searcher -> searchResultsFor(it);

                    if (!mappings.isEmpty()) {
                        TextParts::Iterator index_it = mappings.begin();

                        for(; index_it != mappings.end(); index_it++) {
                            QRectF r = textRect(it, (*index_it).first, (*index_it).second);
                            drawTextOverlay(hid_search_results_overlay, *_painter, r);
                        }
                    }
                }

                if (screenCovered())
                    break;

                it = it -> next();
            }

            drawCursors(curr_painter);

            qDebug() << c;
        }

        DrawContext(QPainter * painter, const QSize & screen_size, const QFont & font, const qreal & letter_spacing = .5, const QPointF & pos = QPointF(0, 0))
            : _searcher(nullptr), _show_cursors(false), _painter(painter), _screen_size(screen_size), _fmetrics(nullptr), _pos(pos), _cursor_width(2), _letter_spacing(letter_spacing), _left_margin(0)
        {
            _visualization = CharVisualization(cv_show_space | cv_show_tab);

            setFont(font);
            setLeftPadding(1);
            setLeftMargin();
            setRightMargin();
        }

        ~DrawContext() {
            delete _line_num_section_pal;
            delete _content_section_pal;
        }

        void setSearcher(EditorSearcher * searcher) {
            _searcher = searcher;
        }

        void serCursors(QList<Cursor> * cursors) {
            _cursors = cursors;
        }

        void setScrolls(QScrollBar * hscroll, QScrollBar * vscroll) {
            _hscroll = hscroll;
            _vscroll = vscroll;
        }

        void setCursorWidth(const qreal & new_cursor_width) {
            _cursor_width = new_cursor_width;
        }

        void setPalettes(QPalette * line_num_section_pal, QPalette * content_section_pal) {
            _line_num_section_pal = line_num_section_pal;
            _content_section_pal = content_section_pal;
        }

        void prepare(QPainter * curr_painter, const QSize & screen_size) {
            _painter = curr_painter;
            _on_screen.clear();

            if (_painter) {
                _painter -> setFont(_font);
            }

            __letter_with_pad_width = qCeil(__symbol_width + _letter_spacing);

            setRightMargin(_vscroll -> isVisible() ? _vscroll -> width() + 3 : 0);
            QPointF pos = QPointF((-_hscroll -> value() * __letter_with_pad_width), 0);

            _screen_size = screen_size;
            __content_width = contentWidth();
            __max_str_length = qCeil(_screen_size.width() / __letter_with_pad_width);
            __left_str_pad = pos.x() == 0 ? 0 : qAbs(qFloor(pos.x() / __letter_with_pad_width));

            _pos = pos + QPointF(leftContentBorder() + _left_padding + (__left_str_pad * __letter_with_pad_width), 0);
        }

        bool screenCovered() {
            return _pos.y() >= _screen_size.height();
        }

        void setLeftPadding(const qint32 & padding = 0) {
            _left_padding = padding + qCeil(_cursor_width);
        }

        void setLeftMargin(const qint32 & margin = 0) {
            qDebug() << "setLeftMargin" << margin;
            _left_margin = margin;
        }

        void setRightMargin(const qint32 & margin = 0) {
            _right_margin = margin;
        }

        qreal contentWidth() {
            return _screen_size.width() - _left_padding - _left_margin - _right_margin - 2;
        }

        qint32 leftContentBorder() { return _left_padding + _left_margin + 2; }

        QRectF numbersAreaRect() {
            return QRectF(0, 0, _left_margin, _screen_size.height());
        }

        QRectF contentAreaRect() {
            return QRectF(leftContentBorder(), 0, contentWidth(), _screen_size.height() - _hscroll -> height());
        }

        qint32 verticalSingleStep() {
            return 1;//__line_height;
        }

        qint32 horizontalSingleStep() {
            return 1;//qCeil(__symbol_width);
        }

        qint32 leftStrPad() {
            return __left_str_pad;
        }

        qint32 maxStrLength() {
            return __max_str_length;
        }

        void setFont(const QFont & font) {
            _font = font;

            if (_letter_spacing > 0) {
                _font.setLetterSpacing(QFont::AbsoluteSpacing, _letter_spacing);
            }

//            QFontInfo f(font);

            _fmetrics = new QFontMetricsF(_font);

            __line_height = qCeil(_fmetrics -> height()) + 2;
            __symbol_width = _fmetrics -> averageCharWidth(); //(_fmetrics -> maxWidth() + _fmetrics -> width('!')) / 2;
        }

        qint32 calcStringWidth(const QString & str) {
            return _fmetrics -> width(str);
//            int char_num = str.length();
//            return qCeil(char_num * __symbol_width + (_letter_spacing * (char_num - 1)));
        }

        qint32 calcNumWidth(const quint64 & num) {
            return calcStringWidth(QString::number(num));
        }

        qint32 calcHScrollWidth(const quint64 & chars_amount) {
//            return qint32(_left_margin + (chars_amount * __symbol_width) + (chars_amount * _letter_spacing)) - (_screen_size.width() - _left_margin);
            return (qint32(_left_margin + (chars_amount * __symbol_width) + (chars_amount * _letter_spacing)) - (_screen_size.width() - _left_margin)) / __symbol_width;

        }

        qint32 calcVScrollWidth(const quint64 & lines_count) {
//            return qint32(lines_count * __line_height)/* - _screen_size.height()*/;
            return qint32(lines_count/* * __line_height*/)/* - _screen_size.height()*/;
        }
    };
};

#endif // CUSTOM_DRAW_CONTEXT_H
