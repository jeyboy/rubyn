#ifndef CLASS_SCOPE_H
#define CLASS_SCOPE_H

#include "iscope.h"

class ClassScope : public IScope {
public:
    inline ScopeType scopeType() const { return sct_class; }
};

#endif // CLASS_SCOPE_H
