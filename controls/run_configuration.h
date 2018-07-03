#ifndef RUN_CONFIGURATION_H
#define RUN_CONFIGURATION_H

#include <qobject.h>

class QToolBar;
class QComboBox;
class QAction;

class RunConfiguration : public QObject {
    Q_OBJECT

    QComboBox * _config_list;

    QAction * _run;
    QAction * _disabled_run;

    QAction * _debbug;
    QAction * _disabled_debbug;
public:
    RunConfiguration(QObject * parent = 0);

    void buildPanel(QToolBar * bar);

protected slots:
    void configSelectionChanged(int index);
};

#endif // RUN_CONFIGURATION_H
