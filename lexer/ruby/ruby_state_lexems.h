#ifndef RUBY_STATE_LEXEMS_H
#define RUBY_STATE_LEXEMS_H

#pragma once

#include <qbytearray.h>

#include "misc/defines.h"
#include "lexer/state_lexem.h"

//#define LEX(val, flag) (Lexem)(val | flag)
//#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

 // = (1ULL << 1),

namespace Ruby {
    enum StateLexem : LEXEM_TYPE {

        lex_ruby_division_breaker = 1 << 9, // 512
        lex_ruby_ternary_braker = 1 << 10, // 1024
//        1 << 11// 2048
//        1 << 12// 4096
//        1 << 13// 8192
//        1 << 14// 16384
//        1 << 15// 32768

        DefaultStateLexems,

        lex_symbol_key              = (lex_reserved + 1) | lex_ruby_division_breaker | lex_ruby_ternary_braker,
        lex_dot_dot                 = (lex_reserved + 2) | lex_ruby_division_breaker | lex_ruby_ternary_braker,  // ..
        lex_dot_dot_dot             = (lex_reserved + 3) | lex_ruby_division_breaker | lex_ruby_ternary_braker,  // ...
        lex_rocket                  = (lex_reserved + 4) | lex_ruby_division_breaker | lex_ruby_ternary_braker,  // =>
        lex_comma                   = (lex_reserved + 5) | lex_ruby_division_breaker | lex_ruby_ternary_braker,  // ,
        lex_wrap_open               = (lex_reserved + 6) | lex_ruby_division_breaker | lex_ruby_ternary_braker, // (
        lex_open_curly_bracket      = (lex_reserved + 7) | lex_ruby_division_breaker | lex_ruby_ternary_braker, // {
        lex_open_square_bracket     = (lex_reserved + 8) | lex_ruby_division_breaker | lex_ruby_ternary_braker, // [
        lex_word                    = (lex_reserved + 9) | lex_ruby_division_breaker | lex_ruby_ternary_braker, // names and etc
        lex_const                   = (lex_reserved + 10) | lex_ruby_division_breaker | lex_ruby_ternary_braker,
        lex_var_local               = (lex_reserved + 11) | lex_ruby_division_breaker | lex_ruby_ternary_braker,
        lex_var_instance            = (lex_reserved + 12) | lex_ruby_division_breaker | lex_ruby_ternary_braker,
        lex_var_object              = (lex_reserved + 13) | lex_ruby_division_breaker | lex_ruby_ternary_braker,
        lex_var_global              = (lex_reserved + 14) | lex_ruby_division_breaker | lex_ruby_ternary_braker,
        lex_var_or_method           = (lex_reserved + 15) | lex_ruby_division_breaker | lex_ruby_ternary_braker,
        lex_unknown_var_or_method   = (lex_reserved + 16) | lex_ruby_division_breaker | lex_ruby_ternary_braker,

        // ...

        lex_operator_assigment                  = (lex_reserved + 25) | lex_ruby_ternary_braker, // =
        lex_operator_comparison                 = (lex_reserved + 26) | lex_ruby_ternary_braker, // ==
        lex_operator_equality                   = (lex_reserved + 27) | lex_ruby_ternary_braker, // ===
        lex_operator_not_equal                  = (lex_reserved + 28) | lex_ruby_ternary_braker, // !=

        lex_operator_less                       = (lex_reserved + 29) | lex_ruby_ternary_braker, // <
        lex_operator_less_eql                   = (lex_reserved + 30) | lex_ruby_ternary_braker, // <=
        lex_operator_great                      = (lex_reserved + 31) | lex_ruby_ternary_braker, // >
        lex_operator_great_eql                  = (lex_reserved + 32) | lex_ruby_ternary_braker, // >=

        lex_operator_sort                       = (lex_reserved + 33) | lex_ruby_ternary_braker, // <=>

