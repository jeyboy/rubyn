#ifndef RUBYDOC_PREPARER_H
#define RUBYDOC_PREPARER_H

#include "iruby_stubs_preparer.h"

class RubyDocPreparer : public IRubyStubsPreparer {
public:
    RubyDocPreparer();

    bool prepare(const QString & version);
};

#endif // RUBYDOC_PREPARER_H
