#ifndef BREAKPOINTS_PANEL_H
#define BREAKPOINTS_PANEL_H

#include "misc/defines.h"

#include <qwidget.h>

class QListWidget;
class File;

class BreakpointsPanel : public QWidget {
    QListWidget * breakpoints;
public:
    BreakpointsPanel(QWidget * parent = nullptr);

    void addBreakpoint(File * f, const EDITOR_POS_TYPE & line_num);
    void moveBreakpoint(File * f, const EDITOR_POS_TYPE & line_num);
    void removeBreakpoint(File * f, const EDITOR_POS_TYPE & line_num);
};

#endif // BREAKPOINTS_PANEL_H
