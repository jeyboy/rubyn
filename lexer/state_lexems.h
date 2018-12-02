#ifndef STATE_LEXEMS_H
#define STATE_LEXEMS_H

#pragma once

#include <qbytearray.h>

#include "misc/defines.h"

//#define LEX(val, flag) (Lexem)(val | flag)
//#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

 // = (1ULL << 1),

enum StackLexemFlag : uint {
    slf_none = 0,

    slf_stack_word = 1,
    slf_stack_delimiter = 2,

    slf_unstack_word = 4,
    slf_unstack_delimiter = 8,

    slf_replace_word = 16,

    slf_word_related = slf_stack_word | slf_unstack_word | slf_replace_word,
    slf_delimiter_related = slf_stack_delimiter | slf_unstack_delimiter,

    slf_stackable = slf_stack_word | slf_stack_delimiter | slf_replace_word,
    slf_unstackable = slf_unstack_word | slf_unstack_delimiter | slf_replace_word
};

enum StateLexem : LEXEM_TYPE {
    lex_min = -10,

    lex_undefined = -9,
    lex_end_line = -8,
    lex_end_doc = -7,

    lex_tab = -6,
    lex_tabs = -5,
    lex_blank = -4,
    lex_blanks = -3,
    lex_ignore = -2,

    lex_default = -1,

    lex_ruby_division_breaker = 1 << 11,
    lex_ruby_ternary_braker = 1 << 12,
//    lex_unary_operator = 1 << 13,
//    lex_binary_operator = 1 << 14,

    lex_error = 0,

    lex_none = 1,

    lex_symbol_key              = 2 | lex_ruby_division_breaker | lex_ruby_ternary_braker,
    lex_dot_dot                 = 3 | lex_ruby_division_breaker | lex_ruby_ternary_braker,  // ..
    lex_dot_dot_dot             = 4 | lex_ruby_division_breaker | lex_ruby_ternary_braker,  // ...
    lex_rocket                  = 5 | lex_ruby_division_breaker | lex_ruby_ternary_braker,  // =>
    lex_comma                   = 6 | lex_ruby_division_breaker | lex_ruby_ternary_braker,  // ,
    lex_wrap_open               = 7 | lex_ruby_division_breaker | lex_ruby_ternary_braker, // (
    lex_open_curly_bracket      = 8 | lex_ruby_division_breaker | lex_ruby_ternary_braker, // {
    lex_open_square_bracket     = 9 | lex_ruby_division_breaker | lex_ruby_ternary_braker, // [
    lex_word                    = 10 | lex_ruby_division_breaker | lex_ruby_ternary_braker, // names and etc
    lex_const                   = 11 | lex_ruby_division_breaker | lex_ruby_ternary_braker,
    lex_var_local               = 12 | lex_ruby_division_breaker | lex_ruby_ternary_braker,
    lex_var_instance            = 13 | lex_ruby_division_breaker | lex_ruby_ternary_braker,
    lex_var_object              = 14 | lex_ruby_division_breaker | lex_ruby_ternary_braker,
    lex_var_global              = 15 | lex_ruby_division_breaker | lex_ruby_ternary_braker,


    lex_operator_assigment                  = 16 | lex_ruby_ternary_braker, // =
    lex_operator_comparison                 = 17 | lex_ruby_ternary_braker, // ==
    lex_operator_equality                   = 18 | lex_ruby_ternary_braker, // ===
    lex_operator_not_equal                  = 19 | lex_ruby_ternary_braker, // !=

    lex_operator_less                       = 20 | lex_ruby_ternary_braker, // <
    lex_operator_less_eql                   = 21 | lex_ruby_ternary_braker, // <=
    lex_operator_great                      = 22 | lex_ruby_ternary_braker, // >
    lex_operator_great_eql                  = 23 | lex_ruby_ternary_braker, // >=

    lex_operator_sort                       = 24 | lex_ruby_ternary_braker, // <=>

