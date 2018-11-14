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
        cc_a,
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
