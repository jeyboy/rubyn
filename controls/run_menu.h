#ifndef RUN_MENU_H
#define RUN_MENU_H

#include <qobject.h>

class QToolBar;
class QComboBox;
class QAction;
class QToolButton;
class QMenu;

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
    void runRequires(const QString & path, const QString & name, const int & run_type);

public slots:
    void projectAdded(const QString & path, const QString & name);
    void projectRemoved(const QString & path);
};

#endif // RUN_MENU_H
