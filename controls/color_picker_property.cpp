#include "color_picker_property.h"

#include <qlayout.h>

ColorPickerProperty::ColorPickerProperty(QWidget * parent) : QWidget(parent) {
    QHBoxLayout * l = new QHBoxLayout(this);

    label = new QLabel(this);
    l -> addWidget(label);

    slider = new QSlider(this);
    slider -> setOrientation(Qt::Horizontal);
    l -> addWidget(slider, 1);

    spin = new QSpinBox(this);
    l -> addWidget(spin);
}
