#include "debug.h"

#include "debugging/idebug_interface.h"

#include <qdebug.h>
#include <qstringbuilder.h>

Debug::Debug() : handler(nullptr) { }

Debug::~Debug() {
    if (handler)
        handler -> clear();

    delete handler;
}

void Debug::setupHandler(IDebugInterface * new_handler) {
    if (handler)
        delete handler;

    handler = new_handler;
}

void Debug::pathRemoved(const QString & path) {

}

void Debug::pathRenamed(const QString & path) {

}

void Debug::enableBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num, const bool & enable) {
    if (handler && handler -> enableBreakpoint(path, line_num, enable)) {
        emit breakpointEnabled(path, line_num, enable);
    }
}
void Debug::addBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num) {
    if (handler && handler -> addBreakpoint(path, line_num)) {
        emit breakpointAdded(path, line_num);
    }
}
void Debug::removeBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num) {
    if (handler && handler -> removeBreakpoint(path, line_num)) {
        emit breakpointRemoved(path, line_num);
    }
}

void Debug::moveBreakpoint(const QString & path, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num) {
    if (handler) {
        if (handler -> removeBreakpoint(path, old_line_num) && handler -> addBreakpoint(path, new_line_num))
        emit breakpointMoved(path, old_line_num, new_line_num);
    }
}

void Debug::resolve(const QString & record) {
    if (handler) {
        QString res = handler -> resolve(record);
        emit resolved(record, res);
    }
}
