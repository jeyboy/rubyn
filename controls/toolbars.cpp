#include "toolbars.h"

#include <qmainwindow.h>

QToolBar * Toolbars::createWidget(const QString & name, const Qt::ToolBarArea & areas) {
    QToolBar * bar = new QToolBar(name, container);

    bar -> setObjectName(name);
    bar -> setAllowedAreas(areas);

    bar -> setStyleSheet(
        QLatin1String(
            "QToolBar {"
            "   border: 2px solid #ddd;"
            "   background-color: #555;"
            "   border-radius: 6px;"
            "}"

            "QToolBar QToolButton {"
            "   border: 1px solid #aaa;"
            "   background-color: #fff;"
            "   border-radius: 6px;"
            "}"
        )
    );

    return bar;
}

void Toolbars::append(QToolBar * bar, const Qt::ToolBarArea & area) {
    container -> addToolBar(area, bar);
}
