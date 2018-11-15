#ifndef COLOR_BUTTON_H
#define COLOR_BUTTON_H

#include <qtoolbutton.h>

class ColorButton : public QToolButton {
    Q_OBJECT

    QColor color;
public:
    explicit ColorButton(QWidget * parent = nullptr);
    void setColor(const QColor & new_color) {
        color = new_color;
        update();
    }

protected:
    void paintEvent(QPaintEvent * e) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // COLOR_BUTTON_H
