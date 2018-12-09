#include "debug_stub_interface.h"

DebugStubInterface::DebugStubInterface() : IDebugInterface() {}

bool DebugStubInterface::enableBreakpoint(const QString & /*path*/, const EDITOR_POS_TYPE & /*line_num*/, const bool & /*enable*/) { return true; }
bool DebugStubInterface::addBreakpoint(const QString & /*path*/, const EDITOR_POS_TYPE & /*line_num*/) { return true; }
bool DebugStubInterface::removeBreakpoint(const QString & /*path*/, const EDITOR_POS_TYPE & /*line_num*/) { return true; }

QString DebugStubInterface::resolve(const QString & /*record*/) { return QLatin1Literal("Fuck yeah!"); }

QList<DebugBreakpoint> DebugStubInterface::breakpoints() { return entries.keys(); }
void DebugStubInterface::clear() { entries.clear(); }
