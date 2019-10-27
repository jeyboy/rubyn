#ifndef CUSTOM_DRAW_CONTEXT_H
#define CUSTOM_DRAW_CONTEXT_H

#include <qpainter.h>
#include <qmath.h>

namespace Custom {
    struct DrawContext {
        QPainter * _painter;
        QSize _screen_size;
        QFont _font;
        QFontMetricsF * _fmetrics;
        QPointF _pos;

        qreal _letter_spacing;

        qreal __line_height;
        qreal __symbol_width;
        qreal __max_str_length;

        DrawContext(QPainter * painter, const QSize & screen_size, const QFont & font, const qreal & letter_spacing = .5, const QPointF & pos = QPointF(0, 0))
            : _painter(painter), _screen_size(screen_size), _fmetrics(nullptr), _pos(pos), _letter_spacing(letter_spacing)
        {
            setFont(font);
        }

        void prepare(QPainter * curr_painter, const QSize & screen_size, const QPointF & pos) {
            _painter = curr_painter;

            _painter -> setFont(_font);

            _screen_size = screen_size;
            _pos = pos;

            __max_str_length = _screen_size.width() / __symbol_width;
        }

        bool screenCovered() {
            return _pos.y() >= _screen_size.height();
        }

        void setFont(const QFont & font) {
            _font = font;
            _font.setLetterSpacing(QFont::AbsoluteSpacing, _letter_spacing);
//            QFontInfo f(font);
            _fmetrics = new QFontMetricsF(_font);

            __line_height = _fmetrics -> height() + 2;
            __symbol_width = _fmetrics -> maxWidth();
        }

        quint32 calcStringWidth(const QString & str) {
            int char_num = str.length();
            return quint32(qCeil(char_num * __symbol_width + (_letter_spacing * (char_num - 1))));
        }

        quint32 calcNumWidth(const quint64 & num) {
            return calcStringWidth(QString::number(num));
        }
    };
};

#endif // CUSTOM_DRAW_CONTEXT_H
