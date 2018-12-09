#ifndef DEBUG_STUB_INTERFACE_H
#define DEBUG_STUB_INTERFACE_H

#include "debugging/idebug_interface.h"

#include <qhash.h>

class DebugStubInterface : public IDebugInterface {
    QHash<DebugBreakpoint, bool> entries;
public:
    DebugStubInterface();

    bool enableBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num, const bool & enable);
    bool addBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);
    bool removeBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);

    QString resolve(const QString & record);

    QList<DebugBreakpoint> breakpoints();
    void clear();
};

#endif // DEBUG_STUB_INTERFACE_H
