#ifndef RUN_CONFIGURATION_H
#define RUN_CONFIGURATION_H

#include <qobject.h>

class QToolBar;
class QComboBox;
class QAction;
class QToolButton;
class QMenu;

class RunConfiguration : public QObject {
    Q_OBJECT

    QMenu * _run_menu;
    QMenu * _debbug_menu;

    QToolButton * _run;
    QToolButton * _debbug;
    QToolButton * _console_btn;
public:
    RunConfiguration(QObject * parent = nullptr);

    void buildPanel(QToolBar * bar);

protected slots:
    void configure();

public slots:
    void projectAdded(const QString &);
    void projectRemoved(const QString &);
};

#endif // RUN_CONFIGURATION_H
