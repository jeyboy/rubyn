#ifndef COLOR_PICKER_PROPERTY_H
#define COLOR_PICKER_PROPERTY_H

#include <qlabel.h>
#include <qspinbox.h>

#include "misc/color.h"

class ColorSlider;

struct ColorPickerProperty : public QWidget {
    Q_OBJECT
public:
    Color::Component comp;
    QLabel * label;
    ColorSlider * slider;
    QDoubleSpinBox * spin;

    ColorPickerProperty(QWidget * parent);

    void change(const Color::Component & new_comp, const Color::Metric & metric);
    void setVal(const qreal & new_val);
signals:
    void changed(const int & component, const qreal & new_val);

protected slots:
    void sliderValChanged(int);
    void spinValChanged(qreal);
};

#endif // COLOR_PICKER_PROPERTY_H
