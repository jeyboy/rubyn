#include "idebug_interface.h"

#include <qstringbuilder.h>

QString IDebugInterface::mark(const QString & path, const EDITOR_POS_TYPE & line_num) { return path % '*' % QString::number(line_num); }

IDebugInterface::IDebugInterface() { }
IDebugInterface::~IDebugInterface() { }

bool IDebugInterface::enableBreakpoint(const QString & /*path*/, const EDITOR_POS_TYPE & /*line_num*/, const bool & /*enable*/) { return false; }
bool IDebugInterface::addBreakpoint(const QString & /*path*/, const EDITOR_POS_TYPE & /*line_num*/) { return false; }
bool IDebugInterface::removeBreakpoint(const QString & /*path*/, const EDITOR_POS_TYPE & /*line_num*/) { return false; }

QString IDebugInterface::resolve(const QString & /*record*/) { return QLatin1String("Unsupported"); }
