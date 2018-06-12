#include "tab_bar.h"

TabBar::TabBar(QWidget * parent) : QTabBar(parent) {

}

void TabBar::tabLayoutChange() {
    emit layoutChanged();
}
