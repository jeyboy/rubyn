#include "run_configuration.h"

#include <qtoolbar.h>
#include <qcombobox.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qdebug.h>
#include <qmenu.h>

RunConfiguration::RunConfiguration(QObject * parent) : QObject(parent), _run_menu(nullptr), _debbug_menu(nullptr), _run(nullptr), _debbug(nullptr), _console_btn(nullptr) {

}

void RunConfiguration::buildPanel(QToolBar * bar) {
    auto addExtraSeparator = [](QToolBar * bar) {
        QWidget * empty = new QWidget(bar);
        empty -> setFixedSize(3, 3);
        bar -> addWidget(empty);
    };

    _run = new QToolButton(bar);
    _run -> setIcon(QIcon(QLatin1Literal(":/tools/run")));
    _run -> setPopupMode(QToolButton::InstantPopup);

    _run_menu = new QMenu(_run);

    _run_menu -> addAction(QIcon(QLatin1Literal(":/tools/run_config")), QLatin1Literal("Configure"), this, SLOT("configure()"));

    _run -> setMenu(_run_menu);

//    _run -> setDisabled(true);

    bar -> addWidget(_run);

    addExtraSeparator(bar);


    _debbug = new QToolButton(bar);
    _debbug -> setIcon(QIcon(QLatin1Literal(":/tools/debug")));
    _debbug -> setPopupMode(QToolButton::InstantPopup);

    _debbug_menu = new QMenu(_debbug);
    _debbug_menu -> addAction(QIcon(QLatin1Literal(":/tools/run_config")), QLatin1Literal("Configure"), this, SLOT("configure()"));

    _debbug -> setMenu(_debbug_menu);
//    _debbug -> setDisabled(true);

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

void RunConfiguration::configure() {

}

void RunConfiguration::projectAdded(const QString & path) {
//    _run -> setDisabled(true);
//    _debbug -> setDisabled(true);
}
void RunConfiguration::projectRemoved(const QString & path) {

}
