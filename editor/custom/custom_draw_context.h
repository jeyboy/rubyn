#ifndef CUSTOM_DRAW_CONTEXT_H
#define CUSTOM_DRAW_CONTEXT_H

//QTextLayout

#include <qpainter.h>
#include <qmath.h>
#include <qdebug.h>

namespace Custom {
    struct DrawContext {
        QPainter * _painter;
        QSize _screen_size;
        QFont _font;
        QFontMetricsF * _fmetrics;
        QPointF _pos;

        qreal _letter_spacing;
        qint32 _left_margin;
        qint32 _right_margin;

        qint32 __left_str_pad;
        qint32 __max_str_length;
        qint32 __line_height;
        qreal __symbol_width;

        DrawContext(QPainter * painter, const QSize & screen_size, const QFont & font, const qreal & letter_spacing = .5, const QPointF & pos = QPointF(0, 0))
            : _painter(painter), _screen_size(screen_size), _fmetrics(nullptr), _pos(pos), _letter_spacing(letter_spacing), _left_margin(0)
        {
            setFont(font);
            setLeftMargin();
            setRightMargin();
        }

        void prepare(QPainter * curr_painter, const QSize & screen_size, const QPointF & pos) {
            _painter = curr_painter;

            _painter -> setFont(_font);

            _screen_size = screen_size;

            qreal target_letter_width = __symbol_width + _letter_spacing;
            __max_str_length = qCeil(_screen_size.width() / target_letter_width);
            __left_str_pad = pos.x() == 0 ? 0 : qAbs(qFloor(pos.x() / target_letter_width));
//            if (__left_str_pad > 0)
//                __left_str_pad -= 1;

            _pos = pos + QPointF(leftContentBorder() + (__left_str_pad * target_letter_width), 0);
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
            return __line_height;
        }

        qint32 horizontalSingleStep() {
            return qCeil(__symbol_width);
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
    };
};

#endif // CUSTOM_DRAW_CONTEXT_H
