#ifndef DEBUG_VIEW_H
#define DEBUG_VIEW_H

#include <qtreewidget.h>

class DebugView : public QTreeWidget {
    Q_OBJECT
public:
    DebugView(QWidget * parent = nullptr);
protected:
    void mouseDoubleClickEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

signals:
    void newItemRequired();
};

#endif // DEBUG_VIEW_H
