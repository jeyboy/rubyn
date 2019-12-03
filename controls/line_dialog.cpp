#include "line_dialog.h"

#include "qlineedit.h"

#include <qevent.h>
#include <qlayout.h>
#include <qdebug.h>

LineDialog::LineDialog(QWidget * parent) : QDialog(parent) {
    setWindowTitle("To Line:");



    input = new QLineEdit(this);


}

void LineDialog::setLineNumber(const qint64 & val) {
    input -> setText(QString::number(val));
}

qint64 LineDialog::lineNumber() {
    return qMax(input -> text().toLongLong() - 1, 1LL);
}

void LineDialog::keyPressEvent(QKeyEvent * e) {
    switch(e -> key()) {
        case Qt::Key_Return: {
            done(QDialog::Accepted);
            return;
        }

        case Qt::Key_Escape: {
            done(QDialog::Rejected);
            return;
        }
    }

    QDialog::keyPressEvent(e);
}
