#ifndef TABBAR_H
#define TABBAR_H

#include <qtabbar.h>

class TabBar : public QTabBar {
    Q_OBJECT
public:
    TabBar(QWidget * parent = 0);
protected:
    void tabLayoutChange();
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dragMoveEvent(QDragMoveEvent *event);
//    void dragLeaveEvent(QDragLeaveEvent *event);
//    void dropEvent(QDropEvent *event);
signals:
    void layoutChanged();
};

#endif // TABBAR_H
