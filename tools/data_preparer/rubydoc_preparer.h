#ifndef RUBYDOC_PREPARER_H
#define RUBYDOC_PREPARER_H

#include "iruby_stubs_preparer.h"

namespace Web {
    class Response;
}

class RubyDocPreparer : public IRubyStubsPreparer {
    Q_OBJECT
public:
    RubyDocPreparer();

    bool takeListOfVersions(QStringList & versions);

    void prepare(const QString & version);

protected slots:
    void responseReady(Web::Response *);
};

#endif // RUBYDOC_PREPARER_H
