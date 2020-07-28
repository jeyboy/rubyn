#include "breakpoints_controller.h"
#include "qdebug.h"

void BreakpointsController::addPanel(const uint & project_id, BreakpointsPanel * panel) {
    qDebug() << "addPanel" << project_id;

    _panels.insert(project_id, panel);

    if (panel) {
        connect(this, &BreakpointsController::activateBreakpoint, panel, &BreakpointsPanel::activateBreakpoint);
        connect(panel, &BreakpointsPanel::breakpointRemoved, this, &BreakpointsController::breakpointRemoved);
        connect(panel, &BreakpointsPanel::breakpointDisabled, this, &BreakpointsController::breakpointDisabled);
    } else {
        _panels.remove(project_id);
    }
}

void BreakpointsController::pathRemoved(const QString & path) {

}

void BreakpointsController::pathRenamed(const QString & old_path, const QString & new_path) {

}

void BreakpointsController::breakpointAdded(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
    qDebug() << "breakpointAdded" << project_id;

    if (_panels.contains(project_id)) {
        BreakpointsPanel * panel = _panels[project_id];
        panel -> addBreakpoint(project_id, path, line_num);
    }
}
void BreakpointsController::breakpointMoved(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & prev_line_num, const EDITOR_POS_TYPE & line_num) {
    qDebug() << "breakpointMoved" << project_id;

    if (_panels.contains(project_id)) {
        BreakpointsPanel * panel = _panels[project_id];
        panel -> moveBreakpoint(project_id, path, prev_line_num, line_num);
    }
}
void BreakpointsController::breakpointRemoved(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
    qDebug() << "breakpointRemoved" << project_id;

    if (_panels.contains(project_id)) {
        BreakpointsPanel * panel = _panels[project_id];
        panel -> removeBreakpoint(project_id, path, line_num);
    }

    emit removeBreakpoint(project_id, path, line_num);
}

void BreakpointsController::breakpointDisabled(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
    qDebug() << "breakpointDisabled" << project_id;

    qDebug() << "BreakpointsController::breakpointDisabled" << project_id << path << line_num;
}
