#include "run_configuration.h"

#include <qtoolbar.h>
#include <qcombobox.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qdebug.h>

RunConfiguration::RunConfiguration(QObject * parent) : QObject(parent), _config_list(nullptr), _run(nullptr), _debbug(nullptr) {

}

void RunConfiguration::buildPanel(QToolBar * bar) {
    auto addExtraSeparator = [](QToolBar * bar) {
        QWidget * empty = new QWidget(bar);
        empty -> setFixedSize(3, 3);
        bar -> addWidget(empty);
    };


    _config_list = new QComboBox(bar);

    _config_list -> addItem(QLatin1Literal("None"));
    _config_list -> addItem(QIcon(QLatin1Literal(":/tools/run_config")), QLatin1Literal("Add new"), QVariant::fromValue(QByteArrayLiteral("+")));

    connect(_config_list, SIGNAL(currentIndexChanged(int)), this, SLOT(configSelectionChanged(int)));

    bar -> addWidget(_config_list);
    addExtraSeparator(bar);

    _run = bar -> addAction(QIcon(QLatin1Literal(":/tools/run")), QLatin1Literal());
    _run -> setDisabled(true);
    addExtraSeparator(bar);

    _debbug = bar -> addAction(QIcon(QLatin1Literal(":/tools/debug")), QLatin1Literal());
    _debbug -> setDisabled(true);
    addExtraSeparator(bar);

    bar -> addSeparator();

    _console_btn = new QToolButton(bar);
    _console_btn -> setIcon(QIcon(QLatin1Literal(":/tools/console")));
    _console_btn -> setPopupMode(QToolButton::InstantPopup);


    QAction * console_btn_cfg = new QAction(QIcon(QLatin1Literal(":/tools/run_config")), "Configure", bar);
    _console_btn -> addAction(console_btn_cfg);

    QAction * bla = bar -> addWidget(_console_btn);
    bla -> setDisabled(true);




    bar -> layout() -> itemAt(bar -> layout() -> count() - 1) -> setAlignment(Qt::AlignJustify);

//    QLayout * lay = bar -> layout();
//    for(int i = 0; i < lay -> count(); ++i) {
//        QLayoutItem * it = lay -> itemAt(i);
//        QToolButton * btn = qobject_cast<QToolButton *>(it -> widget());

//        if (btn)
//            it -> setAlignment(Qt::AlignJustify);
//    }
}

void RunConfiguration::configSelectionChanged(int index) {
    QVariant data = _config_list -> itemData(index);

    if (data.isNull()) {
        // TODO: disable all buttons
    } else {
        QByteArray udata = data.toByteArray();

        if (udata == QByteArrayLiteral("+")) {
            // TODO: show modal for new config
        } else {
            // TODO: update buttons state
        }
    }
}
