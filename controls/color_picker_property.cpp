#include "color_picker_property.h"

#include <qlayout.h>

ColorPickerProperty::ColorPickerProperty(QWidget * parent) : QWidget(parent) {
    QHBoxLayout * l = new QHBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    setContentsMargins(0, 0, 0, 0);

    label = new QLabel(this);
    l -> addWidget(label);

    slider = new QSlider(this);
    slider -> setMinimum(0);
    slider -> setMinimumWidth(50);
    slider -> setOrientation(Qt::Horizontal);
    l -> addWidget(slider, 1);

    spin = new QSpinBox(this);
    spin -> setMinimum(0);
    spin -> setFixedWidth(spin -> fontMetrics().width(QLatin1Literal("222")) + 25);
    l -> addWidget(spin);

    connect(spin, SIGNAL(valueChanged(int)), this, SLOT(valChanged(int)));
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(valChanged(int)));
}

void ColorPickerProperty::change(const ColorComponent & new_comp, const int & new_max) {
    comp = new_comp;

    switch(comp) {
        case cc_none: { label -> setText(QLatin1Literal("None")); break;}
        case cc_r: { label -> setText(QLatin1Literal("R")); break;}
        case cc_g: { label -> setText(QLatin1Literal("G")); break;}
        case cc_b: { label -> setText(QLatin1Literal("B")); break;}
        case cc_h: { label -> setText(QLatin1Literal("H")); break;}
        case cc_s: { label -> setText(QLatin1Literal("S")); break;}
        case cc_v: { label -> setText(QLatin1Literal("V")); break;}
        case cc_l: { label -> setText(QLatin1Literal("L")); break;}
        case cc_c: { label -> setText(QLatin1Literal("C")); break;}
        case cc_m: { label -> setText(QLatin1Literal("M")); break;}
        case cc_y: { label -> setText(QLatin1Literal("Y")); break;}
        case cc_k: { label -> setText(QLatin1Literal("K")); break;}

//        default: label -> setText(QLatin1Literal("Unknown"));
    };

    spin -> setMaximum(new_max);
    slider -> setMaximum(new_max);
}

void ColorPickerProperty::valChanged(int new_val) {
    if (sender() == slider) {
        spin -> blockSignals(true);
        spin -> setValue(new_val);
        spin -> blockSignals(false);
    } else {
        slider -> blockSignals(true);
        slider -> setValue(new_val);
        slider -> blockSignals(false);
    }

    emit changed(comp, new_val);
}
