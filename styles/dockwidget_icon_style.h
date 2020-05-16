#ifndef DOCKWIDGET_ICON_STYLE_H
#define DOCKWIDGET_ICON_STYLE_H

#include <qproxystyle.h>
#include <qstyleoption.h>
#include <qpainter.h>

class DockwidgetIconStyle: public QProxyStyle {
    Q_OBJECT

    QIcon _icon;
public:
    DockwidgetIconStyle(const QIcon & icon, QStyle * style = nullptr) : QProxyStyle(style), _icon(icon) {}

    virtual ~DockwidgetIconStyle() {}

    virtual void drawControl(ControlElement element, const QStyleOption * option, QPainter * painter, const QWidget * widget = Q_NULLPTR) const {
        if (element == QStyle::CE_DockWidgetTitle) {
            //width of the icon
            int width = pixelMetric(QStyle::PM_ToolBarIconSize);
            //margin of title from frame
            int margin = baseStyle() -> pixelMetric(QStyle::PM_DockWidgetTitleMargin);

            QPoint icon_point(margin + option -> rect.left(), margin + option -> rect.center().y() - width / 2);

            painter -> drawPixmap(icon_point, _icon.pixmap(width, width));

            const_cast<QStyleOption *>(option) -> rect = option -> rect.adjusted(width, 0, 0, 0);
        }

        baseStyle() -> drawControl(element, option, painter, widget);
    }
};

#endif // DOCKWIDGET_ICON_STYLE_H
