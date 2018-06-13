#include "tab_bar.h"

//* List of visible tabs
//QRect r = tabBar->rect();
//int numTabs = tabBar->count();
//int firstVisible = 0;
//int lastVisible = numTabs - 1;

//while(firstVisible < numTabs && !r.intersects(tabBar->tabRect(firstVisible)))
//    ++firstVisible;

//while(lastVisible > 0 && !r.intersects(tabBar->tabRect(lastVisible)))
//    --lastVisible;

//qDebug() << firstVisible << lastVisible;

//If you want only fully visible tabs switch intersects() to contains().

TabBar::TabBar(QWidget * parent) : QTabBar(parent) {
//    "QTabBar::scroller{width:85pix;}"
//    setStyleSheet("QTabBar QToolButton::right-arrow {background-color: 'light blue';} QTabBar QToolButton::left-arrow {background-color: 'light blue';}");
//    image: url(rightarrow.png);

//    QTabBar::close-button {
//        image: url(close.png)
//        subcontrol-position: left;
//    }
//    QTabBar::close-button:hover {
//        image: url(close-hover.png)
//    }
}

void TabBar::tabLayoutChange() {
    emit layoutChanged();
}
