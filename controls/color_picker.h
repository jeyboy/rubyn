#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <qwidget.h>

class QLabel;

class ColorPicker : public QWidget {
    Q_OBJECT

    QLabel * curr_color_item;
    QLabel * colors_space;

    QColor current_color;

    void setuplayout();
public:
    ColorPicker(QWidget * parent = nullptr);
};

#endif // COLOR_PICKER_H
