#include "breakpoints_controller.h"

void BreakpointsController::addPanel(const uint & project_uid, BreakpointsPanel * panel) {
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

void BreakpointsController::breakpointAdded(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
    if (_panels.contains())

//    _panel -> addBreakpoint(path, line_num);
}
void BreakpointsController::breakpointMoved(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & prev_line_num, const EDITOR_POS_TYPE & line_num) {
//    _panel -> moveBreakpoint(path, prev_line_num, line_num);
}
void BreakpointsController::breakpointRemoved(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
//    _panel -> removeBreakpoint(path, line_num);
    emit removeBreakpoint(project_id, path, line_num);
}

void BreakpointsController::breakpointDisabled(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
    qDebug() << "BreakpointsController::breakpointDisabled" << project_id << path << line_num;
}
