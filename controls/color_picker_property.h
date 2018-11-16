#ifndef COLOR_PICKER_PROPERTY_H
#define COLOR_PICKER_PROPERTY_H

#include <qlabel.h>
#include <qspinbox.h>

#include "misc/color_component.h"

class ColorSlider;

struct ColorPickerProperty : public QWidget {
    Q_OBJECT
public:
    ColorComponent comp;
    QLabel * label;
    ColorSlider * slider;
    QDoubleSpinBox * spin;

    ColorPickerProperty(QWidget * parent);

    void change(const ColorComponent & new_comp, const int & new_max, const bool & with_precision);
    void setVal(const qreal & new_val);
signals:
    void changed(const int & component, const qreal & new_val);

protected slots:
    void sliderValChanged(int);
    void spinValChanged(qreal);
};

#endif // COLOR_PICKER_PROPERTY_H
