#include "tab_bar.h"

#include "delegates/tab_bar_item_delegate.h"
#include "project/file.h"

#include <qscrollbar.h>
#include <qmimedata.h>
#include <qevent.h>
#include <qdebug.h>

QColor TabBar::remote_file_color = QColor(255, 0, 0, 48);

TabBar::TabBar(QWidget * parent) : QListWidget(parent), hscroll_range(-1), _internal_move(false) {
//    setStyleSheet(
//        QLatin1String(
//            "QListView::item:selected:!active {"
//            "   background: qlineargradient(x1: 0, y1: 0.5, x2: 0, y2: 1, stop: 0 rgba(177,217,244, .4), stop: 1 rgba(192,224,246, .4));"
//            "}"
//        )
//                "QListView::item:alternate {"
//                "    background: #EEEEEE;"
//                "}"

//                "QListView::item:selected:active {"
//                "   color: #000;"
//                "   background: rgba(141,188,222, .6);"
//                "}"

//                "QListView::item:selected:!active {"
//                "   background: rgba(141,188,222, .3);"
//                "}"

////                "QListView::item:selected:active {"
////                "   color: #000000;"
////                "   background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(126, 192, 238, .5), stop: 1 rgba(113,172,214, .5));"
////                "}"

////                "QListView::item:selected:!active {"
////                "   background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(177,217,244, .8), stop: 1 rgba(192,224,246, .8));"
////                "}"

////                "QListView::item:selected:active {"
////                "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #7ec0ee, stop: 1 #71acd6);"
////                "}"

////                "QListView::item:selected:!active {"
////                "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #b1d9f4, stop: 1 #c0e0f6);"
////                "}"

////                "QListView::item {"
////                "    border-right: 3px dotted #000000;"
////                "    color: #000000;"
////                "}"


////                "QListView::item:selected {"
////                "    border: 1px solid #6a6ea9;"
////                "}"


////                "QListView::item:hover {"
////                "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FAFBFE, stop: 1 #DCDEF1);"
////                "}"
//    );

//    setAlternatingRowColors(true);

    #ifdef Q_OS_LINUX
        setStyleSheet(
            QLatin1String(
                "QListView::item:selected:!active {"
                "   background: qlineargradient(x1: 0, y1: 0.5, x2: 0, y2: 1, stop: 0 rgba(177,217,244, .6), stop: 1 rgba(192,224,246, .8));"
                "   color: #000;"
                "}"
            )
        );
    #endif

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

TabBar::~TabBar() {
    if (!_tabs_linkages . isEmpty()) {
        QHash<QString, QListWidgetItem *>::Iterator tab_it = _tabs_linkages.begin();

        for(; tab_it != _tabs_linkages.end(); tab_it++) {
            if (tab_it.value()) {
                File * file = tabFile(tab_it.value());

                if (file) {
                    file -> decOpened();
                }
            }
        }
    }
}

QListWidgetItem * TabBar::addTab(const QIcon & ico, const QString & text) {
    QListWidgetItem * item = new QListWidgetItem(ico, text);
    addItem(item);
    return item;
}

void TabBar::removeTab(QListWidgetItem * tab) {
    delete tab;
}

File * TabBar::currentTabFile() {
    return tabFile(currentRow());
}

File * TabBar::tabFile(const int & index) {
    if (index < 0) return nullptr;

    QListWidgetItem * itm = item(index);

    return itm ? tabFile(itm) : nullptr;
}

File * TabBar::tabFile(QListWidgetItem * tab) {
    QVariant tab_data = tab -> data(Qt::UserRole);

    if (!tab_data.isNull()) {
        return reinterpret_cast<File *>(tab_data.value<quintptr>());
    }

    return nullptr;
}

Qt::DropActions TabBar::supportedDropActions() const {
    return Qt::MoveAction | Qt::CopyAction;
}

void TabBar::dropEvent(QDropEvent * event) {
    TabBar * copy_parent = this;
    QListWidgetItem * copy_source = nullptr;
    QListWidgetItem * target_item = nullptr;

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

    if (_internal_move) {
        File * file = tabFile(copy_source);

        if (file)
            _tabs_linkages.insert(file -> uid(), currentItem());

        delete copy_source;
    }
    else {
        if (!target_item) {
            target_item = currentItem();

            File * file = tabFile(copy_source);
            file -> incOpened();
            _tabs_linkages.insert(file -> uid(), target_item);

            if (file -> isExternal()) {
                target_item -> setBackground(remote_file_color);
            }
        }

        emit copy_parent -> tabCloseRequested(copy_source);
    }
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

void TabBar::markAsChanged(const QString & uid, const bool & mark) {
    if (_tabs_linkages.contains(uid)) {

        QListWidgetItem * item = _tabs_linkages[uid];

        QString curr_text = item -> text();

        if (mark) {
            if (!curr_text.startsWith('*'))
                curr_text.prepend('*');
            else
                return;
        }
        else {
            if (curr_text.startsWith('*'))
                curr_text.remove(0, 1);
            else
                return;
        }

        item -> setText(curr_text);
    }
}

