#include "color_picker_property.h"

#include <qlayout.h>

ColorPickerProperty::ColorPickerProperty(QWidget * parent) : QWidget(parent) {
    QHBoxLayout * l = new QHBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    setContentsMargins(0, 0, 0, 0);

    label = new QLabel(this);
    l -> addWidget(label);

    slider = new QSlider(this);
    slider -> setMinimumWidth(30);
    slider -> setOrientation(Qt::Horizontal);
    l -> addWidget(slider, 1);

    spin = new QSpinBox(this);
    l -> addWidget(spin);
}
