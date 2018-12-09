#include "debug.h"

#include "debugging/idebug_interface.h"

#include <qdebug.h>
#include <qstringbuilder.h>

Debug::Debug() { }

Debug::~Debug() { handler -> clear(); }

void Debug::enableBreakpoint(const QString & path, const int & line_num, const bool & enable) {
    if (handler -> enableBreakpoint(path, line_num, enable)) {
        emit breakpointEnabled(path, line_num, enable);
    }
}
void Debug::addBreakpoint(const QString & path, const int & line_num) {
    if (handler -> addBreakpoint(path, line_num)) {
        emit breakpointAdded(path, line_num);
    }
}
void Debug::removeBreakpoint(const QString & path, const int & line_num) {
    if (handler -> removeBreakpoint(path, line_num)) {
        emit breakpointRemoved(path, line_num);
    }
}

void Debug::resolve(const QString & record) {
    QString res = handler -> resolve(record);
    emit resolved(record, res);
}
