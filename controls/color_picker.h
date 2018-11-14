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

    ColorPickerProperty * row1;
    ColorPickerProperty * row2;
    ColorPickerProperty * row3;
    ColorPickerProperty * row4;
    ColorPickerProperty * row_alpha;

    QColor current_color;

    void setuplayout();
public:
    ColorPicker(QWidget * parent = nullptr);
    void setColor(const QColor & color);

protected:
    void componentChanged();
    void changeColorOutputs(QColor color);

    void hwbToHsv(const qreal & h, const qreal & w, const qreal & b, qreal & s, qreal & v) {
        s = 1.0 - (w / (1.0 - b));
        v = 1.0 - b;
    }

private slots:
    void colorSpaceChanged(const int & new_namespace);

};

#endif // COLOR_PICKER_H
