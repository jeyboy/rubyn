#ifndef CONSOLE_WIDGET_H
#define CONSOLE_WIDGET_H

#include "tools/process.h"
#include "loggers/basic_logger.h"

class ConsoleWidget : public BasicLogger {
    Q_OBJECT

    Process * process;
public:
    ConsoleWidget(const QJsonObject & json, QWidget * parent = nullptr);
    explicit ConsoleWidget(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd = QString(), QWidget * parent = nullptr, QStringList * history_list = nullptr);
    ~ConsoleWidget();
    void output(const QString & txt);
    void scrollDown();

    QJsonObject save();
protected:
    void setup(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd, QStringList * history_list);

    void keyPressEvent(QKeyEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void contextMenuEvent(QContextMenuEvent * e);
private:
    QString cmd_command;
    QString cmd_path;
    QString prompt;
    bool is_locked;
    QStringList * history;
    QStringList queue;
    int history_pos;

    void onEnter();
    void insertPrompt(const bool & insert_new_block = true);
    void historyAdd(const QString & cmd);
    void historyBack();
    void historyForward();

    void onCommand(const QString & cmd);

signals:
    void onChange(const QString & cmd);
};

#endif // CONSOLE_WIDGET_H
