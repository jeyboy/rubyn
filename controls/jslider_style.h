#ifndef JSLIDER_STYLE_H
#define JSLIDER_STYLE_H

#include <qproxystyle.h>

class JSliderStyle : public QProxyStyle {
public:
    JSliderStyle(QStyle * style);

    void drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex * option, QPainter * painter, const QWidget * widget) const;

    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex * opt, SubControl sc, const QWidget * widget) const;
};

#endif // JSLIDER_STYLE_H
