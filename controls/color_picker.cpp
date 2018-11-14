#include "color_picker.h"

#include <qlayout.h>
#include <qtoolbutton.h>
#include <qcombobox.h>

#include "color_picker_property.h"

ColorPicker::ColorPicker(QWidget * parent) : QWidget(parent) {
    setuplayout();
}

void ColorPicker::setuplayout() {
    QGridLayout * l = new QGridLayout(this);
    l -> setContentsMargins(1, 1, 1, 1);

    colors_space = new QLabel(this);
    colors_space -> setStyleSheet("background-color: rgba(255,0,0, .2)");
    l -> addWidget(colors_space, 0, 0, 9, 10);

    QToolButton * left_toggle_btn = new QToolButton(this);
    left_toggle_btn -> setFixedWidth(12);
//    left_toggle_btn -> setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    left_toggle_btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    left_toggle_btn -> setText(QLatin1Literal("<"));
    left_toggle_btn -> setStyleSheet("background-color: rgba(0,255,0, .2)");
    l -> addWidget(left_toggle_btn, 0, 11, 9, 1);


//    QComboBox * color_names = new QComboBox(this);
//    l -> addWidget(color_names, 1, 12, 1, 5);


    QLabel * hex_label = new QLabel(QLatin1Literal("Hex"), this);
    l -> addWidget(hex_label, 0, 12, Qt::AlignRight | Qt::AlignVCenter);

    QComboBox * hex_name = new QComboBox(this);
    hex_name -> setEditable(true);
    l -> addWidget(hex_name, 0, 13, 1, 4);



    curr_color_item = new QLabel(this);
    curr_color_item -> setStyleSheet("background-color: #00ff00");
    l -> addWidget(curr_color_item, 1, 12);

    QToolButton * color_picker_btn = new QToolButton(this);
    color_picker_btn -> setText(QLatin1Literal("Pick"));
    l -> addWidget(color_picker_btn, 1, 16);

    QToolButton * rgb_toggle_btn = new QToolButton(this);
    rgb_toggle_btn -> setText(QLatin1Literal("RGB"));
    rgb_toggle_btn -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    l -> addWidget(rgb_toggle_btn, 1, 13, 1, 3);

    QToolButton * hsv_toggle_btn = new QToolButton(this);
    hsv_toggle_btn -> setText(QLatin1Literal("HSV"));
    hsv_toggle_btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    l -> addWidget(hsv_toggle_btn, 2, 12, 2, 1);

    QToolButton * hsl_toggle_btn = new QToolButton(this);
    hsl_toggle_btn -> setText(QLatin1Literal("HSL"));
    hsl_toggle_btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    l -> addWidget(hsl_toggle_btn, 4, 12, 2, 1);

    QToolButton * cmyk_toggle_btn = new QToolButton(this);
    cmyk_toggle_btn -> setText(QLatin1Literal("CMYK"));
    cmyk_toggle_btn -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    l -> addWidget(cmyk_toggle_btn, 6, 13, 1, 3);

    QToolButton * hvb_toggle_btn = new QToolButton(this);
    hvb_toggle_btn -> setText(QLatin1Literal("HVB"));
    hvb_toggle_btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    l -> addWidget(hvb_toggle_btn, 2, 16, 4, 1);


    ColorPickerProperty * row1 = new ColorPickerProperty(this);
    row1 -> label -> setText(QLatin1Literal("C"));
    l -> addWidget(row1, 2, 13, 1, 3);

    ColorPickerProperty * row2 = new ColorPickerProperty(this);
    row2 -> label -> setText(QLatin1Literal("M"));
    l -> addWidget(row2, 3, 13, 1, 3);

    ColorPickerProperty * row3 = new ColorPickerProperty(this);
    row3 -> label -> setText(QLatin1Literal("Y"));
    l -> addWidget(row3, 4, 13, 1, 3);

    ColorPickerProperty * row4 = new ColorPickerProperty(this);
    row4 -> label -> setText(QLatin1Literal("K"));
    l -> addWidget(row4, 5, 13, 1, 3);


    ColorPickerProperty * row_alpha = new ColorPickerProperty(this);
    row_alpha -> label -> setText(QLatin1Literal("A"));
    l -> addWidget(row_alpha, 7, 13, 1, 3);


    QToolButton * down_toggle_btn = new QToolButton(this);
    down_toggle_btn -> setFixedHeight(12);
    down_toggle_btn -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    down_toggle_btn -> setText(QLatin1Literal("\\/"));
    down_toggle_btn -> setStyleSheet("background-color: rgba(0,255,0, .2)");
    l -> addWidget(down_toggle_btn, 8, 12, 1, 5);

//    QComboBox * colors_sets = new QComboBox(this);
//    QLabel * colors_set = new QLabel(this);
////    Rgb, Hsv, Cmyk, Hsl
}
