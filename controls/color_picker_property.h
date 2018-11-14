#ifndef COLOR_PICKER_PROPERTY_H
#define COLOR_PICKER_PROPERTY_H

#include <qlabel.h>
#include <qslider.h>
#include <qspinbox.h>

struct ColorPickerProperty : public QWidget {
    QLabel * label;
    QSlider * slider;
    QSpinBox * spin;

    ColorPickerProperty(QWidget * parent);
};

#endif // COLOR_PICKER_PROPERTY_H
