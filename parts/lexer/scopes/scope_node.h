#ifndef SCOPE_NODE_H
#define SCOPE_NODE_H

class File;

#include "global_scope.h"
#include "module_scope.h"
#include "class_scope.h"
#include "instance_scope.h"
#include "local_scope.h"

#define CHOOSE_SCOPE_BLOCK(stype) \
    IScope * scope; \
\
    switch(stype) {\
        case sct_global: { if (!gscope) gscope = new GlobalScope(); scope = gscope; break; } \
        case sct_module: { if (!mscope) mscope = new ModuleScope(); scope = mscope; break; } \
        case sct_class: { if (!cscope) cscope = new ClassScope(); scope = cscope; break; } \
        case sct_instance: { if (!iscope) iscope = new InstanceScope(); scope = iscope; break; } \
        case sct_local: { if (!lscope) lscope = new LocalScope(); scope = lscope; break; } \
        default: scope = 0;\
    }


class ScopeNode {
    ScopeNode * parent;
    ScopeNode * next;
    File * file;

    GlobalScope * gscope;
    ModuleScope * mscope;
    ClassScope * cscope;
    InstanceScope * iscope;
    LocalScope * lscope;
public:
    ScopeNode(File * file, ScopeNode * parent = 0) :
        parent(parent), next(0), file(file), gscope(0),
        mscope(0), cscope(0), iscope(0), lscope(0)
    {
        if (parent)
            parent -> next = this;
    }

    ScopeType hasVariable(const QByteArray & name, const bool & ignore_local = false) {
        if (!ignore_local && lscope && lscope -> hasVariable(name))
            return lscope -> scopeType();

        if (iscope && iscope -> hasVariable(name))
            return iscope -> scopeType();

        if (cscope && cscope -> hasVariable(name))
            return cscope -> scopeType();

        if (mscope && mscope -> hasVariable(name))
            return mscope -> scopeType();

        if (gscope && gscope -> hasVariable(name))
            return gscope -> scopeType();

        if (parent)
            return parent -> hasVariable(name, true);
        else
            return sct_none;
    }
    void addVariable(const ScopeType & stype, const QByteArray & name, const int & line, const int & left) {
        CHOOSE_SCOPE_BLOCK(stype);
        scope -> addVariable(name, FilePoint {file, line, left});
    }

    ScopeType hasConst(const QByteArray & name, const bool & ignore_local = false) {
        if (!ignore_local && lscope && lscope -> hasConst(name))
            return lscope -> scopeType();

        if (iscope && iscope -> hasConst(name))
            return iscope -> scopeType();

        if (cscope && cscope -> hasConst(name))
            return cscope -> scopeType();

        if (mscope && mscope -> hasConst(name))
            return mscope -> scopeType();

        if (gscope && gscope -> hasConst(name))
            return gscope -> scopeType();

        if (parent)
            return parent -> hasConst(name, true);
        else
            return sct_none;
    }
    void addConst(const ScopeType & stype, const QByteArray & name, const int & line, const int & left) {
        CHOOSE_SCOPE_BLOCK(stype);
        scope -> addConst(name, FilePoint {file, line, left});
    }

    ScopeType hasMethod(const QByteArray & name, const bool & ignore_local = false) {
        if (!ignore_local && lscope && lscope -> hasMethod(name))
            return lscope -> scopeType();

        if (iscope && iscope -> hasMethod(name))
            return iscope -> scopeType();

        if (cscope && cscope -> hasMethod(name))
            return cscope -> scopeType();

        if (mscope && mscope -> hasMethod(name))
            return mscope -> scopeType();

        if (gscope && gscope -> hasMethod(name))
            return gscope -> scopeType();

        if (parent)
            return parent -> hasMethod(name, true);
        else
            return sct_none;
    }
    void addMethod(const ScopeType & stype, const QByteArray & name, const int & line, const int & left) {
        CHOOSE_SCOPE_BLOCK(stype);
        scope -> addMethod(name, FilePoint {file, line, left});
    }

};

#endif // SCOPE_NODE_H
