#ifndef DEBUG_VIEW_H
#define DEBUG_VIEW_H

#include <qtreewidget.h>

class DebugView : public QTreeWidget {
    Q_OBJECT
public:
    DebugView(QWidget * parent = nullptr);
protected:
    void mouseDoubleClickEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

//protected slots:
//    void modelRowsInserted(const QModelIndex &parent, int first, int last);
//    void modelRowsRemoved(const QModelIndex &parent, int first, int last);

signals:
    void newItemRequired();
};

#endif // DEBUG_VIEW_H
