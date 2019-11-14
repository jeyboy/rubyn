#include "custom_chars.h"

#include <qpainter.h>

using namespace Custom;

QHash<QString, QFontMetrics *> MetricUnit::_metrics;

QImage Chars::_empty;
QHash<CharUnit, QImage> Chars::_glyphs;

QList<QColor> Chars::_colors = {
    QColor(0, 0, 0),
    QColor(255, 0, 0),
    QColor(0, 255, 0),
    QColor(0, 0, 255)
};
QRandomGenerator Chars::_ra;

const QColor & Chars::randomColor() {
    return _colors[_ra.bounded(_colors.length() - 1)];
}

void Chars::drawChar(QPainter * p, const DrawUnit & u) {
    const QRectF rect(u.pos, u.glyph -> size());

//    if (u.bg == Qt::white && u.fg == Qt::black) {
//        p -> drawImage(u.pos, *u.glyph);
//        return;
//    }

    p -> setCompositionMode(QPainter::CompositionMode_Source);
    p -> drawImage(u.pos, *u.glyph);

    p -> setCompositionMode(QPainter::CompositionMode_SourceOut);
    p -> fillRect(rect, u.bg);

    p -> setCompositionMode(QPainter::CompositionMode_DestinationOver);
    p -> fillRect(rect, u.fg);

//    p -> setCompositionMode(QPainter::CompositionMode_Xor);


//    p -> setCompositionMode(QPainter::CompositionMode_Source);
//    p -> drawImage(u.pos, *u.glyph);

//    bool need_bg = u.bg != Qt::white;
//    bool need_fg = u.fg != Qt::black;

//    if (need_bg || need_fg) {
////        p -> save();

//        if (need_bg) {
//            p -> setCompositionMode(QPainter::CompositionMode_SourceOut);
//            p -> fillRect(rect, u.bg);
//        }

//        if (need_fg) {
//            p -> setCompositionMode(QPainter::CompositionMode_DestinationOver);
//            p -> fillRect(rect, u.fg);
//        }

////        p -> restore();
//    }
}

const  QImage & Chars::glyph(const QChar & ch, const QFont & fnt) {
    if (ch == ' ' || ch == '\t')
        return _empty;

    auto & glyph = _glyphs[{ fnt.family(), fnt.pixelSize(), ch }];

    if (glyph.isNull()) {
        QFontMetrics * fmetric = MetricUnit::metric(fnt.family());

//        QPointF extent = fmetric -> boundingRect(ch).bottomRight();
        QSize glyph_size(fmetric -> width(ch), fmetric -> height());

//        QPointF extent = m_fm.boundingRect(ch).translated(m_glyphPos).bottomRight();



        glyph = QImage(glyph_size, QImage::Format_ARGB32_Premultiplied);
        glyph.fill(Qt::transparent);

        QPainter p{&glyph};
        p.setPen(Qt::black);

        p.setRenderHint(QPainter::Antialiasing, true);
        p.setRenderHint(QPainter::HighQualityAntialiasing, true);

        p.setFont(fnt);
        p.translate(0, fmetric -> height() - fmetric -> descent());
//        p.scale(std::min(1.0, (glyph_size.width() - 1) / extent.x()),
//                std::min(1.0, (glyph_size.height() - 1) / extent.y()));

        p.drawText(QPointF{}, {ch});
    }

    return glyph;
}

//void Chars::drawChar(QPainter * p, const QChar & ch, const QPointF & pos, const QColor & color) {
////            auto & glyph = m_glyphs[ch];
////            if (glyph.isNull()) {
////                glyph = QImage{m_glyphRect.size().toSize(), QImage::Format_ARGB32_Premultiplied};
////                glyph.fill(Qt::white);
////                QPainter p{&glyph};
////                p.setCompositionMode(QPainter::CompositionMode_DestinationOut);
////                p.setFont(m_font);
////                p.drawText(m_glyphPos, {ch});
////            }
////            auto rect = m_glyphRect;
////            rect.moveTo(pos);
////            p.fillRect(rect, color);
////            p.drawImage(pos, glyph);
//}
