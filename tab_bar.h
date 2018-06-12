#ifndef TABBAR_H
#define TABBAR_H

#include <qtabbar.h>

class TabBar : public QTabBar {
    Q_OBJECT
public:
    TabBar(QWidget * parent = 0);
protected:
    void tabLayoutChange();
signals:
    void layoutChanged();
};

#endif // TABBAR_H
