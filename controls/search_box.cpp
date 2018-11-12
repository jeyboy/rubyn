#include "search_box.h"

#include <qevent.h>

SearchBox::SearchBox(QWidget * parent) : QLineEdit(parent) {

}

void SearchBox::keyPressEvent(QKeyEvent * e) {
    switch(e -> key()) {
        case Qt::Key_Escape: { emit editingFinished(); break;}

        default: QLineEdit::keyPressEvent(e);
    }
}

void SearchBox::hideEvent(QHideEvent * e) {
    emit hidden();
    QLineEdit::hideEvent(e);
}
