#ifndef DEBUG_H
#define DEBUG_H

#include "misc/singleton.h"

//#include <qpointer.h>

class IDebugInterface;

class Debug : public QObject, public Singleton<Debug> {
    Q_OBJECT

    Debug();
    ~Debug();

    friend class Singleton<Debug>;

    IDebugInterface * handler;
public:

signals:
    void breakpointActivated(const QString & path, const int & line_num);
    void breakpointAdded(const QString & path, const int & line_num);
    void breakpointRemoved(const QString & path, const int & line_num);
    void breakpointEnabled(const QString & path, const int & line_num, const bool & enabled);
    void resolved(const QString & record, const QString & value);

public slots:
    void enableBreakpoint(const QString & path, const int & line_num, const bool & enable);
    void addBreakpoint(const QString & path, const int & line_num);
    void removeBreakpoint(const QString & path, const int & line_num);
    void resolve(const QString & record);
};

#endif // DEBUG_H
