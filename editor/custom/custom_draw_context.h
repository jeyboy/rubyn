#ifndef CUSTOM_DRAW_CONTEXT_H
#define CUSTOM_DRAW_CONTEXT_H

//QTextLayout

#include <qpainter.h>
#include <qscrollbar.h>
#include <qmath.h>
#include <qhash.h>
#include <qdebug.h>

#include "custom_iblock.h"
#include "custom_visualization.h"

namespace Custom {
    struct DrawContext {
        QHash<IBlock *, QRectF> _on_screen;

        QScrollBar * _vscroll;
        QScrollBar * _hscroll;

        QPalette * _line_num_section_pal;
        QPalette * _content_section_pal;

        QPainter * _painter;
        QSize _screen_size;
        QFont _font;
        QFontMetricsF * _fmetrics;
        QPointF _pos;

        CharVisualization _visualization;

        qreal _letter_spacing;
        qint32 _left_margin;
        qint32 _right_margin;

        qint32 __left_str_pad;
        qint32 __max_str_length;
        qint32 __line_height;
        qreal __symbol_width;
        int __letter_with_pad_width;

        void drawGrid() {
            _painter -> save();
            _painter -> setPen(Qt::red);

            for(int i = 0; i < __max_str_length; i++) {
                qreal r = i * (__symbol_width + _letter_spacing);
                _painter -> drawLine(r, 0, r, _screen_size.height());
            }
            _painter -> restore();
        }

        void draw(QPainter * curr_painter, const QSize & screen_size, IBlock * _top_block, const quint32 & top_block_number = 1) {
            prepare(curr_painter, screen_size);

            qDebug() << "-------------------------------";

            IBlock * it = _top_block;
            int c = 0;
            quint32 block_num = top_block_number;

            _painter -> setPen(_content_section_pal -> color(QPalette::Foreground));
            _painter -> fillRect(numbersAreaRect(), _line_num_section_pal -> background());
            _painter -> setClipRect(contentAreaRect());

            while(it) {
                _pos.ry() += __line_height;
                it -> draw(this);
                ++c;

                _painter -> save();

                _painter -> setClipping(false);
                _painter -> setPen(_line_num_section_pal -> color(QPalette::Foreground));
                _painter -> drawText(1, qint32(_pos.y()), QString::number(++block_num));
                _painter -> setClipping(true);

                _painter -> restore();

                if (screenCovered())
                    break;

                it = it -> next();
            }

            qDebug() << c;
        }

        DrawContext(QPainter * painter, const QSize & screen_size, const QFont & font, const qreal & letter_spacing = .5, const QPointF & pos = QPointF(0, 0))
            : _painter(painter), _screen_size(screen_size), _fmetrics(nullptr), _pos(pos), _letter_spacing(letter_spacing), _left_margin(0)
        {
            _visualization = CharVisualization(cv_show_space | cv_show_tab);

            setFont(font);
            setLeftMargin();
            setRightMargin();
        }

        ~DrawContext() {
            delete _line_num_section_pal;
            delete _content_section_pal;
        }

        void setScrolls(QScrollBar * hscroll, QScrollBar * vscroll) {
            _hscroll = hscroll;
            _vscroll = vscroll;
        }

        void setPaletes(QPalette * line_num_section_pal, QPalette * content_section_pal) {
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
            QPointF pos = QPointF(-_hscroll -> value() * __letter_with_pad_width, 0);

            _screen_size = screen_size;
            __max_str_length = qCeil(_screen_size.width() / __letter_with_pad_width);
            __left_str_pad = pos.x() == 0 ? 0 : qAbs(qFloor(pos.x() / __letter_with_pad_width));

            _pos = pos + QPointF(leftContentBorder() + (__left_str_pad * __letter_with_pad_width), 0);
        }

        bool screenCovered() {
            return _pos.y() >= _screen_size.height();
        }

        void setLeftMargin(const qint32 & margin = 0) {
            qDebug() << "setLeftMargin" << margin;
            _left_margin = margin;
        }

        void setRightMargin(const qint32 & margin = 0) {
            _right_margin = margin;
        }

        qint32 leftContentBorder() { return _left_margin + 2; }

        QRectF numbersAreaRect() {
            return QRectF(0, 0, _left_margin, _screen_size.height());
        }

        QRectF contentAreaRect() {
            return QRectF(leftContentBorder(), 0, _screen_size.width() - _left_margin - _right_margin - 2, _screen_size.height());
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