    lex_operator_add                        = 25 | lex_ruby_ternary_braker, // +
    lex_operator_add_assigment              = 26 | lex_ruby_ternary_braker, // +=
    lex_operator_increase                   = 27 | lex_ruby_ternary_braker, // ++
    lex_operator_minus                      = 28 | lex_ruby_ternary_braker, // -
    lex_operator_minus_assigment            = 29 | lex_ruby_ternary_braker, // -=
    lex_operator_decrease                   = 30 | lex_ruby_ternary_braker, // --
    lex_operator_multiplication             = 31 | lex_ruby_ternary_braker, // *
    lex_operator_multiplication_assigment   = 32 | lex_ruby_ternary_braker, // *=
    lex_operator_division                   = 33 | lex_ruby_ternary_braker, // /
    lex_operator_division_assigment         = 34 | lex_ruby_ternary_braker, // /=
    lex_operator_exponentiation             = 35 | lex_ruby_ternary_braker, // **
    lex_operator_exponentiation_assigment   = 36 | lex_ruby_ternary_braker, // **=
    lex_operator_modulus                    = 37 | lex_ruby_ternary_braker, // %
    lex_operator_modulus_assigment          = 38 | lex_ruby_ternary_braker, // %=

    lex_operator_bit_and                    = 39 | lex_ruby_ternary_braker, // &
    lex_operator_bit_or                     = 40 | lex_ruby_ternary_braker, // |
    lex_operator_bit_exclusive_or           = 41 | lex_ruby_ternary_braker, // ^
    lex_operator_bit_not                    = 42 | lex_ruby_ternary_braker, // ~
    lex_operator_bit_left_shift             = 43 | lex_ruby_ternary_braker, // <<
    lex_operator_bit_right_shift            = 44 | lex_ruby_ternary_braker, // >>

    lex_operator_bit_and_assigment          = 45 | lex_ruby_ternary_braker, // &=
    lex_operator_bit_or_assigment           = 46 | lex_ruby_ternary_braker, // |=
    lex_operator_bit_exclusive_or_assigment = 47 | lex_ruby_ternary_braker, // ^=
    lex_operator_bit_left_shift_assigment   = 48 | lex_ruby_ternary_braker, // <<=
    lex_operator_bit_right_shift_assigment  = 49 | lex_ruby_ternary_braker, // >>=

    lex_operator_and_word                   = 50 | lex_ruby_ternary_braker,
    lex_operator_and                        = 51 | lex_ruby_ternary_braker, // &&
    lex_operator_and_assigment              = 52 | lex_ruby_ternary_braker, // &&=
    lex_operator_or_word                    = 53 | lex_ruby_ternary_braker,
    lex_operator_or                         = 54 | lex_ruby_ternary_braker, // ||
    lex_operator_or_assigment               = 55 | lex_ruby_ternary_braker, // ||=
    lex_operator_not                        = 56 | lex_ruby_ternary_braker, // !

    lex_operator_safe_navigation = 57, // &. // ruby 2.3+

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

    lex_expression, // abstract

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
    lex_method_def_scope_or_name, // def Goof.tort // Goof in exmp
    lex_method_def_scoped_name, // def self.meth_name // self in exmp
    lex_method_def_scoped_delimiter, // def self.meth_name // dot in exmp
    lex_method_def_name,
    lex_method_def_block,
    lex_method_def_block_end,


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

    lex_class,

    lex_class_def,
    lex_class_def_name,
    lex_class_def_extension,
    lex_class_def_extender,
    lex_class_def_inheritance,
    lex_class_def_ancestor,
    lex_class_def_resolution,
    lex_class_def_block,
    lex_class_def_block_end,

    lex_class_def_short,
    lex_class_def_short_accessing,
    lex_class_def_short_method,
    lex_class_def_short_block,
    lex_class_def_short_block_end,

    lex_module,

    lex_module_def,
    lex_module_def_name,
    lex_module_def_resolution,
    lex_module_def_block,
    lex_module_def_block_end,


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
    lex_include_obj, // part of name
    lex_include_resolution, // ::
    lex_include_name, // full name

    lex_extend, // extend some obj
    lex_extend_obj, // part of name
    lex_extend_resolution, // ::
    lex_extend_name, // full name

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


    lex_switch,
    lex_switch_target,
    lex_switch_block,
    lex_switch_block_end,

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

#endif // STATE_LEXEMS_H
