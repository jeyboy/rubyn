#include "tab_bar.h"

#include <qscrollbar.h>
#include <qmimedata.h>
#include <qdebug.h>

TabBar::TabBar(QWidget * parent) : QListWidget(parent) {
    setMaximumHeight(30);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFlow(QListView::LeftToRight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragDropOverwriteMode(true);
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

QMimeData * TabBar::mimeData(const QList<QListWidgetItem *> items) const {
    QMimeData * data = QListWidget::mimeData(items);

    data -> setParent(this);

    return data;
}

bool TabBar::dropMimeData(int index, const QMimeData * data, Qt::DropAction action) {
    qDebug() << this << data -> parent();
    return QListWidget::dropMimeData(index, data, action);
}

void TabBar::scrollForward() {
    horizontalScrollBar() -> triggerAction(QAbstractSlider::SliderPageStepAdd);
}
void TabBar::scrollBackward() {
    horizontalScrollBar() -> triggerAction(QAbstractSlider::SliderPageStepSub);
}

