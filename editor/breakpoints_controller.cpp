#include "breakpoints_controller.h"

void BreakpointsController::addPanel(const QString & project_uid, BreakpointsPanel * panel) {
    _panels.insert(project_uid, panel);

    if (panel) {
        connect(this, &BreakpointsController::activateBreakpoint, panel, &BreakpointsPanel::activateBreakpoint);
        connect(panel, &BreakpointsPanel::breakpointRemoved, this, &BreakpointsController::breakpointRemoved);
        connect(panel, &BreakpointsPanel::breakpointDisabled, this, &BreakpointsController::breakpointDisabled);
    } else {
        _panels.remove(project_uid);
    }
}

void BreakpointsController::pathRemoved(const QString & path) {

}

void BreakpointsController::pathRenamed(const QString & old_path, const QString & new_path) {

}

void BreakpointsController::breakpointAdded(const QString & path, const EDITOR_POS_TYPE & line_num) {
//    _panel -> addBreakpoint(path, line_num);
}
void BreakpointsController::breakpointMoved(const QString & path, const EDITOR_POS_TYPE & prev_line_num, const EDITOR_POS_TYPE & line_num) {
//    _panel -> moveBreakpoint(path, prev_line_num, line_num);
}
void BreakpointsController::breakpointRemoved(const QString & path, const EDITOR_POS_TYPE & line_num) {
//    _panel -> removeBreakpoint(path, line_num);
    emit removeBreakpoint(path, line_num);
}

void BreakpointsController::breakpointDisabled(const QString & path, const EDITOR_POS_TYPE & line_num) {
    qDebug() << "BreakpointsController::breakpointDisabled" << path << line_num;
}
