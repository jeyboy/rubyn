#ifndef RUN_MENU_H
#define RUN_MENU_H

#include <qobject.h>

class QToolBar;
class QComboBox;
class QAction;
class QToolButton;
class QMenu;
class RunConfig;

class RunMenu : public QObject {
    Q_OBJECT

    QMenu * _run_menu;
    QMenu * _debbug_menu;

    QToolButton * _run;
    QToolButton * _debbug;
    QToolButton * _console_btn;
public:
    RunMenu(QObject * parent = nullptr);

    void buildPanel(QToolBar * bar);

protected slots:
    void run();
    void configure();

signals:
    void runRequires(RunConfig * conf);

public slots:
    void projectAdded(const uint & project_id, const QString & path, const QString & name);
    void projectRemoved(const uint & project_id, const QString & path);
};

#endif // RUN_MENU_H
