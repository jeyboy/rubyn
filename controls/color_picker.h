#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <qwidget.h>

#include "misc/color.h"

class QLabel;
class ColorPickerProperty;
class QToolButton;
class QComboBox;
class ColorButton;

class ColorPicker : public QWidget {
    Q_OBJECT

    Color::Spec curr_color_namespace;

    ColorButton * curr_color_item;
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
