#include "breakpoints_controller.h"

void BreakpointsController::setPanel(BreakpointsPanel * panel) {
    _panel = panel;

    if (_panel) {
        connect(this, &BreakpointsController::activateBreakpoint, _panel, &BreakpointsPanel::activateBreakpoint);
        connect(_panel, &BreakpointsPanel::breakpointRemoved, this, &BreakpointsController::breakpointRemoved);
    }
}

void BreakpointsController::pathRemoved(const QString & path) {

}

void BreakpointsController::pathRenamed(const QString & old_path, const QString & new_path) {

}

void BreakpointsController::breakpointAdded(const QString & path, const EDITOR_POS_TYPE & line_num) {
    _panel -> addBreakpoint(path, line_num);
}
void BreakpointsController::breakpointMoved(const QString & path, const EDITOR_POS_TYPE & prev_line_num, const EDITOR_POS_TYPE & line_num) {
    _panel -> moveBreakpoint(path, prev_line_num, line_num);
}
void BreakpointsController::breakpointRemoved(const QString & path, const EDITOR_POS_TYPE & line_num) {
    _panel -> removeBreakpoint(path, line_num);
    emit removeBreakpoint(path, line_num);
}
