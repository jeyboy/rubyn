#ifndef CUSTOM_CHARS_H
#define CUSTOM_CHARS_H

#include "custom_visualization.h"

#include <qhash.h>
#include <qimage.h>
#include <qfontmetrics.h>

#include <qcolor.h>
#include <qrandom.h>

namespace Custom {
    struct CharUnit { QString family; int size; QChar ch; bool visualize; };

    inline bool operator==(const CharUnit & e1, const CharUnit & e2) {
        return e1.family == e2.family &&
                e1.size == e2.size &&
                e1.ch == e2.ch &&
                e1.visualize == e2.visualize;
    }

    inline uint qHash(const CharUnit & key, uint seed) {
        return qHash(key.family + key.ch + QChar(key.size), seed);
    }


    struct DrawUnit { QPointF pos; const QImage * glyph; QColor fg, bg; };

    struct MetricUnit {
        static QHash<QString, QFontMetrics *> _metrics;
        static QFontMetrics * metric(const QFont & font) {
            QString name = font.family();

            if (!_metrics.contains(name)) {
                _metrics.insert(name, new QFontMetrics(font));
            }

            return _metrics[name];
        }
    };

    class Chars {
        static QImage _empty;
        static QHash<CharUnit, QImage> _glyphs;
        static QList<QColor> _colors;
        static QRandomGenerator _ra;

    public:
        static const QColor & randomColor();
        static void drawChar(QPainter * p, const DrawUnit & u);
        static const QImage & glyph(const QChar & ch, const QFont & fnt, const CharVisualization & visualization);
//        static void drawChar(QPainter * p, const QChar & ch, const QPointF & pos, const QColor & color);
    };
}

#endif // CUSTOM_CHARS_H
