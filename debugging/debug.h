#ifndef DEBUG_H
#define DEBUG_H

#include "misc/singleton.h"
#include "misc/defines.h"

//#include <qpointer.h>

class IDebugInterface;

class Debug : public QObject, public Singleton<Debug> {
    Q_OBJECT

    Debug();
    ~Debug();

    friend class Singleton<Debug>;

    IDebugInterface * handler;
public:
    void setupHandler(IDebugInterface * new_handler);

signals:
    void breakpointActivated(const QString & path, const EDITOR_POS_TYPE & line_num);
    void breakpointAdded(const QString & path, const EDITOR_POS_TYPE & line_num);
    void breakpointMoved(const QString & path, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num);
    void breakpointRemoved(const QString & path, const EDITOR_POS_TYPE & line_num);
    void breakpointEnabled(const QString & path, const EDITOR_POS_TYPE & line_num, const bool & enabled);
    void resolved(const QString & record, const QString & value);

public slots:
    void pathRemoved(const QString & path);
    void pathRenamed(const QString & path);

    void enableBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num, const bool & enable);
    void addBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);
    void removeBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num);
    void moveBreakpoint(const QString & path, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num);
    void resolve(const QString & record);
};

#endif // DEBUG_H
