#include "debug_view.h"

#include <qevent.h>

DebugView::DebugView(QWidget * parent) : QTreeWidget(parent) {

}

void DebugView::mouseDoubleClickEvent(QMouseEvent * event) {
    if (!itemAt(event -> pos()))
        emit newItemRequired();

    QTreeWidget::mouseDoubleClickEvent(event);
}
