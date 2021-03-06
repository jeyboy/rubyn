#ifndef DOCK_WIDGETS
#define DOCK_WIDGETS

#include "misc/singleton.h"

class DockWidget;
class QMainWindow;

class DockWidgets : public Singleton<DockWidgets> {
    QMainWindow * container;
public:
    void registerContainer(QMainWindow * target) { container = target; }

    DockWidget * createWidget(const QString & name, QWidget * content, const Qt::DockWidgetAreas & areas = Qt::AllDockWidgetAreas);

    void append(DockWidget * bar, const Qt::DockWidgetArea & area = Qt::LeftDockWidgetArea);
    void insert(DockWidget * bar, DockWidget * dock);
};

#endif // DOCK_WIDGETS