        lex_operator_add                        = (lex_reserved + 34) | lex_ruby_ternary_braker, // +
        lex_operator_add_assigment              = (lex_reserved + 35) | lex_ruby_ternary_braker, // +=
        lex_operator_increase                   = (lex_reserved + 36) | lex_ruby_ternary_braker, // ++
        lex_operator_minus                      = (lex_reserved + 37) | lex_ruby_ternary_braker, // -
        lex_operator_minus_assigment            = (lex_reserved + 38) | lex_ruby_ternary_braker, // -=
        lex_operator_decrease                   = (lex_reserved + 39) | lex_ruby_ternary_braker, // --
        lex_operator_multiplication             = (lex_reserved + 40) | lex_ruby_ternary_braker, // *
        lex_operator_multiplication_assigment   = (lex_reserved + 41) | lex_ruby_ternary_braker, // *=
        lex_operator_division                   = (lex_reserved + 42) | lex_ruby_ternary_braker, // /
        lex_operator_division_assigment         = (lex_reserved + 43) | lex_ruby_ternary_braker, // /=
        lex_operator_exponentiation             = (lex_reserved + 44) | lex_ruby_ternary_braker, // **
        lex_operator_exponentiation_assigment   = (lex_reserved + 45) | lex_ruby_ternary_braker, // **=
        lex_operator_modulus                    = (lex_reserved + 46) | lex_ruby_ternary_braker, // %
        lex_operator_modulus_assigment          = (lex_reserved + 47) | lex_ruby_ternary_braker, // %=

        lex_operator_bit_and                    = (lex_reserved + 48) | lex_ruby_ternary_braker, // &
        lex_operator_bit_or                     = (lex_reserved + 49) | lex_ruby_ternary_braker, // |
        lex_operator_bit_exclusive_or           = (lex_reserved + 50) | lex_ruby_ternary_braker, // ^
        lex_operator_bit_not                    = (lex_reserved + 51) | lex_ruby_ternary_braker, // ~
        lex_operator_bit_left_shift             = (lex_reserved + 52) | lex_ruby_ternary_braker, // <<
        lex_operator_bit_right_shift            = (lex_reserved + 53) | lex_ruby_ternary_braker, // >>

        lex_operator_bit_and_assigment          = (lex_reserved + 54) | lex_ruby_ternary_braker, // &=
        lex_operator_bit_or_assigment           = (lex_reserved + 55) | lex_ruby_ternary_braker, // |=
        lex_operator_bit_exclusive_or_assigment = (lex_reserved + 56) | lex_ruby_ternary_braker, // ^=
        lex_operator_bit_left_shift_assigment   = (lex_reserved + 57) | lex_ruby_ternary_braker, // <<=
        lex_operator_bit_right_shift_assigment  = (lex_reserved + 58) | lex_ruby_ternary_braker, // >>=

        lex_operator_and_literal                = (lex_reserved + 59) | lex_ruby_ternary_braker,
        lex_operator_and                        = (lex_reserved + 60) | lex_ruby_ternary_braker, // &&
        lex_operator_and_assigment              = (lex_reserved + 61) | lex_ruby_ternary_braker, // &&=
        lex_operator_or_literal                 = (lex_reserved + 62) | lex_ruby_ternary_braker,
        lex_operator_or                         = (lex_reserved + 63) | lex_ruby_ternary_braker, // ||
        lex_operator_or_assigment               = (lex_reserved + 64) | lex_ruby_ternary_braker, // ||=
        lex_operator_not                        = (lex_reserved + 65) | lex_ruby_ternary_braker, // !

        lex_operator_req_match                  = (lex_reserved + 66) | lex_ruby_ternary_braker, // =~
        lex_operator_req_not_match              = (lex_reserved + 67) | lex_ruby_ternary_braker, // !~

        lex_operator_safe_navigation = (lex_reserved + 68), // &. // ruby 2.3+

        lex_loop,
        lex_yield,
        lex_raise,

        lex_super,
        lex_self,

        lex_bin,
        lex_oct,
        lex_dec,
        lex_hex,
        lex_float,
        lex_double,

//        lex_expression, // abstract

        lex_symbol,
        lex_char_sequence,

        lex_var_scoped, // variables in blocks and etc // |a, b|

        lex_interpolation, // #{
        lex_interpolation_close, // }
        lex_wrap_close, // )

        lex_dot,  // .
        lex_question_mark,  // ?
        lex_colon,  // :
        lex_semicolon,  // ;
        lex_resolution,  // ::
        lex_close_curly_bracket, // }
        lex_close_square_bracket, // ]


        lex_method_def,
        lex_method_def_pre_name,
        lex_method_def_scope_or_name, // def Goof.tort // Goof in exmp
        lex_method_def_post_scope_or_name,
        lex_method_def_scoped_name, // def self.meth_name // self in exmp
        lex_method_def_scoped_delimiter, // def self.meth_name // dot in exmp
        lex_method_def_name,
        lex_method_def_post_name,
        lex_method_def_block_start,
//        lex_method_def_block_end,


