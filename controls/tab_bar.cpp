#include "tab_bar.h"

#include "tab_bar_item_delegate.h"
#include "project/file.h"

#include <qscrollbar.h>
#include <qmimedata.h>
#include <qdebug.h>

TabBar::TabBar(QWidget * parent) : QListWidget(parent), hscroll_range(-1), _internal_move(false) {
    setMaximumHeight(30);
    setIconSize(QSize(22, 22));

    setSelectionMode(QAbstractItemView::SingleSelection);
    setFlow(QListView::LeftToRight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::SelectedClicked);
//    setMovement(QListView::Free);

    TabBarItemDelegate * item_delegate = new TabBarItemDelegate(this);
    setItemDelegate(item_delegate);
    connect(item_delegate, SIGNAL(closeTabRequested(QModelIndex)), this , SLOT(itemCloseRequested(QModelIndex)));

    connect(horizontalScrollBar(), SIGNAL(rangeChanged(int,int)), this, SLOT(scrollUpdated(int,int)));
}

QListWidgetItem * TabBar::addTab(const QIcon & ico, const QString & text) {
    QListWidgetItem * item = new QListWidgetItem(ico, text);
    addItem(item);
    return item;
}

void TabBar::removeTab(QListWidgetItem * tab) {
    delete tab;
}

File * TabBar::tabFile(QListWidgetItem * tab) {
    QVariant tab_data = tab -> data(Qt::UserRole);

    if (!tab_data.isNull()) {
        return reinterpret_cast<File *>(tab_data.value<quintptr>());
    }

    return 0;
}

Qt::DropActions TabBar::supportedDropActions() const {
    return Qt::MoveAction | Qt::CopyAction;
}

void TabBar::dropEvent(QDropEvent * event) {
    TabBar * copy_parent = this;
    QListWidgetItem * copy_source = 0;
    QListWidgetItem * target_item = 0;

    if ((_internal_move = event -> source() == this)) {
        copy_source = currentItem();
    } else {
        copy_parent = reinterpret_cast<TabBar *>(event -> source());
        copy_source = copy_parent -> currentItem();

        File * file = tabFile(copy_source);

        if (file && _tabs_linkages.contains(file -> uid())) {
            target_item = _tabs_linkages[file -> uid()];
        }
    }

    if (target_item) { // if we already have this file in tabs
        setCurrentItem(target_item);
        event -> accept();
    } else {
        QListWidget::dropEvent(event);
    }

    if (_internal_move)
        delete copy_source;
    else
        emit copy_parent -> tabCloseRequested(copy_source);

    _internal_move = false;
}

//QMimeData * TabBar::mimeData(const QList<QListWidgetItem *> items) const {
//    QMimeData * data = QListWidget::mimeData(items);

////    data -> setParent(this);

//    qDebug() << data -> parent();

//    return data;
//}

bool TabBar::dropMimeData(int index, const QMimeData * data, Qt::DropAction action) {
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

void TabBar::itemCloseRequested(const QModelIndex & index) {
    QListWidgetItem * item = itemFromIndex(index);

    if (item)
        emit tabCloseRequested(item);
}

void TabBar::scrollUpdated(int /*min*/, int max) {
    if (hscroll_range == -1 || (hscroll_range == 0 && max > 0) || (hscroll_range > 0 && max == 0))
        emit scrollsRequired(max > 0);

    hscroll_range = max;
}

void TabBar::scrollForward() {
    horizontalScrollBar() -> triggerAction(QAbstractSlider::SliderSingleStepAdd);
}
void TabBar::scrollBackward() {
    horizontalScrollBar() -> triggerAction(QAbstractSlider::SliderSingleStepSub);
}

