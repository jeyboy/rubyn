#include "basic_logger.h"

BasicLogger::BasicLogger(QWidget * parent) : QPlainTextEdit(parent) {
    setReadOnly(true);
}

void BasicLogger::setReadOnly(const bool & read_only) {
    QPlainTextEdit::setReadOnly(read_only);
}

void BasicLogger::printAlert(const QString & msg) {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(212, 175, 55));
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(msg);
}

void BasicLogger::printNotify(const QString & msg) {
    QTextCharFormat format;
    format.setForeground(Qt::green);
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(msg);
}

void BasicLogger::printText(const QString & msg) {
    QTextCharFormat format;
    format.setForeground(Qt::black);
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(msg);
}

void BasicLogger::printError(const QString & msg) {
    QTextCharFormat format;
    format.setForeground(Qt::red);
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(msg);
}
