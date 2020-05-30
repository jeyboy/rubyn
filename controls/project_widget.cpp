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

#include "loggers/basic_logger.h"
#include "tools/process.h"
#include "misc/run_config.h"
#include "controls/debug_panel.h"
#include "controls/dock_widget.h"
#include "debugging/debug.h"
#include "debugging/debug_stub_interface.h"

ProjectWidget::ProjectWidget(RunConfig * conf, QWidget * parent)
    : QWidget(parent), _conf(conf), _splitter(nullptr), _breakpoints(nullptr), _logger(nullptr), _process(nullptr)
{
    setObjectName("widget_" % conf -> token());

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

    if (conf -> cmd_type & RunConfig::rc_debug) {
        _debug_panel = new DebugPanel(this);

        connect(&BreakpointsController::obj(), &BreakpointsController::activateBreakpoint, _debug_panel, &DebugPanel::activate);
        connect(&BreakpointsController::obj(), &BreakpointsController::deactivate, _debug_panel, &DebugPanel::deactivate);

        _splitter -> addWidget(_debug_panel);

        DebugStubInterface * handler = new DebugStubInterface();
        Debug::obj().setupHandler(handler);
    }

    _logger = new BasicLogger(this);

    _splitter -> addWidget((QWidget *)_logger);

//    l -> addWidget(_debug_bar);
    l -> addWidget(_splitter);
}

ProjectWidget::~ProjectWidget() {
    delete _conf;
}

void ProjectWidget::initButtons(DockWidget * cntr) {
    if (_conf -> cmd_type & RunConfig::rc_debug) {
        QToolButton * btn;

        btn = cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/step_out")), this, SLOT(stepOut()), -1);
        btn -> setToolTip(QLatin1Literal("Step out from object"));

        btn = cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/step_into")), this, SLOT(stepInto()), -1);
        btn -> setToolTip(QLatin1Literal("Step into object"));

        btn = cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/step_over")), this, SLOT(stepOver()), -1);
        btn -> setToolTip(QLatin1Literal("Step to next line"));

        cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/debug")), this, SLOT(debug()), -1);
    } else {
        cntr -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/run2")), this, SLOT(run()), -1);
    }
}

void ProjectWidget::load(const QJsonObject & obj) {
    _splitter -> restoreState(QByteArray::fromBase64(obj.value(QLatin1Literal("splitter_state")).toString().toLatin1()));
}

QJsonObject ProjectWidget::save() {
    QJsonObject res = _conf -> toJson();

    res.insert(QLatin1Literal("splitter_state"), QLatin1String(_splitter -> saveState().toBase64()));

    return res;
}

void ProjectWidget::run() {
    _process = new Process(this);
    _process -> bindOutput(_logger);
    _process -> setWorkingDirectory(_conf -> work_dir);
    _process -> setEnvironment(_conf -> env_variables);

    _process -> proc(_conf -> runCmd());
}
void ProjectWidget::debug() {}

void ProjectWidget::stepOver() {}
void ProjectWidget::stepInto() {}
void ProjectWidget::stepOut() {}


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
