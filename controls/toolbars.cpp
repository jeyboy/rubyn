#include "toolbars.h"

#include <qmainwindow.h>

QToolBar * Toolbars::createWidget(const QString & name, const Qt::ToolBarArea & areas) {
    QToolBar * bar = new QToolBar(name, container);

    bar -> setObjectName(name);
    bar -> setAllowedAreas(areas);

    return bar;
}

void Toolbars::append(QToolBar * bar, const Qt::ToolBarArea & area) {
    container -> addToolBar(area, bar);
}