        lex_method_def_args_start,
        lex_method_def_arg_attr, // const
        lex_method_def_arg_type, // int
        lex_method_def_arg_access_type, // * & and etc
    //    lex_method_def_arg_access_typed, // * & and etc
        lex_method_def_arg_name,
        lex_method_def_arg_assign,
        lex_method_def_arg_assign_val,
        lex_method_def_arg_splitter,
        lex_method_def_args_end,
        lex_method_def_arg_assigment, // =
        lex_method_def_arg_assigment_wrap, // (
        lex_method_def_arg_assigment_curly, // {
        lex_method_def_arg_assigment_square, // [


        lex_method_def_vars_start,
        lex_method_def_var_attr, // const
        lex_method_def_var_type, // int
        lex_method_def_var_access_type, // * & and etc
    //    lex_method_def_var_access_typed, // * & and etc
        lex_method_def_var_name,
        lex_method_def_var_assign,
        lex_method_def_var_assign_val,
        lex_method_def_vars_splitter,
    //    lex_method_def_vars_end,

    //    lex_predefined,
        lex_method,
        lex_method_access,

        lex_method_call_args_start,
        lex_method_call_args_close,
        lex_method_call_arg_entry,
        lex_method_call_args_splitter,

        lex_method_call_vars_start,
        lex_method_call_var_entry,
        lex_method_call_vars_splitter,
        lex_method_call_vars_end,


        lex_method_call_block,
        lex_method_call_block_vars_start,
        lex_method_call_block_var_name,
        lex_method_call_block_vars_splitter,
        lex_method_call_block_vars_end,
        lex_method_call_block_end,

//        lex_class,

        lex_class_def,
        lex_class_def_prename, // blank after def
        lex_class_def_name_part,
        lex_class_def_name_end,

        lex_class_def_extension, // class << self
        lex_class_def_extender,

        lex_class_def_resolution, // class A::B
        lex_class_def_ancestor,

        lex_class_def_inheritance, // class A < B

//        lex_class_def_block,
//        lex_class_def_block_end,

//        lex_class_def_short,
//        lex_class_def_short_accessing,
//        lex_class_def_short_method,
//        lex_class_def_short_block,
//        lex_class_def_short_block_end,

//        lex_module,

        lex_module_def,
        lex_module_def_prename,
        lex_module_def_name_part,
        lex_module_def_name_end,

        lex_module_def_resolution,
        lex_module_def_ancestor,


        lex_lambda_def,
        lex_lambda_def_vars_start,
        lex_lambda_def_var_attr, // const
        lex_lambda_def_var_type, // int
        lex_lambda_def_var_access_type, // * & and etc
        lex_lambda_def_var_name,
        lex_lambda_def_vars_splitter,
        lex_lambda_def_vars_end,
        lex_lambda_def_block,
        lex_lambda_def_block_end,


        lex_proc_def,
        lex_proc_def_block,
        lex_proc_def_block_end,
        lex_proc_def_vars_start,
        lex_proc_def_var_attr, // const
        lex_proc_def_var_type, // int
        lex_proc_def_var_access_type, // * & and etc
        lex_proc_def_var_name,
        lex_proc_def_vars_splitter,
        lex_proc_def_vars_end,


        lex_inline_commentary_content,

        lex_commentary_start,
        lex_commentary_content,
        lex_commentary_end,

        lex_literal_spec, // \n, \t
        lex_literal_code, // \u2344, \xf4

        lex_command_start,
        lex_command_content,
        lex_command_interception,
        lex_command_end,

        lex_string_start,
        lex_string_content,
        lex_string_end,

        lex_estring_start, // "
        lex_estring_content,
        lex_estring_interception,
        lex_estring_end,

        lex_percent_presentation_start, // %n/.../
        lex_percent_presentation_content,
        lex_percent_presentation_end,

        lex_epercent_presentation_start, // %N/.../
        lex_epercent_presentation_content,
        lex_epercent_presentation_interception,
        lex_epercent_presentation_end,

        // <<HEREDOC ... HEREDOC // <<-HEREDOC ... HEREDOC // <<~HEREDOC .. HEREDOC
        lex_heredoc_mark,
        lex_heredoc_close_mark,
        lex_heredoc_start,
        lex_heredoc_content,
        lex_heredoc_interception,
        lex_heredoc_end,

        lex_heredoc_intended_mark,
        lex_heredoc_intended_start,
        lex_heredoc_intended_content,
        lex_heredoc_intended_end,

