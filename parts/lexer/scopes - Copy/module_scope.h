#ifndef MODULE_SCOPE_H
#define MODULE_SCOPE_H

#include "iscope.h"

class ModuleScope : public IScope {
public:
    inline ScopeType scopeType() const { return sct_module; }
};

#endif // MODULE_SCOPE_H
