#include "color_picker.h"

#include <qlayout.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qbuttongroup.h>

#include "misc/defines.h"
#include "logger.h"
#include "color_grabber.h"
#include "color_button.h"
#include "color_picker_property.h"

ColorPicker::ColorPicker(QWidget * parent) : QWidget(parent), grabber(nullptr), curr_color_item(nullptr) {
    setuplayout();
}

ColorPicker::~ColorPicker() {
    delete grabber;
}

void ColorPicker::setColor(const Color & color) {
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

    metrics_list = new QComboBox(this);
    metrics_list -> setEditable(false);
    metrics_list -> addItem(QLatin1Literal("0.0-1.0"), Color::cm_proportional);
    metrics_list -> addItem(QLatin1Literal("0-255"), Color::cm_ranged);
    metrics_list -> addItem(QLatin1Literal("0-100%"), Color::cm_percentage);
    l -> addWidget(metrics_list, 0, 4);

    metrics_list -> setCurrentText(QLatin1Literal("0-255"));
    color_metric = Color::cm_ranged;
    connect(metrics_list, SIGNAL(currentIndexChanged(int)), this, SLOT(metricSelectionChanged(int)));


    QList<QPair<Color::Namespace, QLatin1String> > names = {
        QPair<Color::Namespace, QLatin1String>(Color::Rgb, QLatin1Literal("RGB")),
        QPair<Color::Namespace, QLatin1String>(Color::Hsv, QLatin1Literal("HSV")),
        QPair<Color::Namespace, QLatin1String>(Color::Hsl, QLatin1Literal("HSL")),
        QPair<Color::Namespace, QLatin1String>(Color::Cmyk, QLatin1Literal("CMYK")),
        QPair<Color::Namespace, QLatin1String>(Color::Hwb, QLatin1Literal("HWB")),
    };
    QList<QPair<Color::Namespace, QLatin1String> >::Iterator it = names.begin();

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
    row1 -> change(Color::cc_rgb_r, color_metric);
    vl -> addWidget(row1);

    row2 = new ColorPickerProperty(this);
    row2 -> change(Color::cc_rgb_g, color_metric);
    vl -> addWidget(row2);

    row3 = new ColorPickerProperty(this);
    row3 -> change(Color::cc_rgb_b, color_metric);
    vl -> addWidget(row3);

    row4 = new ColorPickerProperty(this);
    row4 -> change(Color::cc_cmyk_k, color_metric);
    vl -> addWidget(row4);
    row4 -> setVisible(false);

    l -> addLayout(vl, 1, 1, 4, 4);

    row_alpha = new ColorPickerProperty(this);
    row_alpha -> change(Color::cc_alpha, color_metric);
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

void ColorPicker::changeColorOutputs(Color color) {
    const QSignalBlocker blocker1(row1);
    const QSignalBlocker blocker2(row2);
    const QSignalBlocker blocker3(row3);
    const QSignalBlocker blocker4(row4);
    const QSignalBlocker blockera(row_alpha);
    const QSignalBlocker blocker_hex(hex_name);

    current_color = color;
    qreal c1, c2, c3, c4, a;

    color.getComponents(color_space, c1, c2, c3, c4, a, color_metric);

    row1 -> setVal(c1);
    row2 -> setVal(c2);
    row3 -> setVal(c3);
    row4 -> setVal(c4);

    row_alpha -> setVal(a);

    hex_name -> setCurrentText(color.name(QColor::HexArgb));
}

void ColorPicker::colorPickingRequired() {
    if (!grabber) {
        grabber = new ColorGrabber();
        connect(grabber, SIGNAL(colorHovered(const QRgb &)), this, SLOT(colorHovered(const QRgb &)));
    }

    grabber -> initiate();
    grabber -> show();
}

void ColorPicker::metricSelectionChanged(int index) {
    const QSignalBlocker blocker1(row1);
    const QSignalBlocker blocker2(row2);
    const QSignalBlocker blocker3(row3);
    const QSignalBlocker blocker4(row4);
    const QSignalBlocker blockera(row_alpha);
    const QSignalBlocker blocker_hex(hex_name);

    color_metric = static_cast<Color::Metric>(metrics_list -> itemData(index).toInt());

    colorSpaceChanged(color_space);
}

void ColorPicker::componentChanged(const int & component, const qreal & new_val) {
    Color color = current_color;

    color.setComponent(color_space, static_cast<Color::Component>(component), new_val, color_metric);

    setColor(color);
}

void ColorPicker::colorSpaceChanged(const int & new_namespace) {
    switch(new_namespace) {
        case Color::Rgb: {
            row1 -> change(Color::cc_rgb_r, color_metric);
            row2 -> change(Color::cc_rgb_g, color_metric);
            row3 -> change(Color::cc_rgb_b, color_metric);
        break;}

        case Color::Hsv: {
            row1 -> change(Color::cc_hsv_h, color_metric);
            row2 -> change(Color::cc_hsv_s, color_metric);
            row3 -> change(Color::cc_hsv_v, color_metric);
        break;}

        case Color::Hsl: {
            row1 -> change(Color::cc_hsl_h, color_metric);
            row2 -> change(Color::cc_hsl_s, color_metric);
            row3 -> change(Color::cc_hsl_l, color_metric);
        break;}

        case Color::Cmyk: {
            row1 -> change(Color::cc_cmyk_c, color_metric);
            row2 -> change(Color::cc_cmyk_m, color_metric);
            row3 -> change(Color::cc_cmyk_y, color_metric);
            row4 -> change(Color::cc_cmyk_k, color_metric);
        break;}

        case Color::Hwb: {
            row1 -> change(Color::cc_hwb_h, color_metric);
            row2 -> change(Color::cc_hwb_w, color_metric);
            row3 -> change(Color::cc_hwb_b, color_metric);
        break;}

        default: Logger::error(QLatin1Literal("ColorPicker"), QLatin1Literal("colorSpaceChanged: unknown namespace"));
    };

    row_alpha -> change(Color::cc_alpha, color_metric);

    row4 -> setVisible(new_namespace == Color::Cmyk);
    color_space = static_cast<Color::Namespace>(new_namespace);
    current_color = current_color.convertTo(color_space);
    setColor(current_color);
}

void ColorPicker::hexChanged(const QString & name) {
    setColor(QColor(name));
}

void ColorPicker::colorHovered(const QRgb & rgb) { setColor(QColor(rgb)); }
