#include "run_configuration.h"

#include <qtoolbar.h>
#include <qcombobox.h>

RunConfiguration::RunConfiguration(QObject * parent) : QObject(parent), _config_list(0), _run(0), _debbug(0) {

}

void RunConfiguration::buildPanel(QToolBar * bar) {
    _config_list = new QComboBox(bar);

    _config_list -> addItem(QIcon(QLatin1Literal(":/tools/run_config")), QLatin1Literal("Add new"));

    connect(_config_list, SIGNAL(currentIndexChanged(int)), this, SLOT(configSelectionChanged(int)));

    bar -> addWidget(_config_list);

    _run = bar -> addAction(QIcon(QLatin1Literal(":/tools/run")), QLatin1Literal());
    _run -> setDisabled(true);

    _debbug = bar -> addAction(QIcon(QLatin1Literal(":/tools/debug")), QLatin1Literal());
    _debbug -> setDisabled(true);
}

void RunConfiguration::configSelectionChanged(int index) {
    QVariant data = _config_list -> itemData(index);

    if (data.isNull()) {
        // TODO: show modal for new config
    } else {
        // TODO: update buttons state
    }
}
