#include "project_widget.h"

//#include <qtoolbar.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include <qsplitter.h>
#include <qplaintextedit.h>

//#include <qevent.h>
//#include <qtextobject.h>
//#include <qscrollbar.h>
//#include <qjsonobject.h>

#include "breakpoints_panel.h"
#include "editor/breakpoints_controller.h"

#include "misc/run_config.h"
#include "controls/debug_panel.h"
#include "controls/dock_widget.h"
#include "debugging/debug.h"
#include "debugging/debug_stub_interface.h"

ProjectWidget::ProjectWidget(const QString & path, const int & cmd_type, QWidget * parent)
    : QWidget(parent), _path(path), _cmd_type(cmd_type), _splitter(nullptr), _breakpoints(nullptr), _logger(nullptr)
{
    RunConfig run_config = RunConfig(_cmd_type);
    setObjectName("widget_" % QString::number(cmd_type) % '|' % path);

    QHBoxLayout * l = new QHBoxLayout(this);
    l -> setContentsMargins(1, 1, 1, 1);
    l -> setSpacing(0);

    _splitter = new QSplitter(this);
    _splitter -> setObjectName("splitter_" % objectName());

    _splitter -> setStyleSheet(
        QLatin1Literal(
            "QSplitter::handle {"
            "   border: 2px solid #ddd;"
            "   background-color: #555;"
            "   border-radius: 4px;"
            "   background-repeat: no-repeat;"
            "   background-position: center center;"
            "   padding: 1px;"
            "}"

            "QSplitter::handle:vertical {"
            "   background-image: url(:/grape);"
            "}"

            "QSplitter::handle:horizontal {"
            "   background-image: url(:/grape_horizontal);"
            "}"
        )
    );

    if (run_config & rc_debug) {
        _debug_panel = new DebugPanel(this);

        connect(&BreakpointsController::obj(), &BreakpointsController::activateBreakpoint, _debug_panel, &DebugPanel::activate);
        connect(&BreakpointsController::obj(), &BreakpointsController::deactivate, _debug_panel, &DebugPanel::deactivate);

        _splitter -> addWidget(_debug_panel);

        DebugStubInterface * handler = new DebugStubInterface();
        Debug::obj().setupHandler(handler);
    }

    _logger = new QPlainTextEdit(this);

    _splitter -> addWidget(_logger);

//    l -> addWidget(_debug_bar);
    l -> addWidget(_splitter);
}

void ProjectWidget::initButtons(DockWidget * cntr) {
    RunConfig run_config = RunConfig(_cmd_type);

    if (run_config & rc_debug) {
        QToolButton * btn;

        cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/debug")), this, SLOT(debug()), 0);

        btn = cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/step_over")), this, SLOT(stepOver()), 1);
        btn -> setToolTip(QLatin1Literal("Step to next line"));

        btn = cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/step_into")), this, SLOT(stepInto()), 2);
        btn -> setToolTip(QLatin1Literal("Step into object"));

        btn = cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/step_out")), this, SLOT(stepOut()), 3);
        btn -> setToolTip(QLatin1Literal("Step out from object"));
    } else {
        cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/run2")), this, SLOT(run()), 0);
    }
}

void ProjectWidget::load(const QJsonObject & obj) {
    _splitter -> restoreState(QByteArray::fromBase64(obj.value(QLatin1Literal("splitter_state")).toString().toLatin1()));
}

QJsonObject ProjectWidget::save() {
    QJsonObject res;

    res.insert(QLatin1Literal("path"), _path);
    res.insert(QLatin1Literal("cmd_type"), _cmd_type);
    res.insert(QLatin1Literal("splitter_state"), QLatin1String(_splitter -> saveState().toBase64()));

//    res.insert(QLatin1Literal("history"), QJsonValue::fromVariant(*history));

    return res;
}

void ProjectWidget::run() {}
void ProjectWidget::debug() {}

void ProjectWidget::stepOver() {}
void ProjectWidget::stepInto() {}
void ProjectWidget::stepOut() {}

//ProjectWidget::ProjectWidget(const QJsonObject & json) : is_locked(false), history_pos(0) {
//    bool read_only = json.value(QLatin1Literal("read_only")).toBool();
//    QString cmd = json.value(QLatin1Literal("cmd_command")).toString();
//    QString path = json.value(QLatin1Literal("cmd_path")).toString();
//    QString def_prompt = json.value(QLatin1Literal("prompt")).toString();
//    QStringList * history_list = new QStringList(json.value(QLatin1Literal("history")).toVariant().toStringList());

//    setup(read_only, path, def_prompt, cmd, history_list);
//}

