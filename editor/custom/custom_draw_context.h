#ifndef CUSTOM_DRAW_CONTEXT_H
#define CUSTOM_DRAW_CONTEXT_H

#include <qpainter.h>

namespace Custom {
    struct DrawContext {
        QPainter * _painter;
        QSize _screen_size;
        QFont _font;
        QFontMetricsF * _fmetrics;
        QPointF _pos;

        qreal __line_height;
        qreal __symbol_width;
        qreal __max_str_length;

        DrawContext(QPainter * painter, const QSize & screen_size, const QFont & font, const QPointF & pos = QPointF(0, 0))
            : _painter(painter), _screen_size(screen_size), _font(font), _fmetrics(nullptr), _pos(pos)
        {
            setFont(_font);
        }

        void prepare(QPainter * curr_painter, const QSize & screen_size, const QPointF & pos) {
            _painter = curr_painter;
            _screen_size = screen_size;
            _pos = pos;

            __max_str_length = _screen_size.width() / __symbol_width;
        }

        bool screenCovered() {
            return _pos.y() >= _screen_size.height();
        }

        void setFont(const QFont & font) {
//            QFontInfo f(font);
            _fmetrics = new QFontMetricsF(font);

            __line_height = _fmetrics -> height() + 2;
            __symbol_width = _fmetrics -> maxWidth();
        }
    };
};

#endif // CUSTOM_DRAW_CONTEXT_H
