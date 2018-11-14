#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <qwidget.h>

class QLabel;
class ColorPickerProperty;
class QToolButton;

class ColorPicker : public QWidget {
    Q_OBJECT

    enum ColorNamespace {
        cn_none = 0,
        cn_rgb,
        cn_hsv,
        cn_hsl,
        cn_cmyk,
        cn_hvb
    };

    QLabel * curr_color_item;
    ColorNamespace curr_color_namespace;
//    QLabel * colors_space;

    QToolButton * rgb_toggle_btn;
    QToolButton * hsv_toggle_btn;
    QToolButton * hsl_toggle_btn;
    QToolButton * cmyk_toggle_btn;
    QToolButton * hvb_toggle_btn;

    ColorPickerProperty * row1;
    ColorPickerProperty * row2;
    ColorPickerProperty * row3;
    ColorPickerProperty * row4;

    QColor current_color;

    void setuplayout();
public:
    ColorPicker(QWidget * parent = nullptr);
private slots:
    void colorSpaceChanged();
};

#endif // COLOR_PICKER_H
