#ifndef DATA_OBJ_H
#define DATA_OBJ_H

#include <qmap.h>

#include "lexer/lexem_mean_type.h"

struct DataMethod {
    LexerMeanType lex_type;

    QStringList description;

    QStringList signatures;

    QString args_mask;

    QString alias_name;

    DataMethod(const LexerMeanType & mtype = lmt_unknow) : lex_type(mtype) {

    }
};

struct DataObj {
    uchar level;

    QByteArray parent;
    QByteArray name;
    QByteArray obj_type;
    QByteArray obj_inheritance;

    QStringList description;
    QStringList includes;

    QMap<QByteArray, QByteArray> attributes;
    QMap<QByteArray, QByteArray> constants;
    QMap<QByteArray, DataMethod> methods;
    QMap<QByteArray, DataObj> namespaces;

    DataObj(const uchar & obj_level = 1) : level(obj_level) {

    }
};

#endif // DATA_OBJ_H
