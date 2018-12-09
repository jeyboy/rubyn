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
    QHash<QString, QHash<EDITOR_POS_TYPE, QListWidgetItem * >> records;
public:
    BreakpointsPanel(QWidget * parent = nullptr);

signals:
    void breakpointAdded(const QString & path, const EDITOR_POS_TYPE & line_num);
    void breakpointMoved(const QString & path, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num);
    void breakpointRemoved(const QString & path, const EDITOR_POS_TYPE & line_num);

public slots:
    void pathRemoved(const QString & path);
    void pathRenamed(const QString & path);

    void activateBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);
    void addBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);
    void moveBreakpoint(const QString & path, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num);
    void removeBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);
};

#endif // BREAKPOINTS_PANEL_H
