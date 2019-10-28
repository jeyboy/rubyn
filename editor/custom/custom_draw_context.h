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

        qint32 __line_height;
        qreal __symbol_width;
        qreal __max_str_length;

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
            _pos = pos + QPointF(leftContentBorder(), 0);

            __max_str_length = _screen_size.width() / __symbol_width;
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

        void setFont(const QFont & font) {
            _font = font;

            if (_letter_spacing > 0) {
                _font.setLetterSpacing(QFont::AbsoluteSpacing, _letter_spacing);
            }

//            QFontInfo f(font);

            _fmetrics = new QFontMetricsF(_font);

            __line_height = qCeil(_fmetrics -> height()) + 2;
            __symbol_width = _fmetrics -> averageCharWidth() + 1; //(_fmetrics -> maxWidth() + _fmetrics -> width('!')) / 2;
        }

        qint32 calcStringWidth(const QString & str) {
            return _fmetrics -> width(str) * 1.7;
//            int char_num = str.length();
//            return qCeil(char_num * __symbol_width + (_letter_spacing * (char_num - 1)));
        }

        qint32 calcNumWidth(const quint64 & num) {
            return calcStringWidth(QString::number(num));
        }
    };
};

#endif // CUSTOM_DRAW_CONTEXT_H
