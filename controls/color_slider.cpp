#include "color_slider.h"

#include <qpainter.h>
#include <qvariant.h>

#include "jslider_style.h"
#include "misc/color_component.h"

ColorSlider::ColorSlider(QWidget * parent) : QSlider(parent) {
    setMinimumWidth(80);
    setOrientation(Qt::Horizontal);

    jstyle = new JSliderStyle(style());
    setStyle(jstyle);
}

void ColorSlider::resizeEvent(QResizeEvent * e) {
    QSlider::resizeEvent(e);
    calcBackground();
}

void ColorSlider::calcBackground() {
    QPixmap p(width(), height());

    QPainter painter(&p);

    QColor c;

    int namespace_id = property("namespace_id").toInt();
    int component_id = property("component_id").toInt();

    for(int i = 0; i < width(); i++) {
        switch(component_id) {
            case
        }
    }

    jstyle -> setBackground(p);
}
