#ifndef PARA_TYPE_H
#define PARA_TYPE_H

#include "misc/defines.h"

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

    pt_open_if = 1 << 14 | pt_open_foldable,

    pt_open_elsif = 1 << 15 | pt_open_foldable,

    pt_open_else = 1 << 16 | pt_open_foldable,

    pt_open_unless = 1 << 17 | pt_open_foldable,

    pt_open_case = 1 << 18 | pt_open_foldable,

    pt_open_when = 1 << 19 | pt_open_foldable,

    pt_open_while = 1 << 20 | pt_open_foldable,

    pt_open_until = 1 << 21 | pt_open_foldable,

    pt_open_for = 1 << 22 | pt_open_foldable,

    pt_rescue = 1 << 23 | pt_open_foldable,

    pt_ensure = 1 << 24 | pt_open_foldable,

    pt_open_struct = pt_open_do_block | pt_open_method | pt_open_class | pt_open_module |
        pt_open_if | pt_open_else | pt_open_elsif | pt_open_unless | pt_open_case |
        pt_open_when | pt_open_while | pt_open_until | pt_open_for | pt_rescue | pt_ensure,

    pt_close_struct = 1 << 25 | pt_close,

    pt_string = 1 << 26,

    pt_open_string = pt_string | pt_open,
    pt_close_string = pt_string | pt_close,

    pt_interpolation = 1 << 27,

    pt_open_interpolation = pt_interpolation | pt_open,
    pt_close_interpolation = pt_interpolation | pt_close,

    pt_regexp = 1 << 28,

    pt_open_regexp = pt_regexp | pt_open,
    pt_close_regexp = pt_regexp | pt_close,

    pt_max = 1 << 29,
    pt_max_end = pt_max | pt_close
};

//static inline QByteArray toString(const PARA_TYPE & para_type) {
//    switch(para_type) {
//        case pt_selectable: return QByteArrayLiteral("selectable");
//        case pt_foldable: return QByteArrayLiteral("foldable");
//        case pt_open_foldable: return QByteArrayLiteral("open_foldable");

//        case pt_curly_bracket: return QByteArrayLiteral("curly_bracket");
//        case pt_open_curly_bracket: return QByteArrayLiteral("open_curly_bracket");
//        case pt_close_curly_bracket: return QByteArrayLiteral("close_curly_bracket");

//        case pt_square_bracket: return QByteArrayLiteral("square_bracket");
//        case pt_open_square_bracket: return QByteArrayLiteral("open_square_bracket");
//        case pt_close_square_bracket: return QByteArrayLiteral("close_square_bracket");

//        case pt_round_bracket: return QByteArrayLiteral("round_bracket");
//        case pt_open_round_bracket: return QByteArrayLiteral("open_round_bracket");
//        case pt_close_round_bracket: return QByteArrayLiteral("close_round_bracket");

////        pt_angle_bracket = 1 << 7 | pt_selectable, //<

////        pt_open_angle_bracket = pt_angle_bracket | pt_open, //<
////        pt_close_angle_bracket = pt_angle_bracket | pt_close, //>

//        case pt_open_do_block: return QByteArrayLiteral("open_do_block");
//        case pt_open_begin_block: return QByteArrayLiteral("open_begin_block");
//        case pt_open_method: return QByteArrayLiteral("open_method");
//        case pt_open_class: return QByteArrayLiteral("open_class");
//        case pt_open_module: return QByteArrayLiteral("open_module");
//        case pt_open_if: return QByteArrayLiteral("open_if");
//        case pt_open_unless: return QByteArrayLiteral("open_unless");
//        case pt_open_case: return QByteArrayLiteral("open_case");
//        case pt_open_while: return QByteArrayLiteral("open_while");
//        case pt_open_until: return QByteArrayLiteral("open_until");
//        case pt_open_for: return QByteArrayLiteral("open_for");

//        case pt_open_struct: return QByteArrayLiteral("open_struct");
//        case pt_close_struct: return QByteArrayLiteral("close_struct");

//        case pt_max: return QByteArrayLiteral("max");
//        case pt_max_end: return QByteArrayLiteral("max_end");

//        default: return QByteArrayLiteral("XXX");
//    };
//}

#endif // PARA_TYPE_H
