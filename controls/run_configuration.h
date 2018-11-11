#ifndef RUN_CONFIGURATION_H
#define RUN_CONFIGURATION_H

#include <qobject.h>

class QToolBar;
class QComboBox;
class QAction;
class QToolButton;

class RunConfiguration : public QObject {
    Q_OBJECT

    QComboBox * _config_list;

    QAction * _run;
    QAction * _debbug;
    QToolButton * _console_btn;
public:
    RunConfiguration(QObject * parent = 0);

    void buildPanel(QToolBar * bar);

protected slots:
    void configSelectionChanged(int index);
};

#endif // RUN_CONFIGURATION_H
