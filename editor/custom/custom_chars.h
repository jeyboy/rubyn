#ifndef CUSTOM_CHARS_H
#define CUSTOM_CHARS_H

#include <qhash.h>
#include <qimage.h>
#include <qfontmetrics.h>

namespace Custom {
    struct CharUnit { QString family; int size; QChar ch; };

    inline bool operator==(const CharUnit & e1, const CharUnit & e2) {
        return e1.family == e2.family &&
                e1.size == e2.size &&
                e1.ch == e2.ch;
    }

    inline uint qHash(const CharUnit & key, uint seed) {
        return qHash(key.family + key.ch + QChar(key.size), seed);
    }


    struct DrawUnit { QPointF pos; QImage * glyph; QColor fg, bg; };

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
    public:
        static void drawChar(QPainter * p, DrawUnit u);
        static QImage & glyph(const QChar & ch, const QFont & fnt);
//        static void drawChar(QPainter * p, const QChar & ch, const QPointF & pos, const QColor & color);
    };
}

#endif // CUSTOM_CHARS_H