        lex_eheredoc_mark,
        lex_eheredoc_start,
        lex_eheredoc_content,
        lex_eheredoc_end,

        lex_eheredoc_intended_mark,
        lex_eheredoc_intended_start,
        lex_eheredoc_intended_content,
        lex_eheredoc_intended_end,

        lex_cheredoc_mark,
        lex_cheredoc_start,
        lex_cheredoc_content,
        lex_cheredoc_end,

        lex_cheredoc_intended_mark,
        lex_cheredoc_intended_start,
        lex_cheredoc_intended_content,
        lex_cheredoc_intended_end,
        //////////////////////////////////////


        lex_regexp_start, // /\a+/
        lex_regexp_content,
        lex_regexp_interception,
        lex_regexp_end,
        lex_regexp_flags,

        lex_interception_close,

        lex_require, // require some source
        lex_require_path,

        lex_include, // include some obj
        lex_include_pre_obj, // space before name
        lex_include_obj_part, // part of name
        lex_include_resolution, // ::
        lex_include_splitter, // ,
        lex_include_end,

        lex_extend, // extend some obj
        lex_prepend, // prepend some obj

        lex_undef, // undef method
        lex_undef_arg,
        lex_undef_arg_splitter,

        lex_visibility_scope, // public, private etc // use one space pad in format // https://fabiokung.com/2010/04/05/ruby-indentation-for-access-modifiers-and-their-sections/
        lex_visibility_scope_arg, // public :show, :index and etc
        lex_visibility_scope_arg_splitter, // ,

        lex_alias,
        lex_alias_base_name,
        lex_alias_alt_name,


    //    lex_wrap_start, // (


        lex_hash_start,
        lex_hash_item, // key and val
        lex_hash_key,
        lex_hash_key_with_relation,
        lex_hash_key_relation, // =>
        lex_hash_val,
        lex_hash_splitter,
        lex_hash_end,


        lex_array_start,
        lex_array_item,
        lex_array_splitter,
        lex_array_end,


        lex_ternary_main_start, // ? :
        lex_ternary_main_val, // ? :
        lex_ternary_alt_start,
        lex_ternary_alt_val,

        lex_then,
        lex_in,

        lex_unless,
        lex_unless_rule,
        lex_unless_then,
        lex_unless_block,
        lex_unless_block_end,

        lex_if,
        lex_if_rule,
        lex_if_then,
        lex_if_block,
        lex_if_block_end,

        lex_elsif,
        lex_elsif_rule,
        lex_elsif_then,
        lex_elsif_block,
        lex_elsif_block_end,

        lex_else,
        lex_else_block,
        lex_else_block_end,


//        lex_switch,
//        lex_switch_target,
//        lex_switch_block,
//        lex_switch_block_end,

        lex_case,
        lex_case_target,
        lex_case_target_block,
        lex_case_target_block_end,

        lex_when,
        lex_when_target,
        lex_when_target_splitter,
        lex_when_then,
        lex_when_else,
        lex_when_block,
        lex_when_block_end,


        lex_while,
        lex_while_rule,
        lex_while_block,
        lex_while_block_end,

        lex_until,
        lex_until_rule,
        lex_until_block,
        lex_until_block_end,

        lex_for,
        lex_for_vars_start,
        lex_for_var,
        lex_for_vars_splitter,
        lex_for_vars_end,

        lex_for_in,
        lex_for_in_target,

        lex_loop_break,
        lex_loop_redo,
        lex_loop_next,

        lex_do,
        lex_do_block_start,
        lex_do_block_vars_start,
        lex_do_block_var_access_type, // * & and etc
        lex_do_block_var_name,
        lex_do_block_vars_splitter,
        lex_do_block_vars_end,

        lex_inline_block_start,

        lex_inline_do_block_start,
        lex_inline_do_block_vars_start,
        lex_inline_do_block_var_access_type, // * & and etc
        lex_inline_do_block_var_name,
        lex_inline_do_block_vars_splitter,
        lex_inline_do_block_vars_end,

        lex_begin,
        lex_end,

        lex_block_start,
        lex_block_rescue,
        lex_block_ensure,
        lex_block_retry,
    //    lex_block_end,
    //    lex_inline_block_end, lex_close_curly_bracket


        lex_return,


        lex_global_pre_hook,
        lex_global_post_hook,
        lex_end_of_code,
    };
}

#endif // RUBY_STATE_LEXEMS_H
