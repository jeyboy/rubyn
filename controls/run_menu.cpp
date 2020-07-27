#include "run_menu.h"

#include <qtoolbar.h>
#include <qcombobox.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qdebug.h>
#include <qmenu.h>

#include "misc/run_config.h"

RunMenu::RunMenu(QObject * parent) : QObject(parent), _run_menu(nullptr), _debbug_menu(nullptr), _run(nullptr), _debbug(nullptr), _console_btn(nullptr) {

}

void RunMenu::buildPanel(QToolBar * bar) {
    auto addExtraSeparator = [](QToolBar * bar) {
        QWidget * empty = new QWidget(bar);
        empty -> setFixedSize(3, 3);
        bar -> addWidget(empty);
    };

    _run = new QToolButton(bar);
    _run -> setIcon(QIcon(QLatin1Literal(":/tools/run2")));
    _run -> setPopupMode(QToolButton::InstantPopup);

    _run_menu = new QMenu(_run);

    _run_menu -> addAction(QIcon(QLatin1Literal(":/tools/run_config")), QLatin1Literal("Configure"), this, &RunMenu::configure);

    _run_menu -> addSeparator();

    _run -> setMenu(_run_menu);

    bar -> addWidget(_run);

    addExtraSeparator(bar);


    _debbug = new QToolButton(bar);
    _debbug -> setIcon(QIcon(QLatin1Literal(":/tools/debug")));
    _debbug -> setPopupMode(QToolButton::InstantPopup);

    _debbug_menu = new QMenu(_debbug);
    _debbug_menu -> addAction(QIcon(QLatin1Literal(":/tools/run_config")), QLatin1Literal("Configure"), this, &RunMenu::configure);
    _debbug_menu -> addSeparator();

    _debbug -> setMenu(_debbug_menu);

    bar -> addWidget(_debbug);

    addExtraSeparator(bar);

//    _console_btn = new QToolButton(bar);
//    _console_btn -> setIcon(QIcon(QLatin1Literal(":/tools/console")));
//    _console_btn -> setPopupMode(QToolButton::InstantPopup);


//    QAction * console_btn_cfg = new QAction(QIcon(QLatin1Literal(":/tools/run_config")), "Configure", bar);
//    _console_btn -> addAction(console_btn_cfg);

//    QAction * bla = bar -> addWidget(_console_btn);
//    bla -> setDisabled(true);




//    bar -> layout() -> itemAt(bar -> layout() -> count() - 1) -> setAlignment(Qt::AlignJustify);

//    QLayout * lay = bar -> layout();
//    for(int i = 0; i < lay -> count(); ++i) {
//        QLayoutItem * it = lay -> itemAt(i);
//        QToolButton * btn = qobject_cast<QToolButton *>(it -> widget());

//        if (btn)
//            it -> setAlignment(Qt::AlignJustify);
//    }
}

void RunMenu::run() {
    QAction * act = qobject_cast<QAction *>(sender());

    RunConfig * conf = new RunConfig((RunConfig::CmdType)act -> property("type").toInt());

    conf -> name = act -> text();
    conf -> work_dir = act -> property("dir").toString();

    emit runRequires(conf);
}

void RunMenu::configure() {

}

void RunMenu::projectAdded(const uint & project_id, const QString & path, const QString & name) {
    QAction * act = _run_menu -> addAction(QIcon(QLatin1Literal(":/tools/run2")), name, this, &RunMenu::run);
    act -> setProperty("dir", path);
    act -> setProperty("type", RunConfig::rc_rails_server);
    act -> setProperty("uid", project_id);

    act = _debbug_menu -> addAction(QIcon(QLatin1Literal(":/tools/debug")), name, this, &RunMenu::run);
    act -> setProperty("dir", path);
    act -> setProperty("type", RunConfig::rc_rails_server_debug);
    act -> setProperty("uid", project_id);
}

void RunMenu::projectRemoved(const uint & project_id, const QString & path) {
    QList<QAction *> lst = _run_menu -> findChildren<QAction *>();

    for(QList<QAction *>::Iterator it = lst.begin(); it != lst.end(); it++) {
        if ((*it) -> property("uid").toUInt() == project_id) {
            _run_menu -> removeAction((*it));
            break;
        }
    }

    lst = _debbug_menu -> findChildren<QAction *>();

    for(QList<QAction *>::Iterator it = lst.begin(); it != lst.end(); it++) {
        if ((*it) -> property("uid").toUInt() == project_id) {
            _debbug_menu -> removeAction((*it));
            break;
        }
    }
}
