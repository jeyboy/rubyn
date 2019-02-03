#include "console_widget.h"

#include <qevent.h>
#include <qtextobject.h>
#include <qscrollbar.h>
#include <qjsonobject.h>

ConsoleWidget::ConsoleWidget(const QJsonObject & json) : is_locked(false), history_pos(0) {
    bool read_only = json.value(QLatin1Literal("read_only")).toBool();
    QString cmd = json.value(QLatin1Literal("cmd_command")).toString();
    QString path = json.value(QLatin1Literal("cmd_path")).toString();
    QString def_prompt = json.value(QLatin1Literal("prompt")).toString();
    QStringList * history_list = new QStringList(json.value(QLatin1Literal("history")).toVariant().toStringList());

    setup(read_only, path, def_prompt, cmd, history_list);
}

ConsoleWidget::ConsoleWidget(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd, QWidget * parent, QStringList * history_list) : QPlainTextEdit(parent), process(nullptr), is_read_only(read_only), cmd_command(cmd), cmd_path(path), is_locked(false), history_pos(0) {
    setup(read_only, path, def_prompt, cmd, history_list);
}

void ConsoleWidget::setup(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd, QStringList * history_list) {
    process = new Process(this);

    prompt = def_prompt + QLatin1Literal("> ");
    history = history_list ? history_list : read_only ? nullptr : new QStringList;

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);

    if (history)
        history_pos = history -> length();

    insertPrompt(false);

    onCommand(cmd);
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

    if(key == Qt::Key_Return && mods == Qt::NoModifier)
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
//    int pos = textCursor().position();

//    QPlainTextEdit::mouseDoubleClickEvent(e);

//    QTextCursor c = textCursor();
//    c.setPosition(pos);

//    setTextCursor(c);
}

void ConsoleWidget::contextMenuEvent(QContextMenuEvent *) {

}

void ConsoleWidget::onEnter() {
    QString cmd = textCursor().block().text().mid(prompt.length());

    if (!cmd.isEmpty()) {
        is_locked = true;

        historyAdd(cmd);

        emit onCommand(cmd);
    }

    insertPrompt();
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
    vbar -> setValue(vbar -> maximum());
}

QJsonObject ConsoleWidget::save() {
    QJsonObject res;

    res.insert(QLatin1Literal("read_only"), is_read_only);
    res.insert(QLatin1Literal("cmd_command"), cmd_command);
    res.insert(QLatin1Literal("cmd_path"), cmd_path);
    res.insert(QLatin1Literal("prompt"), prompt.mid(0, prompt.length() - 2));

    res.insert(QLatin1Literal("history"), QJsonValue::fromVariant(*history));

    return res;
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

void ConsoleWidget::onCommand(const QString & cmd) {
    if (process -> state() == QProcess::NotRunning) {
        process -> start(cmd_path + '/' + cmd);
    } else {
        queue.append(cmd_path + '/' + cmd);
    }
}
