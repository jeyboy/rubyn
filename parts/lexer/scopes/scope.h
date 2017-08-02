#ifndef SCOPE_H
#define SCOPE_H

#include <qhash.h>

#include "file_point.h"
#include "misc/chain.h"

class Scope {
    QHash<QByteArray, FilePoint *> context_objs;
    QHash<QByteArray, Chain<VarPoint> > inclusions;
public:
    ~Scope() {
        qDeleteAll(context_objs);
    }

    inline bool hasVariable(const QByteArray & name) { return context_objs.contains(name); }
    inline void addVariable(const QByteArray & name, FilePoint * fpoint) {
        context_objs.insert(name, fpoint);
    }

    inline void registerInclusion(const QByteArray & name, const VarPoint & val) {
        if (!inclusions.contains(name))
            inclusions[name] = Chain<VarPoint>();

        inclusions[name].add(val);
    }
};

#endif // SCOPE_H
