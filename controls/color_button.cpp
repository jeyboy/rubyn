#include "color_button.h"

#include <qevent.h>
#include <qpainter.h>

ColorButton::ColorButton(QWidget * parent) : QToolButton(parent) {
    setIcon(QIcon(":/tools/transparency"));
}

void ColorButton::paintEvent(QPaintEvent * e) {
    QToolButton::paintEvent(e);

    QPainter painter(this);

    painter.setBrush(color);
    painter.drawRoundedRect(rect().adjusted(1, 1, -2, -2), 4, 4);
}
