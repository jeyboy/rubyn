#ifndef IRUBY_STUBS_PREPARER_H
#define IRUBY_STUBS_PREPARER_H

#include "misc/defines.h"

class IRubyStubsPreparer {
public:
    virtual bool prepare(const QString & version) = 0;
};

#endif // IRUBY_STUBS_PREPARER_H
