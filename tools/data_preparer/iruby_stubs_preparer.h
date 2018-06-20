#ifndef IRUBY_STUBS_PREPARER_H
#define IRUBY_STUBS_PREPARER_H

#include <qobject.h>

#include "misc/defines.h"

class IRubyStubsPreparer : public QObject {
    Q_OBJECT
public:
    virtual void prepare(const QString & version) = 0;

signals:
    void done(const bool & status);
};

#endif // IRUBY_STUBS_PREPARER_H
