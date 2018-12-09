#ifndef DEBUG_BREAKPOINT_H
#define DEBUG_BREAKPOINT_H

#include "misc/defines.h"

struct DebugBreakpoint {
    QString path;
    EDITOR_POS_TYPE line_num;
};

#endif // DEBUG_BREAKPOINT_H
