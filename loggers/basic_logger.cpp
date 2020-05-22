#include "basic_logger.h"

BasicLogger::BasicLogger(QWidget * parent) : QPlainTextEdit(parent) {
    setReadOnly(true);
    textCursor().insertText("-------------- *** ----------------");
}

void BasicLogger::setReadOnly(const bool & read_only) {
    QPlainTextEdit::setReadOnly(read_only);
}

void BasicLogger::printAlert(const QString & msg) {
    textCursor().insertBlock();
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(212, 175, 55));
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(msg);
}

void BasicLogger::printNotify(const QString & msg) {
    textCursor().insertBlock();
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 155, 0));
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(msg);
}

void BasicLogger::printText(const QString & msg) {
    textCursor().insertBlock();
    QTextCharFormat format;
    format.setForeground(Qt::black);
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(msg);
}

void BasicLogger::printError(const QString & msg) {
    textCursor().insertBlock();
    QTextCharFormat format;
    format.setForeground(Qt::red);
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(msg);
}
