#ifndef TOOLBARS
#define TOOLBARS

#include <qtoolbar.h>

#include "misc/singleton.h"

class QMainWindow;

class Toolbars : public Singleton<Toolbars> {
    QMainWindow * container;
public:
    void registerContainer(QMainWindow * target) { container = target; }

    QToolBar * createWidget(const QString & name, const Qt::ToolBarArea & areas = Qt::AllToolBarAreas);

    void append(QToolBar * bar, const Qt::ToolBarArea & area = Qt::LeftToolBarArea);
};

#endif // TOOLBARS
