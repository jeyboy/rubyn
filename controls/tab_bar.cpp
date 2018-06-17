#include "tab_bar.h"

#include "tab_bar_item_delegate.h"

#include <qscrollbar.h>
#include <qmimedata.h>
#include <qdebug.h>

TabBar::TabBar(QWidget * parent) : QListWidget(parent) {
    setMaximumHeight(30);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFlow(QListView::LeftToRight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::SelectedClicked);

    TabBarItemDelegate * item_delegate = new TabBarItemDelegate(this);
    setItemDelegate(item_delegate);
    connect(item_delegate, SIGNAL(closeTabRequested(QModelIndex)), this , SLOT(itemCloseRequested(QModelIndex)));
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

Qt::DropActions TabBar::supportedDropActions() const {
    return Qt::MoveAction; // | Qt::CopyAction
}

QMimeData * TabBar::mimeData(const QList<QListWidgetItem *> items) const {
    QMimeData * data = QListWidget::mimeData(items);

//    data -> setParent(this);

    qDebug() << data -> parent();

    return data;
}

bool TabBar::dropMimeData(int index, const QMimeData * data, Qt::DropAction action) {
    qDebug() << this << data -> parent();
    return QListWidget::dropMimeData(index, data, action);
}

void TabBar::itemCloseRequested(const QModelIndex & index) {
    QListWidgetItem * item = itemFromIndex(index);

    if (item)
        emit tabCloseRequested(item);
}

void TabBar::scrollForward() {
    horizontalScrollBar() -> triggerAction(QAbstractSlider::SliderPageStepAdd);
}
void TabBar::scrollBackward() {
    horizontalScrollBar() -> triggerAction(QAbstractSlider::SliderPageStepSub);
}

