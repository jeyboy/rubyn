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
    label -> setMinimumWidth(14);

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

void ColorPickerProperty::change(const Color::Component & new_comp, const Color::Metric & metric) {
    comp = new_comp;
    slider -> setProperty("component_id", new_comp);

    label -> setText(Color::componentName(new_comp));

    qreal new_max = Color::componentMax(new_comp, metric);

    spin -> setMaximum(new_max);
    spin -> setDecimals(metric == Color::cm_ranged ? 0 : 2);
    slider -> setMaximum(static_cast<int>(new_max * 100));
    slider -> calcBackground(true);
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
