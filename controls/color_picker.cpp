#include "color_picker.h"

#include <qlayout.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qbuttongroup.h>

#include "misc/defines.h"
#include "logger.h"
#include "color_button.h"
#include "color_picker_property.h"

ColorPicker::ColorPicker(QWidget * parent) : QWidget(parent), curr_color_item(nullptr) {
    setuplayout();
}

void ColorPicker::setColor(const QColor & color) {
    current_color = color;

    if (curr_color_item)
        curr_color_item -> setColor(current_color);

    changeColorOutputs(color);
}

void ColorPicker::setuplayout() {
    QButtonGroup * btn_group = new QButtonGroup(this);

    QGridLayout * l = new QGridLayout(this);
    QVBoxLayout * vl = new QVBoxLayout();

    l -> setContentsMargins(1, 1, 1, 1);

    QLabel * hex_label = new QLabel(QLatin1Literal("Hex"), this);
    QFont f = hex_label -> font();
    f.setBold(true);
    f.setKerning(true);
    f.setPixelSize(12);
    hex_label -> setFont(f);
    l -> addWidget(hex_label, 0, 0, Qt::AlignCenter);

    hex_name = new QComboBox(this);
    hex_name -> setEditable(true);
    hex_name -> setDuplicatesEnabled(false);
//    setValidator
    l -> addWidget(hex_name, 0, 1, 1, 3);

    connect(hex_name, SIGNAL(editTextChanged(const QString &)), this, SLOT(hexChanged(const QString &)));
    connect(hex_name, SIGNAL(currentTextChanged(const QString &)), this, SLOT(hexChanged(const QString &)));

    QComboBox * metric = new QComboBox(this);
    metric -> setEditable(false);
    metric -> addItem(QLatin1Literal("0.0-1.0"), pm_proportional);
    metric -> addItem(QLatin1Literal("0-255"), pm_ranged);
    metric -> addItem(QLatin1Literal("0-100%"), pm_percentage);
    l -> addWidget(metric, 0, 4);


    QList<QPair<ColorNamespace, QLatin1String> > names = {
        QPair<ColorNamespace, QLatin1String>(cn_rgb, QLatin1Literal("RGB")),
        QPair<ColorNamespace, QLatin1String>(cn_hsv, QLatin1Literal("HSV")),
        QPair<ColorNamespace, QLatin1String>(cn_hsl, QLatin1Literal("HSL")),
        QPair<ColorNamespace, QLatin1String>(cn_cmyk, QLatin1Literal("CMYK")),
        QPair<ColorNamespace, QLatin1String>(cn_hvb, QLatin1Literal("HVB")),
    };
    QList<QPair<ColorNamespace, QLatin1String> >::Iterator it = names.begin();

    for(int pos = 1; it != names.end(); it++, pos++) {
        QToolButton * btn = new QToolButton(this);
        btn_group -> addButton(btn, (*it).first);
        btn -> setCheckable(true);
        btn -> setFixedWidth(40);
        btn -> setText((*it).second);
        btn -> setContentsMargins(2, 2, 2, 2);
        btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        l -> addWidget(btn, pos, 0);
    }

    connect(btn_group, SIGNAL(buttonClicked(int)), this, SLOT(colorSpaceChanged(int)));

    row1 = new ColorPickerProperty(this);
    row1 -> change(ColorPickerProperty::cc_r, 1, false);
    vl -> addWidget(row1);

    row2 = new ColorPickerProperty(this);
    row2 -> change(ColorPickerProperty::cc_g, 1, false);
    vl -> addWidget(row2);

    row3 = new ColorPickerProperty(this);
    row3 -> change(ColorPickerProperty::cc_b, 1, false);
    vl -> addWidget(row3);

    row4 = new ColorPickerProperty(this);
    row4 -> change(ColorPickerProperty::cc_k, 1, false);
    vl -> addWidget(row4);
    row4 -> setVisible(false);

    l -> addLayout(vl, 1, 1, 4, 4);

    row_alpha = new ColorPickerProperty(this);
    row_alpha -> change(ColorPickerProperty::cc_a, 1, false);
    l -> addWidget(row_alpha, 5, 1, 1, 4);

    connect(row1, SIGNAL(changed(const int &, const qreal &)), this, SLOT(componentChanged(const int &, const qreal &)));
    connect(row2, SIGNAL(changed(const int &, const qreal &)), this, SLOT(componentChanged(const int &, const qreal &)));
    connect(row3, SIGNAL(changed(const int &, const qreal &)), this, SLOT(componentChanged(const int &, const qreal &)));
    connect(row4, SIGNAL(changed(const int &, const qreal &)), this, SLOT(componentChanged(const int &, const qreal &)));
    connect(row_alpha, SIGNAL(changed(const int &, const qreal &)), this, SLOT(componentChanged(const int &, const qreal &)));


//    QToolButton * down_toggle_btn = new QToolButton(this);
//    down_toggle_btn -> setFixedHeight(12);
//    down_toggle_btn -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    down_toggle_btn -> setText(QLatin1Literal("\\/"));
//    down_toggle_btn -> setStyleSheet("background-color: rgba(0,255,0, .2)");
//    l -> addWidget(down_toggle_btn, 8, 11, 1, 5);

//    down_toggle_btn -> setVisible(false);

//    QComboBox * colors_sets = new QComboBox(this);
//    QLabel * colors_set = new QLabel(this);

    //    colors_space = new QLabel(this);
    //    colors_space -> setMinimumSize(200, 200);
    //    colors_space -> setStyleSheet("background-color: rgba(255,0,0, .2)");
    //    l -> addWidget(colors_space, 0, 0, 9, 10);
    ////    colors_space -> setVisible(false);

    //    QToolButton * left_toggle_btn = new QToolButton(this);
    //    left_toggle_btn -> setFixedWidth(12);
    ////    left_toggle_btn -> setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    //    left_toggle_btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //    left_toggle_btn -> setText(QLatin1Literal("<"));
    //    left_toggle_btn -> setStyleSheet("background-color: rgba(0,255,0, .2)");
    //    l -> addWidget(left_toggle_btn, 0, 10, 9, 1);
    ////    left_toggle_btn -> setVisible(false);

    btn_group -> buttons().first() -> click();
}

