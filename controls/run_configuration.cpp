#include "run_configuration.h"

#include <qtoolbar.h>
#include <qcombobox.h>

RunConfiguration::RunConfiguration(QObject * parent)
    : QObject(parent), _config_list(0), _run(0), _disabled_run(0), _debbug(0), _disabled_debbug(0)
{

}

void RunConfiguration::buildPanel(QToolBar * bar) {
    _config_list = new QComboBox(bar);

    _config_list -> addItem(QIcon(QLatin1Literal(":/tools/run_config")), QLatin1Literal("Add new"));

    connect(_config_list, SIGNAL(currentIndexChanged(int)), this, SLOT(configSelectionChanged(int)));

    bar -> addWidget(_config_list);

    _run = bar -> addAction(QIcon(QLatin1Literal(":/tools/play")), QLatin1Literal());
    _run -> setVisible(false);

    _disabled_run = bar -> addAction(QIcon(QLatin1Literal(":/tools/play_off")), QLatin1Literal());

    _debbug = bar -> addAction(QIcon(QLatin1Literal(":/tools/start_bug")), QLatin1Literal());
    _debbug -> setVisible(false);

    _disabled_debbug = bar -> addAction(QIcon(QLatin1Literal(":/tools/start_bug_off")), QLatin1Literal());
}

void RunConfiguration::configSelectionChanged(int index) {
    QVariant data = _config_list -> itemData(index);

    if (data.isNull()) {
        // TODO: show modal for new config
    } else {
        // TODO: update buttons state
    }
}
