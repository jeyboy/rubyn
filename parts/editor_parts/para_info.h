#ifndef PARA_INFO_H
#define PARA_INFO_H

#include "misc/defines.h"

struct ParaInfo {
    static QHash<QByteArray, PARA_TYPE> para_tokens;

    enum ParaType : PARA_TYPE {
        pt_none = 0,

        pt_open_curly_bracket = 1 << 0, //{
        pt_close_curly_bracket = 1 << 1, //}

        pt_open_square_bracket = 1 << 2, //[
        pt_close_square_bracket = 1 << 3, //]

        pt_open_round_bracket = 1 << 4, //(
        pt_close_round_bracket = 1 << 5, //)

        pt_open_angle_bracket = 1 << 6, //<
        pt_close_angle_bracket = 1 << 7, //>

        pt_open_block = 1 << 8,

        pt_open_class = 1 << 9,

        pt_open_module = 1 << 10,

        pt_open_struct = pt_open_block | pt_open_class | pt_open_module,
        pt_close_struct = 1 << 11,
    };

    PARA_TYPE para_type;
    EDITOR_POS_TYPE pos;

//    static char paraSymbol(const char & ch) {
//        switch(ch) {
//            case '(': return ')';
//            case '[': return ']';
//            case '{': return '}';

//            default: return ch;
//        };
//    }

//    inline char paraSymbol() { return ParaInfo::paraSymbol(symbol); }
};

QHash<QByteArray, PARA_TYPE> ParaInfo::para_tokens = {
    { QByteArrayLiteral("{"), ParaInfo::pt_open_curly_bracket },
    { QByteArrayLiteral("}"), ParaInfo::pt_close_curly_bracket },
    { QByteArrayLiteral("["), ParaInfo::pt_open_square_bracket },
    { QByteArrayLiteral("]"), ParaInfo::pt_close_square_bracket },
    { QByteArrayLiteral("("), ParaInfo::pt_open_round_bracket },
    { QByteArrayLiteral(")"), ParaInfo::pt_close_round_bracket },
//    { QByteArrayLiteral("<"), ParaInfo::pt_open_angle_bracket },
//    { QByteArrayLiteral(">"), ParaInfo::pt_close_angle_bracket },

    { QByteArrayLiteral("do"), ParaInfo::pt_open_block },
    { QByteArrayLiteral("class"), ParaInfo::pt_open_class },
    { QByteArrayLiteral("module"), ParaInfo::pt_open_module },

    { QByteArrayLiteral("end"), ParaInfo::pt_close_struct },
};

#endif // PARA_INFO_H
