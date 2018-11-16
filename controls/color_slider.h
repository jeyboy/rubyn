#ifndef COLOR_SLIDER_H
#define COLOR_SLIDER_H

#include <qslider.h>

class JSliderStyle;

class ColorSlider : public QSlider {
    Q_OBJECT

    JSliderStyle * jstyle;
public:
    explicit ColorSlider(QWidget * parent = nullptr);

    void calcBackground(const bool & updating = false);
protected:
    void resizeEvent(QResizeEvent * e);

signals:

public slots:
};

#endif // COLOR_SLIDER_H
