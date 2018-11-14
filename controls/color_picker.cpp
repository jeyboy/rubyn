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
    QVBoxLayout * vl = new QVBoxLayout();

    l -> setContentsMargins(1, 1, 1, 1);

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


    QLabel * hex_label = new QLabel(QLatin1Literal("Hex"), this);
    l -> addWidget(hex_label, 0, 11, Qt::AlignRight | Qt::AlignVCenter);

    QComboBox * hex_name = new QComboBox(this);
    hex_name -> setEditable(true);
    l -> addWidget(hex_name, 0, 12, 1, 4);



    curr_color_item = new QLabel(this);
    curr_color_item -> setStyleSheet("background-color: #00ff00");
    l -> addWidget(curr_color_item, 1, 11);

    QToolButton * color_picker_btn = new QToolButton(this);
    color_picker_btn -> setCheckable(true);
    color_picker_btn -> setText(QLatin1Literal("Pick"));
    l -> addWidget(color_picker_btn, 1, 15);

    rgb_toggle_btn = new QToolButton(this);
    rgb_toggle_btn -> setProperty("space", cn_rgb);
    rgb_toggle_btn -> setCheckable(true);
    rgb_toggle_btn -> setText(QLatin1Literal("RGB"));
    rgb_toggle_btn -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    l -> addWidget(rgb_toggle_btn, 1, 12, 1, 3);

    hsv_toggle_btn = new QToolButton(this);
    hsv_toggle_btn -> setProperty("space", cn_hsv);
    hsv_toggle_btn -> setCheckable(true);
    hsv_toggle_btn -> setText(QLatin1Literal("H\nS\nV"));
    hsv_toggle_btn -> setFixedWidth(20);
    hsv_toggle_btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    l -> addWidget(hsv_toggle_btn, 2, 11, 2, 1);

    hsl_toggle_btn = new QToolButton(this);
    hsl_toggle_btn -> setProperty("space", cn_hsl);
    hsl_toggle_btn -> setCheckable(true);
    hsl_toggle_btn -> setText(QLatin1Literal("H\nS\nL"));
    hsl_toggle_btn -> setFixedWidth(20);
    hsl_toggle_btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    l -> addWidget(hsl_toggle_btn, 4, 11, 2, 1);

    cmyk_toggle_btn = new QToolButton(this);
    cmyk_toggle_btn -> setProperty("space", cn_cmyk);
    cmyk_toggle_btn -> setCheckable(true);
    cmyk_toggle_btn -> setText(QLatin1Literal("CMYK"));
    cmyk_toggle_btn -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    l -> addWidget(cmyk_toggle_btn, 6, 12, 1, 3);

    hvb_toggle_btn = new QToolButton(this);
    hvb_toggle_btn -> setProperty("space", cn_hvb);
    hvb_toggle_btn -> setCheckable(true);
    hvb_toggle_btn -> setText(QLatin1Literal("H\nV\nB"));
    hvb_toggle_btn -> setFixedWidth(20);
    hvb_toggle_btn -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    l -> addWidget(hvb_toggle_btn, 2, 15, 4, 1);


    connect(rgb_toggle_btn, SIGNAL(clicked()), this, SLOT(colorSpaceChanged()));
    connect(hsv_toggle_btn, SIGNAL(clicked()), this, SLOT(colorSpaceChanged()));
    connect(hsl_toggle_btn, SIGNAL(clicked()), this, SLOT(colorSpaceChanged()));
    connect(cmyk_toggle_btn, SIGNAL(clicked()), this, SLOT(colorSpaceChanged()));
    connect(hvb_toggle_btn, SIGNAL(clicked()), this, SLOT(colorSpaceChanged()));



    row1 = new ColorPickerProperty(this);
    row1 -> change(ColorPickerProperty::cc_r, 255);
    vl -> addWidget(row1);

    row2 = new ColorPickerProperty(this);
    row2 -> change(ColorPickerProperty::cc_g, 255);
    vl -> addWidget(row2);

    row3 = new ColorPickerProperty(this);
    row3 -> change(ColorPickerProperty::cc_b, 255);
    vl -> addWidget(row3);

    row4 = new ColorPickerProperty(this);
    row4 -> change(ColorPickerProperty::cc_k, 255);
    vl -> addWidget(row4);
    row4 -> setVisible(false);

    l -> addLayout(vl, 2, 12, 4, 3);

    ColorPickerProperty * row_alpha = new ColorPickerProperty(this);
    row_alpha -> label -> setText(QLatin1Literal("A"));
    l -> addWidget(row_alpha, 7, 12, 1, 3);


    QToolButton * down_toggle_btn = new QToolButton(this);
    down_toggle_btn -> setFixedHeight(12);
    down_toggle_btn -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    down_toggle_btn -> setText(QLatin1Literal("\\/"));
    down_toggle_btn -> setStyleSheet("background-color: rgba(0,255,0, .2)");
    l -> addWidget(down_toggle_btn, 8, 11, 1, 5);

    down_toggle_btn -> setVisible(false);

//    QComboBox * colors_sets = new QComboBox(this);
//    QLabel * colors_set = new QLabel(this);
////    Rgb, Hsv, Cmyk, Hsl

    rgb_toggle_btn -> setChecked(true);
}

void ColorPicker::colorSpaceChanged() {
    QObject * obj = sender();
    int space = obj -> property("space").toInt();

    switch(space) {
        case cn_rgb:
        case cn_hsv:
        case cn_hsl:
        case cn_cmyk:
        case cn_hvb:
        default:;
    };
}
