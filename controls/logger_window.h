#ifndef LOGGER_WINDOW_H
#define LOGGER_WINDOW_H

#include <qplaintextedit.h>

class LoggerWindow : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit LoggerWindow(QWidget * parent = Q_NULLPTR);
    explicit LoggerWindow(const QString & text, QWidget * parent = Q_NULLPTR);
protected:
    void contextMenuEvent(QContextMenuEvent * event);
};

#endif // LOGGER_WINDOW_H