void ColorPicker::changeColorOutputs(QColor color) {
    const QSignalBlocker blocker1(row1);
    const QSignalBlocker blocker2(row2);
    const QSignalBlocker blocker3(row3);
    const QSignalBlocker blocker4(row4);
    const QSignalBlocker blockera(row_alpha);
    const QSignalBlocker blocker_hex(hex_name);

    current_color = color;
    qreal a = color.alphaF();

    switch(curr_color_namespace) {
        case cn_rgb: {
            row1 -> setVal(color.redF());
            row2 -> setVal(color.greenF());
            row3 -> setVal(color.blueF());
        break;}

        case cn_hsv: {
            qreal h, s, v;

            color.getHsvF(&h, &s, &v, &a);

            row1 -> setVal(h);
            row2 -> setVal(s);
            row3 -> setVal(v);
        break;}

        case cn_hsl: {
            qreal h, s, l;

            color.getHslF(&h, &s, &l, &a);

            row1 -> setVal(h);
            row2 -> setVal(s);
            row3 -> setVal(l);
        break;}

        case cn_cmyk: {
            qreal c, m, y, k;

            color.getCmykF(&c, &m, &y, &k, &a);

            row1 -> setVal(c);
            row2 -> setVal(m);
            row3 -> setVal(y);
            row4 -> setVal(k);
        break;}

        case cn_hvb: {
            qreal h, s, v, w, b;

            color.getHsvF(&h, &s, &v, &a);

            w = (1.0 - s) * v;
            b = 1.0 - v;

            row1 -> setVal(h);
            row2 -> setVal(w);
            row3 -> setVal(b);
        break;}

        default: Logger::obj().write(QLatin1Literal("ColorPicker"), QLatin1Literal("colorSpaceChanged: unknown namespace"), Logger::log_error);
    };

    row_alpha -> setVal(a);
    hex_name -> setCurrentText(color.name(QColor::HexArgb));
}

void ColorPicker::colorPickingRequired() {

}

