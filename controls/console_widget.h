#ifndef CONSOLE_WIDGET_H
#define CONSOLE_WIDGET_H

#include <qplaintextedit.h>

class ConsoleWidget : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit ConsoleWidget(const QString & path, QWidget * parent = nullptr);
    void output(const QString & txt);
    void scrollDown();
protected:
    void keyPressEvent(QKeyEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void contextMenuEvent(QContextMenuEvent * e);
private:
    QString prompt;
    bool is_locked;
    QStringList * history;
    int history_pos;

    void onEnter();
    void insertPrompt(const bool & insert_new_block = true);
    void historyAdd(const QString & cmd);
    void historyBack();
    void historyForward();
signals:
    void onCommand(const QString & cmd);
    void onChange(const QString & cmd);
};

#endif // CONSOLE_WIDGET_H
