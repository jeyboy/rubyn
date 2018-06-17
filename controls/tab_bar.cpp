#include "tab_bar.h"

#include "tab_bar_item_delegate.h"

#include <qscrollbar.h>
#include <qmimedata.h>
#include <qdebug.h>

TabBar::TabBar(QWidget * parent) : QListWidget(parent), _internal_move(false) {
    setMaximumHeight(26);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFlow(QListView::LeftToRight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::SelectedClicked);
//    setMovement(QListView::Free);

    TabBarItemDelegate * item_delegate = new TabBarItemDelegate(this);
    setItemDelegate(item_delegate);
    connect(item_delegate, SIGNAL(closeTabRequested(QModelIndex)), this , SLOT(itemCloseRequested(QModelIndex)));
}

QListWidgetItem * TabBar::addTab(const QIcon & ico, const QString & text) {
    QListWidgetItem * item = new QListWidgetItem(ico, text);
    addItem(item);
    return item;
}

void TabBar::removeTab(QListWidgetItem * tab) {
    delete tab;
}

Qt::DropActions TabBar::supportedDropActions() const {
    return Qt::MoveAction | Qt::CopyAction;
}

void TabBar::dropEvent(QDropEvent * event) {
    QListWidgetItem * copy_source = 0;

    if ((_internal_move = event -> source() == this)) {
        copy_source = currentItem();
    } else {
        copy_source = reinterpret_cast<TabBar *>(event -> source()) -> currentItem();
    }

    QListWidget::dropEvent(event);

    _internal_move = false;

    delete copy_source;
}

//QMimeData * TabBar::mimeData(const QList<QListWidgetItem *> items) const {
//    QMimeData * data = QListWidget::mimeData(items);

////    data -> setParent(this);

//    qDebug() << data -> parent();

//    return data;
//}

bool TabBar::dropMimeData(int index, const QMimeData * data, Qt::DropAction action) {
    //TODO: reject drop if this file already exists in current tab bar and
    //   drop is not eternal + find this file and set like current

    if (!_internal_move) {

    }

    bool res = QListWidget::dropMimeData(index, data, action);

    emit currentRowChanged(index);

    return res;
}

void TabBar::rowsInserted(const QModelIndex &parent, int start, int end) {
    QListWidget::rowsInserted(parent, start, end);

    emit itemsCountChanged();
}
void TabBar::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end) {
    QListWidget::rowsAboutToBeRemoved(parent, start, end);
    emit itemsCountChanged(start - (end + 1));
}

void TabBar::updateGeometries() {
    QListWidget::updateGeometries();

    emit scrollsRequired(horizontalScrollBar() -> maximum() > 0);
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

