#include "debug_frames_view.h"

#include <qevent.h>

DebugFramesView::DebugFramesView(QWidget * parent) : QTreeWidget(parent) {
//    connect(model(), &QAbstractItemModel::rowsInserted, this, &DebugView::modelRowsInserted);
//    connect(model(), &QAbstractItemModel::rowsRemoved, this, &DebugView::modelRowsRemoved);
}

void DebugFramesView::mouseDoubleClickEvent(QMouseEvent * event) {
    if (!itemAt(event -> pos()))
        emit newItemRequired();

    QTreeWidget::mouseDoubleClickEvent(event);
}

//void DebugFramesView::modelRowsInserted(const QModelIndex & /*parent*/, int /*first*/, int /*last*/) {
//    if (model() -> rowCount() > 0)
//        emit hasData();
//    else
//        emit hasNoData();
//}
//void DebugFramesView::modelRowsRemoved(const QModelIndex & /*parent*/, int /*first*/, int /*last*/) {
//    if (model() -> rowCount() > 0)
//        emit hasData();
//    else
//        emit hasNoData();
//}
