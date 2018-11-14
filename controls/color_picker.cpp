#include "color_picker.h"

#include <qlayout.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qbuttongroup.h>

#include "controls/logger.h"
#include "color_picker_property.h"

ColorPicker::ColorPicker(QWidget * parent) : QWidget(parent) {
    setuplayout();
}

void ColorPicker::setColor(const QColor & color) {

}

//TODO: add color picker button to header
// add curr_color_item to header

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

    QComboBox * hex_name = new QComboBox(this);
    hex_name -> setEditable(true);
    l -> addWidget(hex_name, 0, 1, 1, 4);

//    curr_color_item = new QLabel(this);
//    curr_color_item -> setStyleSheet("background-color: #00ff00");
//    l -> addWidget(curr_color_item, 1, 11);

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
    row1 -> change(ColorPickerProperty::cc_r, 255, false);
    vl -> addWidget(row1);

    row2 = new ColorPickerProperty(this);
    row2 -> change(ColorPickerProperty::cc_g, 255, false);
    vl -> addWidget(row2);

    row3 = new ColorPickerProperty(this);
    row3 -> change(ColorPickerProperty::cc_b, 255, false);
    vl -> addWidget(row3);

    row4 = new ColorPickerProperty(this);
    row4 -> change(ColorPickerProperty::cc_k, 255, false);
    vl -> addWidget(row4);
    row4 -> setVisible(false);

    l -> addLayout(vl, 1, 1, 4, 4);

    row_alpha = new ColorPickerProperty(this);
    row_alpha -> change(ColorPickerProperty::cc_a, 255, false);
    l -> addWidget(row_alpha, 5, 1, 1, 4);


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

    btn_group -> buttons().first() -> setChecked(true);
}

void ColorPicker::componentChanged() {

}

void ColorPicker::changeColorOutputs(QColor color) {
    qreal a = 255;

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


            row1 -> setVal(color.cyan());
            row2 -> setVal(color.magenta());
            row3 -> setVal(color.yellow());
            row4 -> setVal(color.black());
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
}

void ColorPicker::colorSpaceChanged(const int & new_namespace) {
    curr_color_namespace = static_cast<ColorNamespace>(new_namespace);

    switch(new_namespace) {
        case cn_rgb: {
            row1 -> change(ColorPickerProperty::cc_r, 255, false);
            row2 -> change(ColorPickerProperty::cc_g, 255, false);
            row3 -> change(ColorPickerProperty::cc_b, 255, false);

            row4 -> setVisible(false);
        break;}

        case cn_hsv: {
            row1 -> change(ColorPickerProperty::cc_h, 359, false);
            row2 -> change(ColorPickerProperty::cc_s, 255, false);
            row3 -> change(ColorPickerProperty::cc_v, 255, false);

            row4 -> setVisible(false);
        break;}

        case cn_hsl: {
            row1 -> change(ColorPickerProperty::cc_h, 359, false);
            row2 -> change(ColorPickerProperty::cc_s, 255, false);
            row3 -> change(ColorPickerProperty::cc_l, 255, false);

            row4 -> setVisible(false);
        break;}

        case cn_cmyk: {
            row1 -> change(ColorPickerProperty::cc_c, 255, false);
            row2 -> change(ColorPickerProperty::cc_m, 255, false);
            row3 -> change(ColorPickerProperty::cc_y, 255, false);
            row4 -> change(ColorPickerProperty::cc_k, 255, false);

            row4 -> setVisible(true);
        break;}

        case cn_hvb: {
            row1 -> change(ColorPickerProperty::cc_h, 255, false);
            row2 -> change(ColorPickerProperty::cc_v, 255, false);
            row3 -> change(ColorPickerProperty::cc_b, 255, false);

            row4 -> setVisible(false);
        break;}

        default: Logger::obj().write(QLatin1Literal("ColorPicker"), QLatin1Literal("colorSpaceChanged: unknown namespace"), Logger::log_error);
    };
}
