#ifndef SCOPE_H
#define SCOPE_H

#include <qhash.h>

#include "scope_types.h"
#include "parts/editor_parts/file_point.h"

//class FilePoint;

class IScope {
    QHash<QByteArray, FilePoint> * methods;
    QHash<QByteArray, FilePoint> * variables;
    QHash<QByteArray, FilePoint> * constants;
public:
    virtual ScopeType scopeType() const = 0;

    inline bool hasVariable(const QByteArray & name) { return variables -> contains(name); }
    inline void addVariable(const QByteArray & name, const FilePoint & fpoint) {
        variables -> insert(name, fpoint);
    }

    inline bool hasConst(const QByteArray & name) { return constants -> contains(name); }
    inline void addConst(const QByteArray & name, const FilePoint & fpoint) {
        constants -> insert(name, fpoint);
    }

    inline bool hasMethod(const QByteArray & name) { return methods -> contains(name); }
    void addMethod(const QByteArray & name, const FilePoint & fpoint) {
        methods -> insert(name, fpoint);
    }
};

#endif // SCOPE_H
