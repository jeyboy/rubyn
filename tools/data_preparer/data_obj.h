#ifndef DATA_OBJ_H
#define DATA_OBJ_H

#include <qmap.h>

#include "lexer/lexem_mean_type.h"

struct DataObj {
    uchar level;
    QByteArray parent;

    QStringList obj_description;
    QStringList includes;

    QByteArray obj_type;
    QByteArray obj_inheritance;

    struct DataMethod {
        LexerMeanType lex_type;

        QStringList description;

        QStringList signatures;

        QString args_mask;

        DataMethod(const LexerMeanType & mtype = lmt_unknow) : lex_type(mtype) {

        }
    };

    QMap<QByteArray, QString> constants;
    QMap<QByteArray, DataMethod> methods;

    DataObj(const uchar & obj_level = 1) : level(obj_level) {

    }
};

#endif // DATA_OBJ_H
