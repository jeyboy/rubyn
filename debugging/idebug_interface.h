#ifndef IDEBUG_INTERFACE_H
#define IDEBUG_INTERFACE_H

#include <qstring.h>

#include "misc/defines.h"

struct DebugBreakpoint {
    QString path;
    EDITOR_POS_TYPE line_num;
};

class IDebugInterface : public QObject {
public:
    static QString mark(const QString & path, const int & line_num);

    IDebugInterface();
    virtual ~IDebugInterface();

    virtual bool enableBreakpoint(const QString & path, const int & line_num, const bool & enable);
    virtual bool addBreakpoint(const QString & path, const int & line_num);
    virtual bool removeBreakpoint(const QString & path, const int & line_num);

    virtual QString resolve(const QString & record);

    virtual QVector<DebugBreakpoint> breakpoints() = 0;
    virtual void clear() = 0;
signals:
    void breakpointActivated(const QString & path, const int & line_num);
};

#endif // IDEBUG_INTERFACE_H
