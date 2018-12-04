#ifndef BREAKPOINTS_PANEL_H
#define BREAKPOINTS_PANEL_H

#include "misc/defines.h"

#include <qwidget.h>
#include <qhash.h>

class QListWidget;
class QListWidgetItem;
class File;

class BreakpointsPanel : public QWidget {
    Q_OBJECT

    QListWidget * breakpoints;
    QHash<QString, QListWidgetItem *> records;

    QString buildUid(File * f, const EDITOR_POS_TYPE & line_num);
public:
    BreakpointsPanel(QWidget * parent = nullptr);

signals:
    void breakpointAdded(File * f, const EDITOR_POS_TYPE & line_num);
    void breakpointMoved(File * f, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num);
    void breakpointRemoved(File * f, const EDITOR_POS_TYPE & line_num);
    void breakpointActivated(File * f, const EDITOR_POS_TYPE & line_num);

public slots:
    void addBreakpoint(File * f, const EDITOR_POS_TYPE & line_num);
    void moveBreakpoint(File * f, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num);
    void removeBreakpoint(File * f, const EDITOR_POS_TYPE & line_num);
};

#endif // BREAKPOINTS_PANEL_H
