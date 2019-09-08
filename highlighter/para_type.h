#ifndef PARA_TYPE_H
#define PARA_TYPE_H

#include "misc/defines.h"

enum ParaType : PARA_TYPE {
    pt_max = 1 << 28,
    pt_close = 1 << 29,
    pt_foldable = 1 << 30,

    pt_max_end = pt_max | pt_close,

    //////////////////////////////

    pt_none = 0,

    //////////////////////////////

    // {}
    pt_curly_bracket = 1,
    pt_close_curly_bracket = pt_curly_bracket | pt_close,

    pt_foldable_curly_bracket = pt_curly_bracket | pt_foldable,
    pt_close_foldable_curly_bracket = pt_foldable_curly_bracket | pt_close,

    // []
    pt_square_bracket = 2,
    pt_close_square_bracket = pt_square_bracket | pt_close,
    pt_foldable_square_bracket = pt_square_bracket | pt_foldable,
    pt_close_foldable_square_bracket = pt_foldable_square_bracket | pt_close,

    // ()
    pt_round_bracket = 3,
    pt_close_round_bracket = pt_round_bracket | pt_close,

    // <>
    pt_angle_bracket = 4,
    pt_close_angle_bracket = pt_angle_bracket | pt_close,

    // ''
    pt_string = 5,
    pt_close_string = pt_string | pt_close,

    // ""
    pt_estring = 6,
    pt_close_estring = pt_estring | pt_close,

    // ``
    pt_command = 7,
    pt_close_command = pt_command | pt_close,

    // #{}
    pt_interpolation = 8,
    pt_close_interpolation = pt_interpolation | pt_close,

    // //
    pt_regexp = 9,
    pt_close_regexp = pt_regexp | pt_close,

    pt_representation = 10,
    pt_close_representation = pt_representation | pt_close,

    pt_open_class = 11 | pt_foldable,
    pt_open_module = 12 | pt_foldable,
    pt_open_do_block = 13 | pt_foldable,

    pt_open_begin_block = 14 | pt_foldable,
    pt_open_method = 15 | pt_foldable,
    pt_open_if = 16 | pt_foldable,
    pt_open_elsif = 17 | pt_foldable,
    pt_open_else = 18 | pt_foldable,
    pt_open_unless = 19 | pt_foldable,
    pt_open_case = 20 | pt_foldable,
    pt_open_when = 21 | pt_foldable,
    pt_open_while = 22 | pt_foldable,
    pt_open_until = 23 | pt_foldable,
    pt_open_for = 24 | pt_foldable,
    pt_rescue = 25 | pt_foldable,
    pt_ensure = 26 | pt_foldable,

    pt_close_begin_block = pt_open_begin_block | pt_close,
    pt_close_method = pt_open_method | pt_close,
    pt_close_if = pt_open_if | pt_close,
    pt_close_elsif = pt_open_elsif | pt_close,
    pt_close_else = pt_open_else | pt_close,
    pt_close_unless = pt_open_unless | pt_close,
    pt_close_case = pt_open_case | pt_close,
    pt_close_when = pt_open_when | pt_close,
    pt_close_while = pt_open_while | pt_close,
    pt_close_until = pt_open_until | pt_close,
    pt_close_for = pt_open_for | pt_close,


//    pt_open_struct = pt_open_do_block | pt_open_method | pt_open_class | pt_open_module |
//        pt_open_if | pt_open_else | pt_open_elsif | pt_open_unless | pt_open_case |
//        pt_open_when | pt_open_while | pt_open_until | pt_open_for | pt_rescue | pt_ensure,

    pt_close_struct = 27 | pt_close | pt_foldable,

    pt_comment = 28,
    pt_close_comment = pt_comment | pt_close,
    pt_foldable_comment = pt_comment | pt_foldable,
    pt_close_foldable_comment = pt_comment | pt_close| pt_foldable,

    pt_ternary = 29,
    pt_close_ternary = pt_ternary | pt_close,
};

#endif // PARA_TYPE_H
