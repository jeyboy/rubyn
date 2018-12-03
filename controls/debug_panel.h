#ifndef DEBUG_PANEL_H
#define DEBUG_PANEL_H

#include <qtreewidget.h>

class DebugPanel : public QTreeWidget {
public:
    DebugPanel(QWidget * parent = nullptr);
};

#endif // DEBUG_PANEL_H
