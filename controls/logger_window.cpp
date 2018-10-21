#include "logger_window.h"

#include <qmenu.h>

LoggerWindow::LoggerWindow(QWidget * parent) : QPlainTextEdit (parent) {}
LoggerWindow::LoggerWindow(const QString & text, QWidget * parent) : QPlainTextEdit (text, parent) {}

void LoggerWindow::contextMenuEvent(QContextMenuEvent * event) {
    QMenu * menu = createStandardContextMenu(event -> pos());

    menu -> addSeparator();

    QAction * act = menu -> addAction(tr("Clear"));
    connect(act, SIGNAL(triggered()), this, SLOT(clear()));
    /*QAction * choosedAction = */menu -> exec(event -> globalPos());

    delete menu;
}