void ColorPicker::componentChanged(const int & component, const qreal & new_val) {
    QColor color = current_color;

    switch(component) {
        case ColorPickerProperty::cc_a: { color.setAlphaF(new_val); break;}
        case ColorPickerProperty::cc_r: { color.setRedF(new_val); break;}
        case ColorPickerProperty::cc_g: { color.setGreenF(new_val); break;}
        case ColorPickerProperty::cc_b:
        case ColorPickerProperty::cc_h:
        case ColorPickerProperty::cc_s:
        case ColorPickerProperty::cc_v:
        case ColorPickerProperty::cc_l: {
            switch(curr_color_namespace) {
                case cn_rgb: { color.setBlueF(new_val); break;}
                case cn_hsv: {
                    color.setHsvF(
                        row1 -> spin -> value(),
                        row2 -> spin -> value(),
                        row3 -> spin -> value(),
                        row_alpha -> spin -> value()
                    );
                break;}
                case cn_hsl: {
                    color.setHslF(
                        row1 -> spin -> value(),
                        row2 -> spin -> value(),
                        row3 -> spin -> value(),
                        row_alpha -> spin -> value()
                    );
                break;}
                case cn_hvb: {
                    qreal s, v;

                    hwbToHsv(row2 -> spin -> value(), row3 -> spin -> value(), s, v);

                    color.setHsvF(
                        row1 -> spin -> value(),
                        s,
                        v,
                        row_alpha -> spin -> value()
                    );
                break;}

                default:;
            }
        break;}
        case ColorPickerProperty::cc_c:
        case ColorPickerProperty::cc_m:
        case ColorPickerProperty::cc_y:
        case ColorPickerProperty::cc_k: {
            color.setCmykF(
                row1 -> spin -> value(),
                row2 -> spin -> value(),
                row3 -> spin -> value(),
                row4 -> spin -> value(),
                row_alpha -> spin -> value()
            );
        break;}

        default:;
    }

    setColor(color);
}

void ColorPicker::colorSpaceChanged(const int & new_namespace) {
    if (curr_color_namespace == new_namespace)
        return;

    switch(new_namespace) {
        case cn_rgb: {
            current_color = current_color.convertTo(QColor::Rgb);

            row1 -> change(ColorPickerProperty::cc_r, 1, true); // 255
            row2 -> change(ColorPickerProperty::cc_g, 1, true); // 255
            row3 -> change(ColorPickerProperty::cc_b, 1, true); // 255
        break;}

        case cn_hsv: {
            current_color = current_color.convertTo(QColor::Hsv);

            row1 -> change(ColorPickerProperty::cc_h, 1, true); // 359
            row2 -> change(ColorPickerProperty::cc_s, 1, true); // 255
            row3 -> change(ColorPickerProperty::cc_v, 1, true); // 255
        break;}

        case cn_hsl: {
            current_color = current_color.convertTo(QColor::Hsl);

            row1 -> change(ColorPickerProperty::cc_h, 1, true); // 359
            row2 -> change(ColorPickerProperty::cc_s, 1, true); // 255
            row3 -> change(ColorPickerProperty::cc_l, 1, true); // 255
        break;}

        case cn_cmyk: {
            current_color = current_color.convertTo(QColor::Cmyk);

            row1 -> change(ColorPickerProperty::cc_c, 1, true); // 255
            row2 -> change(ColorPickerProperty::cc_m, 1, true); // 255
            row3 -> change(ColorPickerProperty::cc_y, 1, true); // 255
            row4 -> change(ColorPickerProperty::cc_k, 1, true); // 255
        break;}

        case cn_hvb: {
            current_color = current_color.convertTo(QColor::Hsv);

            row1 -> change(ColorPickerProperty::cc_h, 1, true); // 255
            row2 -> change(ColorPickerProperty::cc_v, 1, true); // 255
            row3 -> change(ColorPickerProperty::cc_b, 1, true); // 255
        break;}

        default: Logger::obj().write(QLatin1Literal("ColorPicker"), QLatin1Literal("colorSpaceChanged: unknown namespace"), Logger::log_error);
    };

    row4 -> setVisible(new_namespace == cn_cmyk);
    curr_color_namespace = static_cast<ColorNamespace>(new_namespace);
    setColor(current_color);
}

void ColorPicker::hexChanged(const QString & name) {
    setColor(QColor(name));
}