//ProjectWidget::ProjectWidget(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd, QWidget * parent, QStringList * history_list) : QPlainTextEdit(parent), process(nullptr), is_read_only(read_only), cmd_command(cmd), cmd_path(path), is_locked(false), history_pos(0) {
//    setup(read_only, path, def_prompt, cmd, history_list);
//}

//void ProjectWidget::setup(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd, QStringList * history_list) {
//    process = new Process(this);

//    prompt = def_prompt + QLatin1Literal("> ");
//    history = history_list ? history_list : read_only ? nullptr : new QStringList;

//    QPalette p = palette();
//    p.setColor(QPalette::Base, Qt::black);
//    p.setColor(QPalette::Text, Qt::green);
//    setPalette(p);

//    if (history)
//        history_pos = history -> length();

//    insertPrompt(false);

//    onCommand(cmd);
//}

//void ProjectWidget::keyPressEvent(QKeyEvent * e) {
//    if(is_locked)
//        return;

//    const int key = e -> key();
//    Qt::KeyboardModifiers mods = e->modifiers();

//    if(key >= 0x20 && key <= 0x7e && (mods == Qt::NoModifier || mods == Qt::ShiftModifier))
//        QPlainTextEdit::keyPressEvent(e);

//    if(key == Qt::Key_Backspace && mods == Qt::NoModifier && textCursor().positionInBlock() > prompt.length())
//        QPlainTextEdit::keyPressEvent(e);

//    if(key == Qt::Key_Return && mods == Qt::NoModifier)
//        onEnter();

//    if(key == Qt::Key_Up && mods == Qt::NoModifier)
//        historyBack();

//    if(key == Qt::Key_Down && mods == Qt::NoModifier)
//        historyForward();

//    QString cmd = textCursor().block().text().mid(prompt.length());
//    emit onChange(cmd);
//}

//void ProjectWidget::mousePressEvent(QMouseEvent *) {
//    setFocus();
//}

//void ProjectWidget::mouseDoubleClickEvent(QMouseEvent * e) {
////    int pos = textCursor().position();

////    QPlainTextEdit::mouseDoubleClickEvent(e);

////    QTextCursor c = textCursor();
////    c.setPosition(pos);

////    setTextCursor(c);
//}

//void ProjectWidget::contextMenuEvent(QContextMenuEvent *) {

//}

//void ProjectWidget::onEnter() {
//    QString cmd = textCursor().block().text().mid(prompt.length());

//    if (!cmd.isEmpty()) {
//        is_locked = true;

//        historyAdd(cmd);

//        emit onCommand(cmd);
//    }

//    insertPrompt();
//}

//void ProjectWidget::output(const QString & txt) {
//    textCursor().insertBlock();

//    QTextCharFormat format;
//    format.setForeground(Qt::white);
//    textCursor().setBlockCharFormat(format);
//    textCursor().insertText(txt);

//    insertPrompt();

//    is_locked = false;
//}

//void ProjectWidget::insertPrompt(const bool & insert_new_block) {
//    if(insert_new_block)
//        textCursor().insertBlock();

//    QTextCharFormat format;
//    format.setForeground(Qt::green);
//    textCursor().setBlockCharFormat(format);
//    textCursor().insertText(prompt);

//    scrollDown();
//}

//void ProjectWidget::scrollDown() {
//    QScrollBar * vbar = verticalScrollBar();
//    vbar -> setValue(vbar -> maximum());
//}

//void ProjectWidget::historyAdd(const QString & cmd) {
//    history -> append(cmd);
//    history_pos = history -> length();
//}

//void ProjectWidget::historyBack() {
//    if(!history_pos)
//        return;

//    QTextCursor cursor = textCursor();
//    cursor.movePosition(QTextCursor::StartOfBlock);
//    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
//    cursor.removeSelectedText();
//    cursor.insertText(prompt + history -> at(--history_pos));
//    setTextCursor(cursor);
//}

//void ProjectWidget::historyForward() {
//    if(history_pos == history -> length())
//        return;

//    QTextCursor cursor = textCursor();
//    cursor.movePosition(QTextCursor::StartOfBlock);
//    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
//    cursor.removeSelectedText();

//    if(history_pos == history -> length() - 1)
//        cursor.insertText(prompt);
//    else
//        cursor.insertText(prompt + history -> at(+history_pos));

//    setTextCursor(cursor);
//}

//void ProjectWidget::onCommand(const QString & cmd) {
//    if (process -> state() == QProcess::NotRunning) {
//        process -> start(cmd_path + '/' + cmd);
//    } else {
//        queue.append(cmd_path + '/' + cmd);
//    }
//}
