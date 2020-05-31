#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <qwidget.h>
#include <qjsonobject.h>

//#include <qplaintextedit.h>

//#include "tools/process.h"

class QSplitter;
class BreakpointsPanel;
class DebugPanel;
class BasicLogger;
class DockWidget;
class Process;
class RunConfig;
class QToolButton;

class ProjectWidget : public QWidget {
    Q_OBJECT

    RunConfig * _conf;

    QSplitter * _splitter;
    DebugPanel * _debug_panel;
    BreakpointsPanel * _breakpoints;
    BasicLogger * _logger;
    Process * _process;

    QToolButton * _run_btn;
    QToolButton * _stop_btn;
public:
    ProjectWidget(RunConfig * conf, QWidget * parent = nullptr);
    ~ProjectWidget();

    void initButtons(DockWidget * cntr);

    void load(const QJsonObject & obj);
    QJsonObject save();

protected slots:
    void run();
    void debug();
    void stopProcess();

    void stepOver();
    void stepInto();
    void stepOut();


//    ProjectWidget(const QJsonObject & json);
//    explicit ProjectWidget(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd = QString(), QWidget * parent = nullptr, QStringList * history_list = nullptr);
//    void output(const QString & txt);
//    void scrollDown();

//    QJsonObject save();
//protected:
//    void setup(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd, QStringList * history_list);

//    void keyPressEvent(QKeyEvent * e);
//    void mousePressEvent(QMouseEvent * e);
//    void mouseDoubleClickEvent(QMouseEvent * e);
//    void contextMenuEvent(QContextMenuEvent * e);
//private:
//    bool is_read_only;
//    QString cmd_command;
//    QString cmd_path;
//    QString prompt;
//    bool is_locked;
//    QStringList * history;
//    QStringList queue;
//    int history_pos;

//    void onEnter();
//    void insertPrompt(const bool & insert_new_block = true);
//    void historyAdd(const QString & cmd);
//    void historyBack();
//    void historyForward();

//    void onCommand(const QString & cmd);

//signals:
//    void onChange(const QString & cmd);
};

#endif // PROJECT_WIDGET_H
