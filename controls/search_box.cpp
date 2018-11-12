#include "search_box.h"

#include <qevent.h>

SearchBox::SearchBox(QWidget * parent) : QLineEdit(parent) {
//    setFixedWidth(QWIDGETSIZE_MAX);
    setMinimumSize(0, 0);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void SearchBox::keyPressEvent(QKeyEvent * e) {
    switch(e -> key()) {
        case Qt::Key_Escape: { emit returnPressed(); break;}

        default: QLineEdit::keyPressEvent(e);
    }
}

void SearchBox::hideEvent(QHideEvent * e) {
    emit hidden();
    QLineEdit::hideEvent(e);
}

QSize SearchBox::sizeHint() const {
    return QLineEdit::sizeHint() + QSize(9999, 0);
}
