#ifndef SCOPE_NODE_H
#define SCOPE_NODE_H

class File;

#include "scope_node_type.h"

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
    ScopeNode * ancestor;
    File * file;
    int start;
    ScopeNodeType sn_type;
//    int end;

    GlobalScope * gscope;
    ModuleScope * mscope;
    ClassScope * cscope;
    InstanceScope * iscope;
    LocalScope * lscope;
public:
    ScopeNode(const ScopeNodeType & sn_type = snt_block, File * file = 0, const int & start = 0,
        ScopeNode * parent = 0) : ancestor(parent), file(file), start(start), sn_type(sn_type),
        gscope(0), mscope(0), cscope(0), iscope(0), lscope(0)
    {
        if (!parent)
            gscope = new GlobalScope(); // we must initiate global scope with global attributes
    }

    bool hasModule(const QByteArray & name) {
        if (cscope && cscope -> hasModule(name))
            return true;

        if (mscope && mscope -> hasModule(name))
            return true;

        if (gscope && gscope -> hasModule(name))
            return true;

        return false;
    }
    void addModule(const ScopeType & stype, const QByteArray & name, const int & line, const int & left) {
        CHOOSE_SCOPE_BLOCK(stype);
        scope -> addModule(name, FilePoint {file, line, left, stype});
    }

    bool hasClass(const QByteArray & name) {
        if (cscope && cscope -> hasClass(name))
            return true;

        if (mscope && mscope -> hasClass(name))
            return true;

        if (gscope && gscope -> hasClass(name))
            return true;

        return false;
    }
    void addClass(const ScopeType & stype, const QByteArray & name, const int & line, const int & left) {
        CHOOSE_SCOPE_BLOCK(stype);
        scope -> addClass(name, FilePoint {file, line, left, stype});
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

        if (ancestor)
            return ancestor -> hasVariable(name, true);
        else
            return sct_none;
    }
    void addVariable(const ScopeType & stype, const QByteArray & name, const int & line, const int & left) {
        CHOOSE_SCOPE_BLOCK(stype);
        scope -> addVariable(name, FilePoint {file, line, left, stype});
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

        if (ancestor)
            return ancestor -> hasConst(name, true);
        else
            return sct_none;
    }
    void addConst(const ScopeType & stype, const QByteArray & name, const int & line, const int & left) {
        CHOOSE_SCOPE_BLOCK(stype);
        scope -> addConst(name, FilePoint {file, line, left, stype});
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

        if (ancestor)
            return ancestor -> hasMethod(name, true);
        else
            return sct_none;
    }
    void addMethod(const ScopeType & stype, const QByteArray & name, const int & line, const int & left) {
        CHOOSE_SCOPE_BLOCK(stype);
        scope -> addMethod(name, FilePoint {file, line, left, stype});
    }

};

#endif // SCOPE_NODE_H