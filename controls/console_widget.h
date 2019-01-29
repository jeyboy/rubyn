#ifndef CONSOLE_WIDGET_H
#define CONSOLE_WIDGET_H

#include <qplaintextedit.h>

#include "tools/process.h"

class ConsoleWidget : public QPlainTextEdit {
    Q_OBJECT

    Process * process;
public:
    explicit ConsoleWidget(const bool & read_only, const QString & path, const QString & def_prompt, const QString & cmd = QString(), QWidget * parent = nullptr, QStringList * history_list = nullptr);
    void output(const QString & txt);
    void scrollDown();

    QJsonObject save();
protected:
    void keyPressEvent(QKeyEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void contextMenuEvent(QContextMenuEvent * e);
private:
    bool is_read_only;
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
