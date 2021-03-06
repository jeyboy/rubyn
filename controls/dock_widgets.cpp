#include "dock_widgets.h"

#include "dock_widget.h"

#include <qmainwindow.h>

DockWidget * DockWidgets::createWidget(const QString & name, QWidget * content, const Qt::DockWidgetAreas & areas) {
    DockWidget * dock = new DockWidget(name, container, areas);

//    connect(dock, SIGNAL(closing()), this, SLOT(barClosed()));
//    connect(dock, SIGNAL(topLevelChanged(bool)), this, SLOT(updateActiveTabIcon(bool)));
  //    dock -> showFullScreen();

    if (content) {
        dock -> setWidget(content);
    }

    return dock;
}

void DockWidgets::append(DockWidget * bar, const Qt::DockWidgetArea & area) {
    container -> addDockWidget(area, bar);
}

void DockWidgets::insert(DockWidget * bar, DockWidget * dock) {
    container -> tabifyDockWidget(bar, dock);
}
