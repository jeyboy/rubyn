#ifndef RUBY_PARA_LEXEM_H
#define RUBY_PARA_LEXEM_H

#include "misc/defines.h"

namespace Ruby {
    enum ParaLexem : PARA_TYPE {
        DefaultParaLexems,



//        lex_scope_pre_code = 1, // BEGIN
//        lex_scope_post_code, // END
//        lex_scope_after_code, // __END__
//        lex_scope_method_arg_def, // def n(...)
//        lex_scope_method_var_def, // def n ...
//        lex_scope_method_body, // def n(); ... end
//        lex_scope_lambda_def, // -> () {...}
//        lex_scope_local_block_vars, // .each {|...| }
//        lex_scope_local_block_body, // .each {|a| ... }
//        lex_scope_class_body, // class N { ... }
//        lex_scope_module_body, // class N { ... }
//        lex_scope_array_body, // [ ... ]
//        lex_scope_hash_body, // { ... }
//        lex_scope_string, // "asdad...asdasda"
//        lex_scope_heredoc, // <<`EOC`; ... EOC
//        lex_scope_regexp, // /\w#{...}/
//        lex_scope_percent_string, // %r(/home/#{...})
//        lex_scope_round_brackets, // (...)
//        lex_scope_begin_block, // begin; ... end
//        lex_scope_do_block_vars, // .each do |...| end
//        lex_scope_do_block_body, // .each do |a| ... end



        // {}
        pt_curly_bracket = (pt_reserved + 1),
        pt_close_curly_bracket = pt_curly_bracket | pt_close,

        pt_foldable_curly_bracket = pt_curly_bracket | pt_foldable,
        pt_close_foldable_curly_bracket = pt_foldable_curly_bracket | pt_close,

        // []
        pt_square_bracket = (pt_reserved + 2),
        pt_close_square_bracket = pt_square_bracket | pt_close,
        pt_foldable_square_bracket = pt_square_bracket | pt_foldable,
        pt_close_foldable_square_bracket = pt_foldable_square_bracket | pt_close,

        // ()
        pt_round_bracket = (pt_reserved + 3),
        pt_close_round_bracket = pt_round_bracket | pt_close,

        // <>
        pt_angle_bracket = (pt_reserved + 4),
        pt_close_angle_bracket = pt_angle_bracket | pt_close,

        // ''
        pt_string = (pt_reserved + 5),
        pt_close_string = pt_string | pt_close,

        // ""
        pt_estring = (pt_reserved + 6),
        pt_close_estring = pt_estring | pt_close,

        // ``
        pt_command = (pt_reserved + 7),
        pt_close_command = pt_command | pt_close,

        // #{}
        pt_interpolation = (pt_reserved + 8),
        pt_close_interpolation = pt_interpolation | pt_close,

        // //
        pt_regexp = (pt_reserved + 9),
        pt_close_regexp = pt_regexp | pt_close,

        pt_representation = (pt_reserved + 10),
        pt_close_representation = pt_representation | pt_close,

        pt_open_class = (pt_reserved + 11) | pt_foldable,
        pt_open_module = (pt_reserved + 12) | pt_foldable,
        pt_open_do_block = (pt_reserved + 13) | pt_foldable,

        pt_open_begin_block = (pt_reserved + 14) | pt_foldable,
        pt_open_method = (pt_reserved + 15) | pt_foldable,
        pt_open_if = (pt_reserved + 16) | pt_foldable,
        pt_open_then = (pt_reserved + 17),
        pt_open_elsif = (pt_reserved + 18) | pt_foldable,
        pt_open_else = (pt_reserved + 19) | pt_foldable,
        pt_open_unless = (pt_reserved + 20) | pt_foldable,
        pt_open_case = (pt_reserved + 21) | pt_foldable,
        pt_open_when = (pt_reserved + 22) | pt_foldable,
        pt_open_while = (pt_reserved + 23) | pt_foldable,
        pt_open_until = (pt_reserved + 24) | pt_foldable,
        pt_open_for = (pt_reserved + 25) | pt_foldable,
        pt_open_for_in = (pt_reserved + 26),
        pt_rescue = (pt_reserved + 27) | pt_foldable,
        pt_ensure = (pt_reserved + 28) | pt_foldable,

//        pt_close_begin_block = pt_open_begin_block | pt_close,
//        pt_close_method = pt_open_method | pt_close,
//        pt_close_if = pt_open_if | pt_close,
//        pt_close_then = pt_open_then | pt_close,
//        pt_close_elsif = pt_open_elsif | pt_close,
//        pt_close_else = pt_open_else | pt_close,
//        pt_close_unless = pt_open_unless | pt_close,
//        pt_close_case = pt_open_case | pt_close,
//        pt_close_when = pt_open_when | pt_close,
//        pt_close_while = pt_open_while | pt_close,
//        pt_close_until = pt_open_until | pt_close,
//        pt_close_for = pt_open_for | pt_close,


    //    pt_open_struct = pt_open_do_block | pt_open_method | pt_open_class | pt_open_module |
    //        pt_open_if | pt_open_else | pt_open_elsif | pt_open_unless | pt_open_case |
    //        pt_open_when | pt_open_while | pt_open_until | pt_open_for | pt_rescue | pt_ensure,

        pt_close_struct = (pt_reserved + 29) | pt_close | pt_foldable,


        //TODO: not implemented yet
        pt_comment = (pt_reserved + 30),
        pt_close_comment = pt_comment | pt_close,
        pt_foldable_comment = pt_comment | pt_foldable,
        pt_close_foldable_comment = pt_comment | pt_close| pt_foldable,

        pt_ternary = (pt_reserved + 31),
        pt_close_ternary = pt_ternary | pt_close,

        pt_heredoc = (pt_reserved + 32),
        pt_close_heredoc = pt_heredoc | pt_close,
    };
}

#endif // RUBY_PARA_LEXEM_H
