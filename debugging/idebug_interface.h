#ifndef IDEBUG_INTERFACE_H
#define IDEBUG_INTERFACE_H

#include "debugging/debug_breakpoint.h"

class IDebugInterface {
public:
    static QString mark(const QString & path, const EDITOR_POS_TYPE & line_num);

    IDebugInterface();
    virtual ~IDebugInterface();

    virtual bool enableBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num, const bool & enable);
    virtual bool addBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);
    virtual bool removeBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);

    virtual QString resolve(const QString & record);

    virtual QList<DebugBreakpoint> breakpoints() = 0;
    virtual void clear() = 0;
};

#endif // IDEBUG_INTERFACE_H
