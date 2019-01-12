#ifndef BREAKPOINTS_CONTROLLER_H
#define BREAKPOINTS_CONTROLLER_H

#include "misc/singleton.h"

#include "controls/breakpoints_panel.h"

#include <qobject.h>

class BreakpointsController : public QObject, public Singleton<BreakpointsController> {
    Q_OBJECT

    BreakpointsPanel * _panel;
public:
    void setPanel(BreakpointsPanel * panel);

signals:
    void activateBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);
    void removeBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);

public slots:
    void pathRemoved(const QString & path);
    void pathRenamed(const QString & old_path, const QString & new_path);

    void breakpointAdded(const QString & path, const EDITOR_POS_TYPE & line_num);
    void breakpointMoved(const QString & path, const EDITOR_POS_TYPE & prev_line_num, const EDITOR_POS_TYPE & line_num);
    void breakpointRemoved(const QString & path, const EDITOR_POS_TYPE & line_num);
};

#endif // BREAKPOINTS_CONTROLLER_H
