#ifndef SCOPE_H
#define SCOPE_H

#include <qhash.h>

#include "file_point.h"
#include "misc/chain.h"
#include "misc/stack.h"

class Scope {
    QHash<QByteArray, FilePoint *> context_objs;
//    QHash<QByteArray, Chain<VarPoint> > inclusions;
    QHash<QByteArray, FilePoint *> unreg_vars;
public:
    ~Scope() {
        qDeleteAll(context_objs);
    }

    inline bool hasVar(const QByteArray & name) { return context_objs.contains(name); }
    inline void addVar(const QByteArray & name, FilePoint * fpoint) {
        context_objs.insert(name, fpoint);
    }
    inline Lexem varType(const QByteArray & name) { return context_objs[name] -> stype; }

//    inline void registerInclusion(const QByteArray & name, const VarPoint & val) {
//        if (!inclusions.contains(name))
//            inclusions[name] = Chain<VarPoint>();

//        inclusions[name].add(val);
//    }

    inline void clearUnregVar() {
        context_objs.unite(unreg_vars);
        unreg_vars.clear();
    }
    inline void addUnregVar(const QByteArray & name, FilePoint * fpoint) {
        unreg_vars[name] = fpoint;
    }
};

#endif // SCOPE_H
