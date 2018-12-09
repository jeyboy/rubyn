#include "base_item_delegate.h"

#include <qmath.h>
#include <qpainter.h>

BaseItemDelegate::BaseItemDelegate(QObject * parent) : QStyledItemDelegate(parent) {

}

QPixmap BaseItemDelegate::generateWavyPixmap(qreal max_radius, const QPen & pen) {
    QPixmap pixmap;
    QPainterPath path;

    const qreal radiusBase = qMax(qreal(1), max_radius);
    const qreal half_period = qMax(qreal(2), qreal(radiusBase * 1.61803399)); // the golden ratio
    const int width = qCeil(100 / (2 * half_period)) * (2 * half_period);
    const qreal radius = qFloor(radiusBase * 2) / 2.;
    qreal xs = 0;
    qreal ys = radius;

    while (xs < width) {
        xs += half_period;
        ys = -ys;
        path.quadTo(xs - half_period / 2, ys, xs, 0);
    }

    pixmap = QPixmap(width, radius * 2);
    pixmap.fill(Qt::transparent);

    {
        QPen wave_pen = pen;

        wave_pen.setCapStyle(Qt::SquareCap);
        // This is to protect against making the line too fat, as happens on OS X
        // due to it having a rather thick width for the regular underline.
        const qreal max_pen_width = .8 * radius;

        if (wave_pen.widthF() > max_pen_width)
            wave_pen.setWidthF(max_pen_width);

        QPainter img_painter(&pixmap);
        img_painter.setPen(wave_pen);
        img_painter.setRenderHint(QPainter::Antialiasing);
        img_painter.translate(0, radius);
        img_painter.drawPath(path);
    }

    return pixmap;
}
