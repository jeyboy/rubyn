#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <qdialog.h>

class QLineEdit;

class LineDialog : public QDialog {
    Q_OBJECT

    QLineEdit * input;
public:
    LineDialog(QWidget * parent = Q_NULLPTR);

    void setLineNumber(const qint64 & val);
    qint64 lineNumber();
};

#endif // LINEDIALOG_H
