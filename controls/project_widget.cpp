#include "project_widget.h"

#include <qtoolbar.h>
#include <qlayout.h>
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
#include "debugging/debug.h"
#include "debugging/debug_stub_interface.h"

ProjectWidget::ProjectWidget(const QString & path, const int & cmd_type, QWidget * parent)
    : QWidget(parent), _path(path), _cmd_type(cmd_type), _debug_bar(nullptr), _breakpoints(nullptr), _logger(nullptr)
{
    RunConfig run_config = RunConfig(cmd_type);

    QHBoxLayout * l = new QHBoxLayout(this);
    l -> setContentsMargins(1, 1, 1, 1);
//    l -> setSpacing(2);
    QSplitter * splitter = new QSplitter(this);

    splitter -> setStyleSheet(
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
        auto addExtraSeparator = [](QToolBar * bar) {
            QWidget * empty = new QWidget(bar);
            empty -> setFixedSize(3, 3);
            bar -> addWidget(empty);
        };

        _debug_bar = new QToolBar(this);
        _debug_bar -> setOrientation(Qt::Vertical);
        _debug_bar -> setIconSize(QSize(20, 20));
        _debug_bar -> setFixedWidth(34);
    //    debug_bar -> setContentsMargins(1, 1, 1, 1);

        QAction * run_btn = _debug_bar -> addAction(QIcon(QLatin1Literal(":/tools/run")), QLatin1Literal());
        run_btn -> setEnabled(false);
        addExtraSeparator(_debug_bar);

    //    connect(_color_picker, &QAction::triggered, [=]() { color_picker_widget -> setVisible(!color_picker_widget -> isVisible()); _color_picker -> setChecked(color_picker_widget -> isVisible()); });

        QAction * run_debug_btn = _debug_bar -> addAction(QIcon(QLatin1Literal(":/tools/debug")), QLatin1Literal());
    //    debug_bar -> widgetForAction(run_debug_btn) -> setContentsMargins(2,2,2,2);
        run_debug_btn -> setEnabled(false);

        _debug_bar -> addSeparator();

        QAction * debug_step_over_btn = _debug_bar -> addAction(QIcon(QLatin1Literal(":/tools/step_over")), QLatin1Literal());
        debug_step_over_btn -> setToolTip(QLatin1Literal("Step to next line"));
        debug_step_over_btn -> setEnabled(false);
        addExtraSeparator(_debug_bar);

        QAction * debug_step_into_btn = _debug_bar -> addAction(QIcon(QLatin1Literal(":/tools/step_into")), QLatin1Literal());
        debug_step_into_btn -> setToolTip(QLatin1Literal("Step into object"));
        debug_step_into_btn -> setEnabled(false);
        addExtraSeparator(_debug_bar);

        QAction * debug_step_out_btn = _debug_bar -> addAction(QIcon(QLatin1Literal(":/tools/step_out")), QLatin1Literal());
        debug_step_out_btn -> setToolTip(QLatin1Literal("Step out from object"));
        debug_step_out_btn -> setEnabled(false);
        addExtraSeparator(_debug_bar);

        l -> addWidget(_debug_bar);

        _debug_panel = new DebugPanel(this);

        connect(&BreakpointsController::obj(), &BreakpointsController::activateBreakpoint, _debug_panel, &DebugPanel::activate);
        connect(&BreakpointsController::obj(), &BreakpointsController::deactivate, _debug_panel, &DebugPanel::deactivate);

        splitter -> addWidget(_debug_panel);

        DebugStubInterface * handler = new DebugStubInterface();
        Debug::obj().setupHandler(handler);
    }

    _logger = new QPlainTextEdit(this);

    splitter -> addWidget(_logger);

    l -> addWidget(splitter);
}

void ProjectWidget::load(const QJsonObject & obj) {

}

QJsonObject ProjectWidget::save() {
    QJsonObject res;

    res.insert(QLatin1Literal("path"), _path);
    res.insert(QLatin1Literal("cmd_type"), _cmd_type);

//    res.insert(QLatin1Literal("history"), QJsonValue::fromVariant(*history));

    return res;
}

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
