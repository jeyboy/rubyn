#include "color_picker_property.h"

#include "color_slider.h"

#include <qlayout.h>
#include <qdebug.h>

ColorPickerProperty::ColorPickerProperty(QWidget * parent) : QWidget(parent) {
    QHBoxLayout * l = new QHBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    setContentsMargins(0, 0, 0, 0);

    label = new QLabel(this);
    QFont f = label -> font();
    f.setBold(true);
    f.setKerning(true);
    f.setPixelSize(12);
    label -> setFont(f);
    l -> addWidget(label);

    slider = new ColorSlider(this);
    l -> addWidget(slider, 1);

    spin = new QDoubleSpinBox(this);
    spin -> setDecimals(2);
    spin -> setMinimum(0);
    spin -> setFixedWidth(spin -> fontMetrics().width(QLatin1Literal("1.00")) + 25);
    l -> addWidget(spin);

    connect(spin, SIGNAL(valueChanged(qreal)), this, SLOT(spinValChanged(qreal)));
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderValChanged(int)));
}

void ColorPickerProperty::change(const ColorComponent & new_comp, const int & new_max, const bool & with_precision) {
    comp = new_comp;
    slider -> setProperty("component_id", new_comp);

    switch(comp) {
        case cc_none: { label -> setText(QLatin1Literal("None")); break;}
        case cc_a: { label -> setText(QLatin1Literal("A")); break;}
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
    slider -> setMaximum(new_max * 100);
}

void ColorPickerProperty::setVal(const qreal & new_val) {
//    slider -> setValue(new_val);
    spin -> setValue(new_val);
}

void ColorPickerProperty::sliderValChanged(int new_val) {
    spin -> blockSignals(true);
    spin -> setValue(new_val / 100.0);
    spin -> blockSignals(false);

    emit changed(comp, spin -> value());
}

void ColorPickerProperty::spinValChanged(qreal new_val) {
    slider -> blockSignals(true);
    slider -> setValue(static_cast<int>(new_val * 100));
    slider -> blockSignals(false);

    emit changed(comp, new_val);
}
