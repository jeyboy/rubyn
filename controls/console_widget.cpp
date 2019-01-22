#include "console_widget.h"

#include <qevent.h>
#include <qtextobject.h>
#include <qscrollbar.h>

ConsoleWidget::ConsoleWidget(const QString & path, QWidget * parent) : QPlainTextEdit(parent), is_locked(false), history(new QStringList), history_pos(0) {
    prompt = path + QLatin1Literal("> ");

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);

    insertPrompt(false);
}

void ConsoleWidget::keyPressEvent(QKeyEvent * e) {
    if(is_locked)
        return;

    const int key = e -> key();
    Qt::KeyboardModifiers mods = e->modifiers();

    if(key >= 0x20 && key <= 0x7e && (mods == Qt::NoModifier || mods == Qt::ShiftModifier))
        QPlainTextEdit::keyPressEvent(e);

    if(key == Qt::Key_Backspace && mods == Qt::NoModifier && textCursor().positionInBlock() > prompt.length())
        QPlainTextEdit::keyPressEvent(e);

    if(key == Qt::Key_Return && key == Qt::NoModifier)
        onEnter();

    if(key == Qt::Key_Up && mods == Qt::NoModifier)
        historyBack();

    if(key == Qt::Key_Down && mods == Qt::NoModifier)
        historyForward();

    QString cmd = textCursor().block().text().mid(prompt.length());
    emit onChange(cmd);
}

void ConsoleWidget::mousePressEvent(QMouseEvent *) {
    setFocus();
}

void ConsoleWidget::mouseDoubleClickEvent(QMouseEvent * e) {
    QPlainTextEdit::mouseDoubleClickEvent(e);
}

void ConsoleWidget::contextMenuEvent(QContextMenuEvent *) {

}

void ConsoleWidget::onEnter() {
    if(textCursor().positionInBlock() == prompt.length()) {
        insertPrompt();
        return;
    }

    QString cmd = textCursor().block().text().mid(prompt.length());
    is_locked = true;

    historyAdd(cmd);

    emit onCommand(cmd);
}

void ConsoleWidget::output(const QString & txt) {
    textCursor().insertBlock();

    QTextCharFormat format;
    format.setForeground(Qt::white);
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(txt);

    insertPrompt();

    is_locked = false;
}

void ConsoleWidget::insertPrompt(const bool & insert_new_block) {
    if(insert_new_block)
        textCursor().insertBlock();

    QTextCharFormat format;
    format.setForeground(Qt::green);
    textCursor().setBlockCharFormat(format);
    textCursor().insertText(prompt);

    scrollDown();
}

void ConsoleWidget::scrollDown() {
    QScrollBar * vbar = verticalScrollBar();
    vbar->setValue(vbar->maximum());
}

void ConsoleWidget::historyAdd(const QString & cmd) {
    history -> append(cmd);
    history_pos = history -> length();
}

void ConsoleWidget::historyBack() {
    if(!history_pos)
        return;

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(prompt + history -> at(--history_pos));
    setTextCursor(cursor);
}

void ConsoleWidget::historyForward() {
    if(history_pos == history -> length())
        return;

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();

    if(history_pos == history -> length() - 1)
        cursor.insertText(prompt);
    else
        cursor.insertText(prompt + history -> at(+history_pos));

    setTextCursor(cursor);
}
