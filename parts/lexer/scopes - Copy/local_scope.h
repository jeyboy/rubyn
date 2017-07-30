#ifndef LOCAL_SCOPE_H
#define LOCAL_SCOPE_H

#include "iscope.h"

class LocalScope : public IScope {
public:
    inline ScopeType scopeType() const { return sct_local; }
};

#endif // LOCAL_SCOPE_H
