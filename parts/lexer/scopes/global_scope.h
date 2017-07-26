#ifndef GLOBAL_SCOPE_H
#define GLOBAL_SCOPE_H

#include "iscope.h"

class GlobalScope : public IScope {
public:
    inline ScopeType scopeType() const { return sct_global; }
};

#endif // GLOBAL_SCOPE_H
