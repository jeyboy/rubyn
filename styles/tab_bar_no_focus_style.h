#ifndef TAB_BAR_NO_FOCUS_STYLE_H
#define TAB_BAR_NO_FOCUS_STYLE_H

#include <qproxystyle.h>

class TabBarNoFocusStyle : public QProxyStyle {
public:
    void drawPrimitive(PrimitiveElement element, const QStyleOption * option, QPainter * painter, const QWidget * widget) const {
        if ( element == PE_FrameFocusRect ) return;

        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
};

#endif // TAB_BAR_NO_FOCUS_STYLE_H
