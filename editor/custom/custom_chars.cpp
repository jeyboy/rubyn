#include "custom_chars.h"

#include <qpainter.h>

using namespace Custom;

QHash<QString, QFontMetrics *> MetricUnit::_metrics;

QImage Chars::_empty;
QHash<CharUnit, QImage> Chars::_glyphs;


//QChar::Null	0x0000	A QChar with this value isNull().
//QChar::Tabulation	0x0009	Character tabulation.
//QChar::LineFeed	0x000a
//QChar::CarriageReturn	0x000d
//QChar::Space	0x0020
//QChar::Nbsp


void Chars::drawChar(QPainter * p, DrawUnit u) {
    const QRectF rect(u.pos, u.glyph -> size());

//    u.glyph -> setColorTable(QVector<QRgb> {u.bg.rgb(), u.fg.rgb()} );
//    p -> drawImage(u.pos, *u.glyph);

    p -> setCompositionMode(QPainter::CompositionMode_Source);
    p -> drawImage(u.pos, *u.glyph);
    p -> setCompositionMode(QPainter::CompositionMode_SourceOut);
    p -> fillRect(rect, u.bg);
    p -> setCompositionMode(QPainter::CompositionMode_DestinationOver);
    p -> fillRect(rect, u.fg);


//    for (int y = 0; y < img.height(); ++y)
//    {
//        QImage img; // image with an (A)RGB image format
//        QRgb *line = reinterpret_cast<QRgb*>(img.scanLine(y));
//        for (int x = 0; x < img.width(); ++x)
//        {
//            QRgb pixelRgb = line[x];
//            // use qGreen()/qRed()/qBlue() to get value, manipulate to slider values and set it to newColor
//            QColor newColor(...);
//            line[x] = newColor.rgb();
//        }
//    }
}

QImage & Chars::glyph(const QChar & ch, const QFont & fnt) {
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
        p.setPen(Qt::white);

        p.setRenderHint(QPainter::Antialiasing, true);
        p.setRenderHint(QPainter::HighQualityAntialiasing, true);

        p.setFont(fnt);
        p.translate(0, glyph_size.height());
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
