#ifndef SCOPE_H
#define SCOPE_H

#include <qhash.h>

#include "scope_item.h"

class Scope {
    QHash<QByteArray, Lexem> context_obj;
public:


//    inline bool hasVariable(const QByteArray & name) { return variables -> contains(name); }
//    inline void addVariable(const QByteArray & name, const FilePoint & fpoint) {
//        if (!variables) variables = new QHash<QByteArray, FilePoint>();

//        variables -> insert(name, fpoint);
//    }

//    inline bool hasConst(const QByteArray & name) { return constants -> contains(name); }
//    inline void addConst(const QByteArray & name, const FilePoint & fpoint) {
//        if (!constants) constants = new QHash<QByteArray, FilePoint>();

//        constants -> insert(name, fpoint);
//    }

//    inline bool hasMethod(const QByteArray & name) { return methods -> contains(name); }
//    void addMethod(const QByteArray & name, const FilePoint & fpoint) {
//        if (!methods) methods = new QHash<QByteArray, FilePoint>();

//        methods -> insert(name, fpoint);
//    }

//    inline bool hasClass(const QByteArray & name) { return classes -> contains(name); }
//    void addClass(const QByteArray & name, const FilePoint & fpoint) {
//        if (!classes) classes = new QHash<QByteArray, FilePoint>();

//        classes -> insert(name, fpoint);
//    }

//    inline bool hasModule(const QByteArray & name) { return modules -> contains(name); }
//    void addModule(const QByteArray & name, const FilePoint & fpoint) {
//        if (!modules) modules = new QHash<QByteArray, FilePoint>();

//        modules -> insert(name, fpoint);
//    }
};

#endif // SCOPE_H
