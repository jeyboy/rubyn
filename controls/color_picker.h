#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <qwidget.h>

class QLabel;
class ColorPickerProperty;
class QToolButton;
class QComboBox;
class ColorButton;

class ColorPicker : public QWidget {
    Q_OBJECT

    enum ColorNamespace {
        cn_none = 0,
        cn_rgb,
        cn_cmyk,
        cn_hsv,
        cn_hsl,
        cn_hvb
    };

    enum PropertyMetric {
        pm_none = 0,
        pm_proportional, // 0..1
        pm_ranged, // 0..255
        pm_percentage // 0..100%
    };

    ColorButton * curr_color_item;
    ColorNamespace curr_color_namespace;
//    QLabel * colors_space;

    QComboBox * hex_name;

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
    inline void setCurrentColorButton(ColorButton * clr_btn) {
        curr_color_item = clr_btn;
        setColor(current_color);
    }
protected:
    void changeColorOutputs(QColor color);

    void hwbToHsv(const qreal & w, const qreal & b, qreal & s, qreal & v) {
        s = 1.0 - (w / (1.0 - b));
        v = 1.0 - b;
    }

public slots:
    void colorPickingRequired();

private slots:
    void componentChanged(const int & component, const qreal & new_val);
    void colorSpaceChanged(const int & new_namespace);
    void hexChanged(const QString &);
};

#endif // COLOR_PICKER_H
