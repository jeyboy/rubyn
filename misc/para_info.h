#ifndef PARA_INFO_H
#define PARA_INFO_H

#include <qhash.h>

#include "misc/defines.h"

struct ParaInfo {
    static QHash<QByteArray, PARA_TYPE> para_tokens;
    static QHash<PARA_TYPE, PARA_TYPE> para_opposition;

    enum ParaType : PARA_TYPE {
        pt_none = 0,

        pt_open = 1 << 0,
        pt_close = 1 << 1,

        pt_selectable = 1 << 2,
        pt_foldable = 1 << 3,

        pt_open_foldable = pt_open | pt_foldable,

        pt_curly_bracket = 1 << 4 | pt_selectable,

        pt_open_curly_bracket = pt_curly_bracket | pt_open_foldable, //{
        pt_close_curly_bracket = pt_curly_bracket | pt_close, //}

        pt_square_bracket = 1 << 5 | pt_selectable,

        pt_open_square_bracket = pt_square_bracket | pt_open, //[
        pt_close_square_bracket = pt_square_bracket | pt_close, //]

        pt_round_bracket = 1 << 6 | pt_selectable,

        pt_open_round_bracket = pt_round_bracket | pt_open, //(
        pt_close_round_bracket = pt_round_bracket | pt_close, //)

//        pt_angle_bracket = 1 << 7 | pt_selectable, //<

//        pt_open_angle_bracket = pt_angle_bracket | pt_open, //<
//        pt_close_angle_bracket = pt_angle_bracket | pt_close, //>

        pt_open_do_block = 1 << 8 | pt_open_foldable,

        pt_open_begin_block = 1 << 9 | pt_open_foldable,

        pt_open_method = 1 << 11 | pt_open_foldable,

        pt_open_class = 1 << 12 | pt_open_foldable,

        pt_open_module = 1 << 13 | pt_open_foldable,

        pt_open_struct = pt_open_do_block | pt_open_method | pt_open_class | pt_open_module,
        pt_close_struct = 1 << 14 | pt_close,

        pt_max = 1 << 15,
        pt_max_end = pt_max | pt_close
    };

    PARA_TYPE para_type;
    EDITOR_POS_TYPE pos;

    inline PARA_TYPE paraSymbol() { return ParaInfo::para_opposition.value(para_type, pt_none); }

    static inline bool hasPara(const QByteArray & poss_para) { return para_tokens.contains(poss_para); }
    static inline const PARA_TYPE & paraType(const QByteArray & poss_para) { return para_tokens[poss_para]; }
    static inline PARA_TYPE oppositePara(const PARA_TYPE & para_type) { return para_opposition.value(para_type, pt_none); }
};

#endif // PARA_INFO_H
