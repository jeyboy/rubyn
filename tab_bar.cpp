#include "tab_bar.h"

#include <qscrollbar.h>

TabBar::TabBar(QWidget * parent) : QListWidget(parent) {
    setMaximumHeight(50);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFlow(QListView::LeftToRight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QListWidgetItem * TabBar::addTab(const QIcon & ico, const QString & text) {
    QListWidgetItem * item = new QListWidgetItem(ico, text);
    addItem(item);

    emit layoutChanged();

    return item;
}

void TabBar::removeTab(QListWidgetItem * tab) {
    delete tab;

    emit layoutChanged();
}

void TabBar::scrollForward() {
    horizontalScrollBar() -> triggerAction(QAbstractSlider::SliderPageStepAdd);
}
void TabBar::scrollBackward() {
    horizontalScrollBar() -> triggerAction(QAbstractSlider::SliderPageStepSub);
}

