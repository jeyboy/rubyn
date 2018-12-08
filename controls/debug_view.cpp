#include "debug_view.h"

#include <qevent.h>

DebugView::DebugView(QWidget * parent) : QTreeWidget(parent) {
//    connect(model(), &QAbstractItemModel::rowsInserted, this, &DebugView::modelRowsInserted);
//    connect(model(), &QAbstractItemModel::rowsRemoved, this, &DebugView::modelRowsRemoved);
}

void DebugView::mouseDoubleClickEvent(QMouseEvent * event) {
    if (!itemAt(event -> pos()))
        emit newItemRequired();

    QTreeWidget::mouseDoubleClickEvent(event);
}

//void DebugView::modelRowsInserted(const QModelIndex & /*parent*/, int /*first*/, int /*last*/) {
//    if (model() -> rowCount() > 0)
//        emit hasData();
//    else
//        emit hasNoData();
//}
//void DebugView::modelRowsRemoved(const QModelIndex & /*parent*/, int /*first*/, int /*last*/) {
//    if (model() -> rowCount() > 0)
//        emit hasData();
//    else
//        emit hasNoData();
//}
