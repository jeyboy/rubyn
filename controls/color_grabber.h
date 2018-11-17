#ifndef COLOR_GRABBER_H
#define COLOR_GRABBER_H

#include <qwidget.h>

class ColorGrabber : public QWidget {
    Q_OBJECT
public:
    ColorGrabber(QWidget * parent = nullptr);

    void initiate();
protected:
    void mouseMoveEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void keyPressEvent(QKeyEvent * e);
    void leaveEvent(QEvent * e);
signals:
    void colorHovered(const QRgb & rgb);
};

#endif // COLOR_GRABBER_H
