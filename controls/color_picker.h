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

    Color current_color;
    Color::Namespace color_space;
    Color::Metric color_metric;

    ColorButton * curr_color_item;
//    QLabel * colors_space;

    QComboBox * hex_name;
    QComboBox * metrics_list;

    ColorPickerProperty * row1;
    ColorPickerProperty * row2;
    ColorPickerProperty * row3;
    ColorPickerProperty * row4;
    ColorPickerProperty * row_alpha;

    void setuplayout();
public:
    ColorPicker(QWidget * parent = nullptr);
    void setColor(const Color & color);
    inline void setCurrentColorButton(ColorButton * clr_btn) {
        curr_color_item = clr_btn;
        setColor(current_color);
    }
protected:
    void changeColorOutputs(Color color);

public slots:
    void colorPickingRequired();
private slots:
    void metricSelectionChanged(int index);
    void componentChanged(const int & component, const qreal & new_val);
    void colorSpaceChanged(const int & new_namespace);
    void hexChanged(const QString &);
};

#endif // COLOR_PICKER_H
