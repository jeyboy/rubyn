#include "line_dialog.h"

#include "qlineedit.h"

LineDialog::LineDialog(QWidget * parent) : QDialog(parent) {
    input = new QLineEdit(this);
}

void LineDialog::setLineNumber(const qint64 & val) {
    input -> setText(QString::number(val));
}

qint64 LineDialog::lineNumber() {
    return input -> text().toLongLong();
}

