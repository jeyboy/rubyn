#ifndef COLOR_SLIDER_H
#define COLOR_SLIDER_H

#include <qslider.h>

class JSliderStyle;

class ColorSlider : public QSlider {
    Q_OBJECT

    JSliderStyle * jstyle;
public:
    explicit ColorSlider(QWidget * parent = nullptr);
protected:
    void resizeEvent(QResizeEvent * e);

    void calcBackground();
signals:

public slots:
};

#endif // COLOR_SLIDER_H
