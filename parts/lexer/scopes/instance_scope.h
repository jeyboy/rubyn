#ifndef INSTANCE_SCOPE_H
#define INSTANCE_SCOPE_H

#include "iscope.h"

class InstanceScope : public IScope {
public:
    inline ScopeType scopeType() const { return sct_instance; }
};

#endif // INSTANCE_SCOPE_H
