#ifndef COLOR_PICKER_PROPERTY_H
#define COLOR_PICKER_PROPERTY_H

#include <qlabel.h>
#include <qslider.h>
#include <qspinbox.h>

struct ColorPickerProperty : public QWidget {
    Q_OBJECT
public:
    enum ColorComponent : int {
        cc_none = 0,
        cc_r,
        cc_g,
        cc_b,
        cc_h,
        cc_s,
        cc_v,
        cc_l,
        cc_c,
        cc_m,
        cc_y,
        cc_k
    };

    ColorComponent comp;
    QLabel * label;
    QSlider * slider;
    QSpinBox * spin;

    ColorPickerProperty(QWidget * parent);

    void change(const ColorComponent & new_comp, const int & new_max);
signals:
    void changed(const int & component, const int & new_val);

protected slots:
    void valChanged(int);
};

#endif // COLOR_PICKER_PROPERTY_H
