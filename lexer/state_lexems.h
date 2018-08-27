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

    slf_word_related = slf_stack_word | slf_unstack_word,
    slf_delimiter_related = slf_stack_delimiter | slf_unstack_delimiter
};

enum StateLexem : LEXEM_TYPE {
    lex_none = -1,

    lex_error = 0,

    lex_yield,
    lex_raise,

    lex_super,
    lex_self,

    lex_expression, // abstract

    lex_unary_operator,
    lex_binary_operator,

    lex_bin,
    lex_oct,
    lex_dec,
    lex_hex,
    lex_float,
    lex_double,

    lex_symbol_key,
    lex_symbol,

    lex_var_scoped, // variables in blocks and etc // |a, b|

    lex_division_braker_start,

    lex_dot_dot,  // ..
    lex_dot_dot_dot,  // ...
    lex_rocket,  // =>
    lex_comma,  // ,
    lex_open_curly_bracket, // {
    lex_open_square_bracket, // [
    lex_word, // names and etc
    lex_const,
    lex_var_local,
    lex_var_instance,
    lex_var_object,
    lex_var_global,

    lex_division_braker_end,

    lex_interpolation, // #{
    lex_interpolation_close, // }

    lex_dot,  // .
    lex_colon,  // :
    lex_semicolon,  // ;
    lex_resolution,  // ::
    lex_close_curly_bracket, // }
    lex_close_square_bracket, // ]


    lex_operator_assigment, // =
    lex_operator_comparison, // ==
    lex_operator_equality, // ===
    lex_operator_not_equal, // !=

    lex_operator_less, // <
    lex_operator_less_eql, // <=
    lex_operator_great, // >
    lex_operator_great_eql, // >=

    lex_operator_sort, // <=>

    lex_operator_add, // +
    lex_operator_add_assigment, // +=
    lex_operator_increase, // ++
    lex_operator_minus, // -
    lex_operator_minus_assigment, // -=
    lex_operator_decrease, // --
    lex_operator_multiplication, // *
    lex_operator_multiplication_assigment, // *=
    lex_operator_division, // /
    lex_operator_division_assigment, // /=
    lex_operator_exponentiation, // **
    lex_operator_exponentiation_assigment, // **=
    lex_operator_modulus, // %
    lex_operator_modulus_assigment, // %=

    lex_operator_safe_navigation, // &. // ruby 2.3+

    lex_operator_bit_and, // &
    lex_operator_bit_or, // |
    lex_operator_bit_exclusive_or, // ^
    lex_operator_bit_not, // ~
    lex_operator_bit_left_shift, // <<
    lex_operator_bit_right_shift, // >>

    lex_operator_and, // &&
    lex_operator_or, // ||
    lex_operator_or_assigment, // ||=
    lex_operator_not, // !


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

    lex_inline_commentary,

    lex_commentary_content,
    lex_commentary_start,
    lex_commentary_continue,
    lex_commentary_end,

    lex_command_content,
    lex_command_start,
    lex_command_interception,
//    lex_command_intercepted,
    lex_command_continue,
    lex_command_end,

    lex_string_content,
    lex_string_start,
    lex_string_continue,
    lex_string_end,

    lex_estring_content,
    lex_estring_start, // "
    lex_estring_interception,
//    lex_estring_intercepted,
    lex_estring_continue,
    lex_estring_end,

    lex_percent_presentation_content,
    lex_percent_presentation_start, // %n/.../
    lex_percent_presentation_continue,
    lex_percent_presentation_end,


    lex_epercent_presentation_content,
    lex_epercent_presentation_start, // %N/.../
    lex_epercent_presentation_interception,
//    lex_epercent_presentation_intercepted,
    lex_epercent_presentation_continue,
    lex_epercent_presentation_end,

    // <<HEREDOC ... HEREDOC // <<-HEREDOC ... HEREDOC // <<~HEREDOC .. HEREDOC
    lex_heredoc_mark,
    lex_heredoc_content,
    lex_heredoc_start,
    lex_heredoc_continue,
    lex_heredoc_end,

    lex_heredoc_intended_mark,
    lex_heredoc_intended_content,
    lex_heredoc_intended_start,
    lex_heredoc_intended_continue,

    lex_eheredoc_mark,
    lex_eheredoc_content,
    lex_eheredoc_start,
    lex_eheredoc_interception,
//    lex_eheredoc_intercepted,
    lex_eheredoc_continue,

    lex_eheredoc_intended_mark,
    lex_eheredoc_intended_content,
    lex_eheredoc_intended_start,
    lex_eheredoc_intended_interception,
//    lex_eheredoc_intended_intercepted,
    lex_eheredoc_intended_continue,

    lex_cheredoc_mark,
    lex_cheredoc_content,
    lex_cheredoc_start,
    lex_cheredoc_interception,
//    lex_cheredoc_intercepted,
    lex_cheredoc_continue,

    lex_cheredoc_intended_mark,
    lex_cheredoc_intended_content,
    lex_cheredoc_intended_start,
    lex_cheredoc_intended_interception,
//    lex_cheredoc_intended_intercepted,
    lex_cheredoc_intended_continue,
    //////////////////////////////////////


    lex_regexp_start, // /\a+/
    lex_regexp_content,
    lex_regexp_interception,
//    lex_regexp_intercepted,
    lex_regexp_continue,
    lex_regexp_end,
    lex_regexp_flags,


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


    lex_wrap_start, // (
    lex_wrap_end, // )


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

    lex_block_end,
//    lex_inline_block_end, lex_close_curly_bracket


    lex_return,


    lex_global_pre_hook,
    lex_global_post_hook,
    lex_end_of_code,


    lex_undefined,
    lex_end_line,
    lex_end_doc,
    lex_tab,
    lex_tabs,
    lex_blank,
    lex_blanks,
    lex_ignore,

//    lef_max_token,

//    lex_def_val_scoped = 1000,

//    lex_max = lef_max_token + lex_def_val_scoped,

    lex_max
};










//enum StackLexemFlag : uint {
//    slf_none = 0,

//    slf_stack_word = 1,
//    slf_stack_delimiter = 2,

//    slf_unstack_word = 4,
//    slf_unstack_delimiter = 8,

//    slf_word_related = slf_stack_word | slf_unstack_word,
//    slf_delimiter_related = slf_stack_delimiter | slf_unstack_delimiter
//};

//enum StateLexem : LEXEM_TYPE {
//    lex_none = -1,

//    lex_error = 0,

//    lex_yield,
//    lex_raise,

//    lex_super,
//    lex_self,

//    lex_expression, // abstract
//    lex_word, // names and etc

//    lex_unary_operator,
//    lex_binary_operator,

//    lex_bin,
//    lex_oct,
//    lex_dec,
//    lex_hex,
//    lex_float,
//    lex_double,

//    lex_symbol_key,
//    lex_symbol,
//    lex_const,
//    lex_var_scoped, // variables in blocks and etc // |a, b|
//    lex_var_local,
//    lex_var_instance,
//    lex_var_object,
//    lex_var_global,

//    lex_interpolation, // #{
//    lex_interpolation_close, // }

//    lex_dot,  // .
//    lex_dot_dot,  // ..
//    lex_dot_dot_dot,  // ...
//    lex_rocket,  // =>
//    lex_colon,  // :
//    lex_semicolon,  // ;
//    lex_resolution,  // ::
//    lex_comma,  // ,
//    lex_open_curly_bracket, // {
//    lex_close_curly_bracket, // }
//    lex_open_square_bracket, // [
//    lex_close_square_bracket, // ]


//    lex_operator_assigment, // =
//    lex_operator_comparison, // ==
//    lex_operator_equality, // ===
//    lex_operator_not_equal, // !=

//    lex_operator_less, // <
//    lex_operator_less_eql, // <=
//    lex_operator_great, // >
//    lex_operator_great_eql, // >=

//    lex_operator_sort, // <=>

//    lex_operator_add, // +
//    lex_operator_add_assigment, // +=
//    lex_operator_increase, // ++
//    lex_operator_minus, // -
//    lex_operator_minus_assigment, // -=
//    lex_operator_decrease, // --
//    lex_operator_multiplication, // *
//    lex_operator_multiplication_assigment, // *=
//    lex_operator_division, // /
//    lex_operator_division_assigment, // /=
//    lex_operator_exponentiation, // **
//    lex_operator_exponentiation_assigment, // **=
//    lex_operator_modulus, // %
//    lex_operator_modulus_assigment, // %=

//    lex_operator_safe_navigation, // &. // ruby 2.3+

//    lex_operator_bit_and, // &
//    lex_operator_bit_or, // |
//    lex_operator_bit_exclusive_or, // ^
//    lex_operator_bit_not, // ~
//    lex_operator_bit_left_shift, // <<
//    lex_operator_bit_right_shift, // >>

//    lex_operator_and, // &&
//    lex_operator_or, // ||
//    lex_operator_or_assigment, // ||=
//    lex_operator_not, // !


//    lex_method_def,
//    lex_method_def_scope_or_name, // def Goof.tort // Goof in exmp
//    lex_method_def_scoped_name, // def self.meth_name // self in exmp
//    lex_method_def_scoped_delimiter, // def self.meth_name // dot in exmp
//    lex_method_def_name,
//    lex_method_def_block,
//    lex_method_def_block_end,


//    lex_method_def_args_start,
//    lex_method_def_arg_attr, // const
//    lex_method_def_arg_type, // int
//    lex_method_def_arg_access_type, // * & and etc
////    lex_method_def_arg_access_typed, // * & and etc
//    lex_method_def_arg_name,
//    lex_method_def_arg_assign,
//    lex_method_def_arg_assign_val,
//    lex_method_def_arg_splitter,
//    lex_method_def_args_end,

//    lex_method_def_vars_start,
//    lex_method_def_var_attr, // const
//    lex_method_def_var_type, // int
//    lex_method_def_var_access_type, // * & and etc
////    lex_method_def_var_access_typed, // * & and etc
//    lex_method_def_var_name,
//    lex_method_def_var_assign,
//    lex_method_def_var_assign_val,
//    lex_method_def_vars_splitter,
////    lex_method_def_vars_end,

//    lex_method,
//    lex_method_access,

//    lex_method_call_args_start,
//    lex_method_call_args_close,
//    lex_method_call_arg_entry,
//    lex_method_call_args_splitter,

//    lex_method_call_vars_start,
//    lex_method_call_var_entry,
//    lex_method_call_vars_splitter,
//    lex_method_call_vars_end,


//    lex_method_call_block,
//    lex_method_call_block_vars_start,
//    lex_method_call_block_var_name,
//    lex_method_call_block_vars_splitter,
//    lex_method_call_block_vars_end,
//    lex_method_call_block_end,

//    lex_class,

//    lex_class_def,
//    lex_class_def_name,
//    lex_class_def_extension,
//    lex_class_def_extender,
//    lex_class_def_inheritance,
//    lex_class_def_ancestor,
//    lex_class_def_resolution,
//    lex_class_def_block,
//    lex_class_def_block_end,

//    lex_class_def_short,
//    lex_class_def_short_accessing,
//    lex_class_def_short_method,
//    lex_class_def_short_block,
//    lex_class_def_short_block_end,

//    lex_module,

//    lex_module_def,
//    lex_module_def_name,
//    lex_module_def_resolution,
//    lex_module_def_block,
//    lex_module_def_block_end,


//    lex_lambda_def,
//    lex_lambda_def_vars_start,
//    lex_lambda_def_var_attr, // const
//    lex_lambda_def_var_type, // int
//    lex_lambda_def_var_access_type, // * & and etc
//    lex_lambda_def_var_name,
//    lex_lambda_def_vars_splitter,
//    lex_lambda_def_vars_end,
//    lex_lambda_def_block,
//    lex_lambda_def_block_end,


//    lex_proc_def,
//    lex_proc_def_block,
//    lex_proc_def_block_end,
//    lex_proc_def_vars_start,
//    lex_proc_def_var_attr, // const
//    lex_proc_def_var_type, // int
//    lex_proc_def_var_access_type, // * & and etc
//    lex_proc_def_var_name,
//    lex_proc_def_vars_splitter,
//    lex_proc_def_vars_end,

//    lex_inline_commentary,

//    lex_commentary_content,
//    lex_commentary_start,
//    lex_commentary_continue,
//    lex_commentary_end,

//    lex_command_content,
//    lex_command_start,
//    lex_command_interception,
////    lex_command_intercepted,
//    lex_command_continue,
//    lex_command_end,

//    lex_string_content,
//    lex_string_start,
//    lex_string_continue,
//    lex_string_end,

//    lex_estring_content,
//    lex_estring_start, // "
//    lex_estring_interception,
////    lex_estring_intercepted,
//    lex_estring_continue,
//    lex_estring_end,

//    lex_percent_presentation_content,
//    lex_percent_presentation_start, // %n/.../
//    lex_percent_presentation_continue,
//    lex_percent_presentation_end,


//    lex_epercent_presentation_content,
//    lex_epercent_presentation_start, // %N/.../
//    lex_epercent_presentation_interception,
////    lex_epercent_presentation_intercepted,
//    lex_epercent_presentation_continue,
//    lex_epercent_presentation_end,

//    // <<HEREDOC ... HEREDOC // <<-HEREDOC ... HEREDOC // <<~HEREDOC .. HEREDOC
//    lex_heredoc_mark,
//    lex_heredoc_content,
//    lex_heredoc_start,
//    lex_heredoc_continue,
//    lex_heredoc_end,

//    lex_heredoc_intended_mark,
//    lex_heredoc_intended_content,
//    lex_heredoc_intended_start,
//    lex_heredoc_intended_continue,

//    lex_eheredoc_mark,
//    lex_eheredoc_content,
//    lex_eheredoc_start,
//    lex_eheredoc_interception,
////    lex_eheredoc_intercepted,
//    lex_eheredoc_continue,

//    lex_eheredoc_intended_mark,
//    lex_eheredoc_intended_content,
//    lex_eheredoc_intended_start,
//    lex_eheredoc_intended_interception,
////    lex_eheredoc_intended_intercepted,
//    lex_eheredoc_intended_continue,

//    lex_cheredoc_mark,
//    lex_cheredoc_content,
//    lex_cheredoc_start,
//    lex_cheredoc_interception,
////    lex_cheredoc_intercepted,
//    lex_cheredoc_continue,

//    lex_cheredoc_intended_mark,
//    lex_cheredoc_intended_content,
//    lex_cheredoc_intended_start,
//    lex_cheredoc_intended_interception,
////    lex_cheredoc_intended_intercepted,
//    lex_cheredoc_intended_continue,
//    //////////////////////////////////////


//    lex_regexp_start, // /\a+/
//    lex_regexp_content,
//    lex_regexp_interception,
////    lex_regexp_intercepted,
//    lex_regexp_continue,
//    lex_regexp_end,
//    lex_regexp_flags,


//    lex_require, // require some source
//    lex_require_path,

//    lex_include, // include some obj
//    lex_include_obj, // part of name
//    lex_include_resolution, // ::
//    lex_include_name, // full name

//    lex_extend, // extend some obj
//    lex_extend_obj, // part of name
//    lex_extend_resolution, // ::
//    lex_extend_name, // full name

//    lex_undef, // undef method
//    lex_undef_arg,
//    lex_undef_arg_splitter,

//    lex_visibility_scope, // public, private etc // use one space pad in format // https://fabiokung.com/2010/04/05/ruby-indentation-for-access-modifiers-and-their-sections/
//    lex_visibility_scope_arg, // public :show, :index and etc
//    lex_visibility_scope_arg_splitter, // ,

//    lex_alias,
//    lex_alias_base_name,
//    lex_alias_alt_name,


//    lex_wrap_start, // (
//    lex_wrap_end, // )


//    lex_hash_start,
//    lex_hash_item, // key and val
//    lex_hash_key,
//    lex_hash_key_with_relation,
//    lex_hash_key_relation, // =>
//    lex_hash_val,
//    lex_hash_splitter,
//    lex_hash_end,


//    lex_array_start,
//    lex_array_item,
//    lex_array_splitter,
//    lex_array_end,


//    lex_ternary_main_start, // ? :
//    lex_ternary_main_val, // ? :
//    lex_ternary_alt_start,
//    lex_ternary_alt_val,

//    lex_then,
//    lex_in,

//    lex_unless,
//    lex_unless_rule,
//    lex_unless_then,
//    lex_unless_block,
//    lex_unless_block_end,

//    lex_if,
//    lex_if_rule,
//    lex_if_then,
//    lex_if_block,
//    lex_if_block_end,

//    lex_elsif,
//    lex_elsif_rule,
//    lex_elsif_then,
//    lex_elsif_block,
//    lex_elsif_block_end,

//    lex_else,
//    lex_else_block,
//    lex_else_block_end,


//    lex_switch,
//    lex_switch_target,
//    lex_switch_block,
//    lex_switch_block_end,

//    lex_case,
//    lex_case_target,
//    lex_case_target_block,
//    lex_case_target_block_end,

//    lex_when,
//    lex_when_target,
//    lex_when_target_splitter,
//    lex_when_then,
//    lex_when_else,
//    lex_when_block,
//    lex_when_block_end,


//    lex_while,
//    lex_while_rule,
//    lex_while_block,
//    lex_while_block_end,

//    lex_until,
//    lex_until_rule,
//    lex_until_block,
//    lex_until_block_end,

//    lex_for,
//    lex_for_vars_start,
//    lex_for_var,
//    lex_for_vars_splitter,
//    lex_for_vars_end,

//    lex_for_in,
//    lex_for_in_target,

//    lex_loop_break,
//    lex_loop_redo,
//    lex_loop_next,

//    lex_do,
//    lex_do_block_start,
//    lex_do_block_vars_start,
//    lex_do_block_var_access_type, // * & and etc
//    lex_do_block_var_name,
//    lex_do_block_vars_splitter,
//    lex_do_block_vars_end,

//    lex_inline_block_start,

//    lex_inline_do_block_start,
//    lex_inline_do_block_vars_start,
//    lex_inline_do_block_var_access_type, // * & and etc
//    lex_inline_do_block_var_name,
//    lex_inline_do_block_vars_splitter,
//    lex_inline_do_block_vars_end,

//    lex_begin,
//    lex_end,

//    lex_block_start,
//    lex_block_rescue,
//    lex_block_ensure,
//    lex_block_retry,

//    lex_block_end,
////    lex_inline_block_end, lex_close_curly_bracket


//    lex_return,


//    lex_global_pre_hook,
//    lex_global_post_hook,
//    lex_end_of_code,


//    lex_undefined,
//    lex_end_line,
//    lex_end_doc,
//    lex_tab,
//    lex_tabs,
//    lex_blank,
//    lex_blanks,
//    lex_ignore,

////    lef_max_token,

////    lex_def_val_scoped = 1000,

////    lex_max = lef_max_token + lex_def_val_scoped,

//    lex_max
//};

//struct Lexems {
//    static QByteArray toStr(const Lexem & lexem) {
//        switch(lexem) {
//            case lex_error: return QByteArrayLiteral("error_token");
//            case lex_warning: return QByteArrayLiteral("warning_token");
//            case lex_notice: return QByteArrayLiteral("notice_token");
//            case lex_none: return QByteArrayLiteral("none_token");

//            case lex_label: return QByteArrayLiteral("mark_token");
//            case lex_keyword: return QByteArrayLiteral("key_token");
//            case lex_numeric: return QByteArrayLiteral("numeric_token");
//            case lex_var: return QByteArrayLiteral("name_token");
//            case lex_name_def: return QByteArrayLiteral("def_name_token");
//            case lex_commentary: return QByteArrayLiteral("commentary_token");
//            case lex_string: return QByteArrayLiteral("string_token");
//            case lex_regexp: return QByteArrayLiteral("regexp_token");
//            case lex_name_call: return QByteArrayLiteral("name_call_token");


//            case lex_super: return QByteArrayLiteral("super_token");
//            case lex_self: return QByteArrayLiteral("self_token");

//            case lex_expression: return QByteArrayLiteral("expression_token");
//            case lex_word: return QByteArrayLiteral("word_token");

//            case lex_unary_operator: return QByteArrayLiteral("unary_operator_token");
//            case lex_binary_operator: return QByteArrayLiteral("binary_operator_token");

//            case lex_bin: return QByteArrayLiteral("bin_numb_token");
//            case lex_oct: return QByteArrayLiteral("oct_numb_token");
//            case lex_dec: return QByteArrayLiteral("dec_numb_token");
//            case lex_hex: return QByteArrayLiteral("hex_numb_token");
//            case lex_float: return QByteArrayLiteral("float_numb_token");
//            case lex_double: return QByteArrayLiteral("double_numb_token");

//            case lex_symbol: return QByteArrayLiteral("symbol_token");
//            case lex_const: return QByteArrayLiteral("const_token");
//            case lex_var_scoped: return QByteArrayLiteral("var_scoped_token");
//            case lex_var_local: return QByteArrayLiteral("var_local_token");
//            case lex_var_instance: return QByteArrayLiteral("var_instance_token");
//            case lex_var_object: return QByteArrayLiteral("var_object_token");
//            case lex_var_global: return QByteArrayLiteral("var_global_token");

//            case lex_interpolation: return QByteArrayLiteral("interpolation_token");

//            case lex_dot: return QByteArrayLiteral("dot_token");
//            case lex_dot_dot: return QByteArrayLiteral("dot_dot_token");
//            case lex_dot_dot_dot: return QByteArrayLiteral("dot_dot_dot_token");
//            case lex_rocket: return QByteArrayLiteral("rocket_token");
//            case lex_colon: return QByteArrayLiteral("color_token");
//            case lex_semicolon: return QByteArrayLiteral("semicolon_token");
//            case lex_resolution: return QByteArrayLiteral("resolution_token");
//            case lex_comma: return QByteArrayLiteral("comma_token");
//            case lex_open_curly_bracket: return QByteArrayLiteral("open_curly_bracket_token");
//            case lex_close_curly_bracket: return QByteArrayLiteral("close_curly_bracket_token");
//            case lex_open_square_bracket: return QByteArrayLiteral("open_square_bracket_token");
//            case lex_close_square_bracket: return QByteArrayLiteral("close_square_brucket_token");


//            case lex_operator_assigment: return QByteArrayLiteral("operator_assigment_token");
//            case lex_operator_comparison: return QByteArrayLiteral("operator_comparison_token");
//            case lex_operator_equality: return QByteArrayLiteral("operator_equality_token");
//            case lex_operator_not_equal: return QByteArrayLiteral("operator_not_equal_token");

//            case lex_operator_less: return QByteArrayLiteral("operator_less_token");
//            case lex_operator_less_eql: return QByteArrayLiteral("operator_less_eql_token");
//            case lex_operator_great: return QByteArrayLiteral("operator_great_token");
//            case lex_operator_great_eql: return QByteArrayLiteral("operator_great_eql_token");

//            case lex_operator_sort: return QByteArrayLiteral("operator_sort_token");

//            case lex_operator_add: return QByteArrayLiteral("operator_add_token");
//            case lex_operator_add_assigment: return QByteArrayLiteral("operator_add_assigment_token");
//            case lex_operator_increase: return QByteArrayLiteral("operator_increase_token");
//            case lex_operator_minus: return QByteArrayLiteral("operator_minus_token");
//            case lex_operator_minus_assigment: return QByteArrayLiteral("operator_minus_assigment_token");
//            case lex_operator_decrease: return QByteArrayLiteral("operator_decrease_token");
//            case lex_operator_multiplication: return QByteArrayLiteral("operator_multiply_token");
//            case lex_operator_multiplication_assigment: return QByteArrayLiteral("operator_multiply_assigment_token");
//            case lex_operator_division: return QByteArrayLiteral("operator_divide_token");
//            case lex_operator_division_assigment: return QByteArrayLiteral("operator_divide_assigment_token");
//            case lex_operator_exponentiation: return QByteArrayLiteral("operator_exponent_token");
//            case lex_operator_exponentiation_assigment: return QByteArrayLiteral("operator_exponent_assigment_token");
//            case lex_operator_modulus: return QByteArrayLiteral("operator_modulus_token");
//            case lex_operator_modulus_assigment: return QByteArrayLiteral("operator_modulus_assigment_token");

//            case lex_operator_safe_navigation: return QByteArrayLiteral("operator_safe_navigation_token");

//            case lex_operator_bit_and: return QByteArrayLiteral("operator_bit_and_token");
//            case lex_operator_bit_or: return QByteArrayLiteral("operator_bit_or_token");
//            case lex_operator_bit_exclusive_or: return QByteArrayLiteral("operator_bit_exclusive_or_token");
//            case lex_operator_bit_not: return QByteArrayLiteral("operator_bit_not_token");
//            case lex_operator_bit_left_shift: return QByteArrayLiteral("operator_bit_left_shift_token");
//            case lex_operator_bit_right_shift: return QByteArrayLiteral("operator_bit_right_shift_token");

//            case lex_operator_and: return QByteArrayLiteral("operator_and_token");
//            case lex_operator_or: return QByteArrayLiteral("operator_or_token");
//            case lex_operator_or_assigment: return QByteArrayLiteral("operator_or_assigment_token");
//            case lex_operator_not: return QByteArrayLiteral("operator_not_token");


//            case lex_method_def: return QByteArrayLiteral("method_def_token");
//            case lex_method_def_scope: return QByteArrayLiteral("method_def_scope_token");
//            case lex_method_def_scoped: return QByteArrayLiteral("method_def_scoped_token");
//            case lex_method_def_name: return QByteArrayLiteral("method_def_name_token");
//            case lex_method_def_scoped_name: return QByteArrayLiteral("method_def_scoped_name_token");
//            case lex_method_def_block: return QByteArrayLiteral("method_def_block_token");
//            case lex_method_def_block_end: return QByteArrayLiteral("method_def_block_end_token");
//            case lex_method_def_vars_start: return QByteArrayLiteral("method_def_vars_start_token");
//            case lex_method_def_var_attr: return QByteArrayLiteral("method_def_var_attr_token");
//            case lex_method_def_var_type: return QByteArrayLiteral("method_def_var_type_token");
//            case lex_method_def_var_access_type: return QByteArrayLiteral("method_def_var_access_type_token");
//            case lex_method_def_var_name: return QByteArrayLiteral("method_def_var_name_token");
//            case lex_method_def_vars_splitter: return QByteArrayLiteral("method_def_vars_splitter_token");
//            case lex_method_def_vars_end: return QByteArrayLiteral("method_def_vars_end_token");


//            case lex_method_call_name: return QByteArrayLiteral("method_call_name_token");
//            case lex_method_call_vars_start: return QByteArrayLiteral("method_call_vars_start_token");
//            case lex_method_call_var_entry: return QByteArrayLiteral("method_call_var_entry_token");
//            case lex_method_call_vars_splitter: return QByteArrayLiteral("method_call_vars_splitter_token");
//            case lex_method_call_vars_end: return QByteArrayLiteral("method_call_vars_end_token");
//            case lex_method_call_block: return QByteArrayLiteral("method_call_block_token");
//            case lex_method_call_block_vars_start: return QByteArrayLiteral("method_call_block_vars_start_token");
//            case lex_method_call_block_var_name: return QByteArrayLiteral("method_call_block_var_name_token");
//            case lex_method_call_block_vars_splitter: return QByteArrayLiteral("method_call_block_vars_splitter_token");
//            case lex_method_call_block_vars_end: return QByteArrayLiteral("method_call_block_vars_end_token");
//            case lex_method_call_block_end: return QByteArrayLiteral("method_call_block_end_token");


//            case lex_class_def: return QByteArrayLiteral("class_def_token");
//            case lex_class_def_name: return QByteArrayLiteral("class_def_name_token");
//            case lex_class_def_extension: return QByteArrayLiteral("class_def_extension_token");
//            case lex_class_def_extender: return QByteArrayLiteral("class_def_extender_token");
//            case lex_class_def_inheritance: return QByteArrayLiteral("class_def_inheritance_token");
//            case lex_class_def_ancestor: return QByteArrayLiteral("class_def_ancestor_token");
//            case lex_class_def_block: return QByteArrayLiteral("class_def_block_token");
//            case lex_class_def_block_end: return QByteArrayLiteral("class_def_block_end_token");

//            case lex_class_def_short: return QByteArrayLiteral("class_def_short_token");
//            case lex_class_def_short_accessing: return QByteArrayLiteral("class_def_short_accessing_token");
//            case lex_class_def_short_method: return QByteArrayLiteral("class_def_short_method_token");
//            case lex_class_def_short_block: return QByteArrayLiteral("class_def_short_block_token");
//            case lex_class_def_short_block_end: return QByteArrayLiteral("class_def_short_block_end_token");


//            case lex_module_def: return QByteArrayLiteral("module_def_token");
//            case lex_module_def_name: return QByteArrayLiteral("module_def_name_token");
//            case lex_module_def_resolution: return QByteArrayLiteral("module_def_resolution_token");
//            case lex_module_def_block: return QByteArrayLiteral("module_def_block_token");
//            case lex_module_def_block_end: return QByteArrayLiteral("module_def_block_end_token");


//            case lex_lambda_def: return QByteArrayLiteral("lambda_def_token");
//            case lex_lambda_def_vars_start: return QByteArrayLiteral("lambda_def_vars_start_token");
//            case lex_lambda_def_var_attr: return QByteArrayLiteral("lambda_def_var_attr_token");
//            case lex_lambda_def_var_type: return QByteArrayLiteral("lambda_def_var_type_token");
//            case lex_lambda_def_var_access_type: return QByteArrayLiteral("lambda_def_var_access_type_token");
//            case lex_lambda_def_var_name: return QByteArrayLiteral("lambda_def_var_name_token");
//            case lex_lambda_def_vars_splitter: return QByteArrayLiteral("lambda_def_vars_splitter_token");
//            case lex_lambda_def_vars_end: return QByteArrayLiteral("lambda_def_vars_end_token");
//            case lex_lambda_def_block: return QByteArrayLiteral("lambda_def_block_token");
//            case lex_lambda_def_block_end: return QByteArrayLiteral("lambda_def_block_end_token");


//            case lex_proc_def: return QByteArrayLiteral("proc_def_token");
//            case lex_proc_def_block: return QByteArrayLiteral("proc_def_block_token");
//            case lex_proc_def_block_end: return QByteArrayLiteral("proc_def_block_end_token");
//            case lex_proc_def_vars_start: return QByteArrayLiteral("proc_def_vars_start_token");
//            case lex_proc_def_var_attr: return QByteArrayLiteral("proc_def_var_attr_token");
//            case lex_proc_def_var_type: return QByteArrayLiteral("proc_def_var_type_token");
//            case lex_proc_def_var_access_type: return QByteArrayLiteral("proc_def_var_access_type_token");
//            case lex_proc_def_var_name: return QByteArrayLiteral("proc_def_var_name_token");
//            case lex_proc_def_vars_splitter: return QByteArrayLiteral("proc_def_vars_splitter_token");
//            case lex_proc_def_vars_end: return QByteArrayLiteral("proc_def_vars_end_token");

//            case lex_inline_commentary: return QByteArrayLiteral("inline_commentary_token");

//            case lex_commentary_start: return QByteArrayLiteral("commentary_start_token");
//            case lex_commentary_continue: return QByteArrayLiteral("commentary_continue_token");
//            case lex_commentary_end: return QByteArrayLiteral("commentary_end_token");

//            case lex_command_start: return QByteArrayLiteral("command_start_token");
//            case lex_command_interception: return QByteArrayLiteral("command_interception_token");
//            case lex_command_intercepted: return QByteArrayLiteral("command_intercepted_token");
//            case lex_command_continue: return QByteArrayLiteral("command_continue_token");
//            case lex_command_end: return QByteArrayLiteral("command_end_token");

//            case lex_string_start: return QByteArrayLiteral("string_start_token");
//            case lex_string_continue: return QByteArrayLiteral("string_continue_token");
//            case lex_string_end: return QByteArrayLiteral("string_end_token");

//            case lex_estring_start: return QByteArrayLiteral("estring_start_token");
//            case lex_estring_interception: return QByteArrayLiteral("estring_interception_token");
//            case lex_estring_intercepted: return QByteArrayLiteral("estring_intercepted_token");
//            case lex_estring_continue: return QByteArrayLiteral("estring_continue_token");
//            case lex_estring_end: return QByteArrayLiteral("estring_end_token");

//            case lex_percent_presentation_start: return QByteArrayLiteral("percentage_presentation_start_token");
//            case lex_percent_presentation_continue: return QByteArrayLiteral("percentage_presentation_continue_token");
//            case lex_percent_presentation_end: return QByteArrayLiteral("percentage_presentation_end_token");

//            case lex_epercent_presentation_start: return QByteArrayLiteral("epercentage_presentation_start_token");
//            case lex_epercent_presentation_interception: return QByteArrayLiteral("epercentage_presentation_interception_token");
//            case lex_epercent_presentation_intercepted: return QByteArrayLiteral("epercentage_presentation_intercepted_token");
//            case lex_epercent_presentation_continue: return QByteArrayLiteral("epercentage_presentation_continue_token");
//            case lex_epercent_presentation_end: return QByteArrayLiteral("epercentage_presentation_end_token");

//            case lex_heredoc_mark: return QByteArrayLiteral("heredoc_mark_token");
//            case lex_heredoc_start: return QByteArrayLiteral("heredoc_start_token");
//            case lex_heredoc_continue: return QByteArrayLiteral("heredoc_continue_token");
//            case lex_heredoc_end: return QByteArrayLiteral("heredoc_end_token");

//            case lex_heredoc_intended_mark: return QByteArrayLiteral("heredoc_intended_mark_token");
//            case lex_heredoc_intended_start: return QByteArrayLiteral("heredoc_intended_start_token");
//            case lex_heredoc_intended_continue: return QByteArrayLiteral("heredoc_intended_continue_token");

//            case lex_eheredoc_mark: return QByteArrayLiteral("eheredoc_mark_token");
//            case lex_eheredoc_start: return QByteArrayLiteral("eheredoc_start_token");
//            case lex_eheredoc_interception: return QByteArrayLiteral("eheredoc_interception_token");
//            case lex_eheredoc_intercepted: return QByteArrayLiteral("eheredoc_intercepted_token");
//            case lex_eheredoc_continue: return QByteArrayLiteral("eheredoc_continue_token");

//            case lex_eheredoc_intended_mark: return QByteArrayLiteral("eheredoc_intended_mark_token");
//            case lex_eheredoc_intended_start: return QByteArrayLiteral("eheredoc_intended_start_token");
//            case lex_eheredoc_intended_interception: return QByteArrayLiteral("eheredoc_intended_interception_token");
//            case lex_eheredoc_intended_intercepted: return QByteArrayLiteral("eheredoc_intended_intercepted_token");
//            case lex_eheredoc_intended_continue: return QByteArrayLiteral("eheredoc_intended_continue_token");

//            case lex_cheredoc_mark: return QByteArrayLiteral("cheredoc_mark_token");
//            case lex_cheredoc_start: return QByteArrayLiteral("cheredoc_start_token");
//            case lex_cheredoc_interception: return QByteArrayLiteral("cheredoc_interception_token");
//            case lex_cheredoc_intercepted: return QByteArrayLiteral("cheredoc_intercepted_token");
//            case lex_cheredoc_continue: return QByteArrayLiteral("cheredoc_continue_token");

//            case lex_cheredoc_intended_mark: return QByteArrayLiteral("cheredoc_intended_mark_token");
//            case lex_cheredoc_intended_start: return QByteArrayLiteral("cheredoc_intended_start_token");
//            case lex_cheredoc_intended_interception: return QByteArrayLiteral("cheredoc_intended_interception_token");
//            case lex_cheredoc_intended_intercepted: return QByteArrayLiteral("cheredoc_intended_intercepted_token");
//            case lex_cheredoc_intended_continue: return QByteArrayLiteral("cheredoc_intended_continue_token");
//        //////////////////////////////////////


//            case lex_regexp_start: return QByteArrayLiteral("regexp_start_token");
//            case lex_regexp_interception: return QByteArrayLiteral("regexp_interception_token");
//            case lex_regexp_intercepted: return QByteArrayLiteral("regexp_intercepted_token");
//            case lex_regexp_continue: return QByteArrayLiteral("regexp_continue_token");
//            case lex_regexp_end: return QByteArrayLiteral("regexp_end_token");


//            case lex_require: return QByteArrayLiteral("require_token");
//            case lex_require_path: return QByteArrayLiteral("require_path_token");

//            case lex_include: return QByteArrayLiteral("include_token");
//            case lex_include_obj: return QByteArrayLiteral("include_obj_token");
//            case lex_include_resolution: return QByteArrayLiteral("include_resolution_token");
//            case lex_include_name: return QByteArrayLiteral("include_name_token");

//            case lex_extend: return QByteArrayLiteral("extend_token");
//            case lex_extend_obj: return QByteArrayLiteral("extend_obj_token");
//            case lex_extend_resolution: return QByteArrayLiteral("extend_resolution_token");
//            case lex_extend_name: return QByteArrayLiteral("extend_name_token");

//            case lex_undef: return QByteArrayLiteral("undef_token");
//            case lex_undef_name: return QByteArrayLiteral("undef_name_token");

//            case lex_visibility_scope: return QByteArrayLiteral("visibility_scope_token");
//            case lex_visibility_scope_arg: return QByteArrayLiteral("visibility_scope_arg_token");
//            case lex_visibility_scope_arg_splitter: return QByteArrayLiteral("visibility_scope_arg_splitter_token");

//            case lex_alias: return QByteArrayLiteral("alias_token");
//            case lex_alias_base_name: return QByteArrayLiteral("alias_base_name_token");
//            case lex_alias_alt_name: return QByteArrayLiteral("alias_alt_name_token");


//            case lex_wrap_start: return QByteArrayLiteral("wrap_start_token");
//            case lex_wrap_end: return QByteArrayLiteral("wrap_end_token");


//            case lex_hash_start: return QByteArrayLiteral("hash_start_token");
//            case lex_hash_item: return QByteArrayLiteral("hash_item_token");
//            case lex_hash_key: return QByteArrayLiteral("hash_key_token");
//            case lex_hash_key_with_relation: return QByteArrayLiteral("hash_key_with_relation_token");
//            case lex_hash_key_relation: return QByteArrayLiteral("hash_key_relation_token");
//            case lex_hash_val: return QByteArrayLiteral("hash_val_token");
//            case lex_hash_splitter: return QByteArrayLiteral("hash_splitter_token");
//            case lex_hash_end: return QByteArrayLiteral("hash_end_token");


//            case lex_array_start: return QByteArrayLiteral("array_start_token");
//            case lex_array_item: return QByteArrayLiteral("array_item_token");
//            case lex_array_splitter: return QByteArrayLiteral("array_splitter_token");
//            case lex_array_end: return QByteArrayLiteral("array_end_token");


//            case lex_ternary_main_start: return QByteArrayLiteral("ternary_main_start_token");
//            case lex_ternary_main_val: return QByteArrayLiteral("ternary_main_val_token");
//            case lex_ternary_alt_start: return QByteArrayLiteral("ternary_alt_start_token");
//            case lex_ternary_alt_val: return QByteArrayLiteral("ternary_alt_val_token");

//            case lex_then: return QByteArrayLiteral("then_token");
//            case lex_in: return QByteArrayLiteral("in_token");

//            case lex_unless: return QByteArrayLiteral("unless_token");
//            case lex_unless_rule: return QByteArrayLiteral("unless_rule_token");
//            case lex_unless_then: return QByteArrayLiteral("unless_then_token");
//            case lex_unless_block: return QByteArrayLiteral("unless_block_token");
//            case lex_unless_block_end: return QByteArrayLiteral("unless_block_end_token");

//            case lex_if: return QByteArrayLiteral("if_token");
//            case lex_if_rule: return QByteArrayLiteral("if_rule_token");
//            case lex_if_then: return QByteArrayLiteral("if_then_token");
//            case lex_if_block: return QByteArrayLiteral("if_block_token");
//            case lex_if_block_end: return QByteArrayLiteral("if_block_end_token");

//            case lex_elsif: return QByteArrayLiteral("elsif_token");
//            case lex_elsif_rule: return QByteArrayLiteral("elsif_rule_token");
//            case lex_elsif_then: return QByteArrayLiteral("elsif_then_token");
//            case lex_elsif_block: return QByteArrayLiteral("elsif_block_token");
//            case lex_elsif_block_end: return QByteArrayLiteral("elsif_block_end_token");

//            case lex_else: return QByteArrayLiteral("else_token");
//            case lex_else_block: return QByteArrayLiteral("else_block_token");
//            case lex_else_block_end: return QByteArrayLiteral("else_block_end_token");


//            case lex_switch: return QByteArrayLiteral("switch_token");
//            case lex_switch_target: return QByteArrayLiteral("switch_target_token");
//            case lex_switch_block: return QByteArrayLiteral("switch_block_token");
//            case lex_switch_block_end: return QByteArrayLiteral("switch_block_end_token");

//            case lex_case: return QByteArrayLiteral("case_token");
//            case lex_case_target: return QByteArrayLiteral("case_target_token");
//            case lex_case_target_block: return QByteArrayLiteral("case_target_block_token");
//            case lex_case_target_block_end: return QByteArrayLiteral("case_target_block_end_token");

//            case lex_when: return QByteArrayLiteral("when_token");
//            case lex_when_target: return QByteArrayLiteral("when_target_token");
//            case lex_when_target_splitter: return QByteArrayLiteral("when_target_splitter_token");
//            case lex_when_then: return QByteArrayLiteral("when_then_token");
//            case lex_when_else: return QByteArrayLiteral("when_else_token");
//            case lex_when_block: return QByteArrayLiteral("when_block_token");
//            case lex_when_block_end: return QByteArrayLiteral("when_block_token");


//            case lex_while: return QByteArrayLiteral("while_token");
//            case lex_while_rule: return QByteArrayLiteral("while_rule_token");
//            case lex_while_block: return QByteArrayLiteral("while_block_token");
//            case lex_while_block_end: return QByteArrayLiteral("while_block_end_token");

//            case lex_until: return QByteArrayLiteral("until_token");
//            case lex_until_rule: return QByteArrayLiteral("until_rule_token");
//            case lex_until_block: return QByteArrayLiteral("until_block_token");
//            case lex_until_block_end: return QByteArrayLiteral("until_block_end_token");

//            case lex_for: return QByteArrayLiteral("for_token");
//            case lex_for_vars_start: return QByteArrayLiteral("for_vars_start_token");
//            case lex_for_var: return QByteArrayLiteral("for_var_token");
//            case lex_for_vars_splitter: return QByteArrayLiteral("for_vars_splitter_token");
//            case lex_for_vars_end: return QByteArrayLiteral("for_vars_token");

//            case lex_for_in: return QByteArrayLiteral("for_in_token");
//            case lex_for_in_target: return QByteArrayLiteral("for_in_target_token");

//            case lex_loop_break: return QByteArrayLiteral("loop_break_token");
//            case lex_loop_redo: return QByteArrayLiteral("loop_redo_token");
//            case lex_loop_next: return QByteArrayLiteral("loop_next_token");

//            case lex_do: return QByteArrayLiteral("do_token");
//            case lex_do_block_start: return QByteArrayLiteral("do_block_start_token");
//            case lex_do_block_vars_start: return QByteArrayLiteral("do_block_vars_start_token");
//            case lex_do_block_var_access_type: return QByteArrayLiteral("do_block_var_access_type_token");
//            case lex_do_block_var_name: return QByteArrayLiteral("do_block_var_name_token");
//            case lex_do_block_vars_splitter: return QByteArrayLiteral("do_block_vars_splitter_token");
//            case lex_do_block_vars_end: return QByteArrayLiteral("do_block_vars_end_token");

//            case lex_inline_block_start: return QByteArrayLiteral("inline_block_start_token");

//            case lex_inline_do_block_start: return QByteArrayLiteral("inline_do_block_start_token");
//            case lex_inline_do_block_vars_start: return QByteArrayLiteral("inline_do_block_vars_start_token");
//            case lex_inline_do_block_var_access_type: return QByteArrayLiteral("inline_do_block_var_access_type_token");
//            case lex_inline_do_block_var_name: return QByteArrayLiteral("inline_do_block_var_name_token");
//            case lex_inline_do_block_vars_splitter: return QByteArrayLiteral("inline_do_block_vars_splitter_token");
//            case lex_inline_do_block_vars_end: return QByteArrayLiteral("inline_do_block_vars_end_token");


//            case lex_begin: return QByteArrayLiteral("begin_token");
//            case lex_end: return QByteArrayLiteral("end_token");

//            case lex_block_start: return QByteArrayLiteral("block_start_token");
//            case lex_block_rescue: return QByteArrayLiteral("block_rescue_token");
//            case lex_block_ensure: return QByteArrayLiteral("block_ensure_token");
//            case lex_block_retry: return QByteArrayLiteral("block_retry_token");
//            case lex_block_end: return QByteArrayLiteral("block_end_token");


//            case lex_return: return QByteArrayLiteral("return_token");


//            case lex_global_pre_hook: return QByteArrayLiteral("global_pre_hook_token");
//            case lex_global_post_hook: return QByteArrayLiteral("global_post_hook_token");
//            case lex_end_of_code: return QByteArrayLiteral("end_of_code_token");


//            case lex_undefined: return QByteArrayLiteral("undefined_token");
//            case lex_end_line: return QByteArrayLiteral("end_of_code_token");
//            case lex_end_doc: return QByteArrayLiteral("end_doc_token");
//            case lex_tab: return QByteArrayLiteral("tab_token");
//            case lex_blank: return QByteArrayLiteral("blank_token");
//            case lex_blanks: return QByteArrayLiteral("blanks_token");
//            case lex_ignore: return QByteArrayLiteral("ignore_token");

//            default: return QByteArrayLiteral("Unknown: ") + QByteArray::number(lexem);
//        }
//    }
//};

#endif // STATE_LEXEMS_H



//lex_open = 1 << 30,
//lex_close = 1 << 29,
//lex_continue = 1 << 28,
//lex_interception = 1 << 27,
////    lex_block = 1 << 26,

//lex_none = 0,

//lex_string = 1,
//lex_string_start = lex_string | lex_open,
//lex_string_continue = lex_string | lex_continue,
//lex_string_end = lex_string | lex_close,


//lex_inline_commentary = 2,

//lex_commentary = 3,
//lex_commentary_start = lex_commentary | lex_open,
//lex_commentary_continue = lex_commentary | lex_continue,
//lex_commentary_end = lex_commentary | lex_close,


//lex_command = 4,
//lex_command_start = lex_command | lex_open,
//lex_command_interception = lex_command | lex_interception,
////    lex_command_intercepted = 5,
//lex_command_continue = lex_command | lex_continue,
//lex_command_end = lex_command | lex_close,

//lex_estring = 6, // "
//lex_estring_start = lex_estring | lex_open,
//lex_estring_interception = lex_estring | lex_interception,
////    lex_estring_intercepted = 7,
//lex_estring_continue = lex_estring | lex_continue,
//lex_estring_end = lex_estring | lex_close,

//lex_percent_presentation = 8, // %n/.../
//lex_percent_presentation_start = lex_percent_presentation | lex_open,
//lex_percent_presentation_continue = lex_percent_presentation | lex_continue,
//lex_percent_presentation_end = lex_percent_presentation | lex_close,

//lex_epercent_presentation = 9, // %N/.../
//lex_epercent_presentation_start = lex_epercent_presentation | lex_open,
//lex_epercent_presentation_interception = lex_epercent_presentation | lex_interception,
////    lex_epercent_presentation_intercepted = 10,
//lex_epercent_presentation_continue = lex_epercent_presentation | lex_continue,
//lex_epercent_presentation_end = lex_epercent_presentation | lex_close,

//// <<HEREDOC ... HEREDOC // <<-HEREDOC ... HEREDOC // <<~HEREDOC .. HEREDOC
//lex_heredoc_mark = 11,
//lex_heredoc = 12,
//lex_heredoc_start = lex_heredoc | lex_open,
//lex_heredoc_continue = lex_heredoc | lex_continue,
//lex_heredoc_end = lex_heredoc | lex_close,

//lex_heredoc_intended_mark = 13,
//lex_heredoc_intended = 14,
//lex_heredoc_intended_start = lex_heredoc_intended | lex_open,
//lex_heredoc_intended_continue = lex_heredoc_intended | lex_continue,
//lex_heredoc_intended_end = lex_heredoc_intended | lex_close,

//lex_eheredoc_mark = 15,
//lex_eheredoc = 16,
//lex_eheredoc_start = lex_eheredoc | lex_open,
//lex_eheredoc_interception = lex_eheredoc | lex_interception,
////    lex_eheredoc_intercepted = 17,
//lex_eheredoc_continue = lex_eheredoc | lex_continue,
//lex_eheredoc_end = lex_eheredoc | lex_close,

//lex_eheredoc_intended_mark = 18,
//lex_eheredoc_intended = 19,
//lex_eheredoc_intended_start = lex_eheredoc_intended | lex_open,
//lex_eheredoc_intended_interception = lex_eheredoc_intended | lex_interception,
////    lex_eheredoc_intended_intercepted = 20,
//lex_eheredoc_intended_continue = lex_eheredoc_intended | lex_continue,
//lex_eheredoc_intended_end = lex_eheredoc_intended | lex_close,

//lex_cheredoc_mark = 21,
//lex_cheredoc = 22,
//lex_cheredoc_start = lex_cheredoc | lex_open,
//lex_cheredoc_interception = lex_cheredoc | lex_interception,
////    lex_cheredoc_intercepted = 23,
//lex_cheredoc_continue = lex_cheredoc | lex_continue,
//lex_cheredoc_end = lex_cheredoc | lex_close,

//lex_cheredoc_intended_mark = 24,
//lex_cheredoc_intended = 25,
//lex_cheredoc_intended_start = lex_cheredoc_intended | lex_open,
//lex_cheredoc_intended_interception = lex_cheredoc_intended | lex_interception,
////    lex_cheredoc_intended_intercepted = 26,
//lex_cheredoc_intended_continue = lex_cheredoc_intended | lex_continue,
//lex_cheredoc_intended_end = lex_cheredoc_intended | lex_close,
////////////////////////////////////////

//lex_regexp = 27, // /\a+/
//lex_regexp_start = lex_regexp | lex_open,
//lex_regexp_interception = lex_regexp | lex_interception,
////    lex_regexp_intercepted = 28,
//lex_regexp_continue = lex_regexp | lex_continue,
//lex_regexp_end = lex_regexp | lex_close,


//lex_curly_bracket = 29,
//lex_open_curly_bracket = lex_curly_bracket | lex_open, // {
//lex_close_curly_bracket = lex_curly_bracket | lex_close, // }

//lex_square_bracket = 30,
//lex_open_square_bracket = lex_square_bracket | lex_open, // [
//lex_close_square_bracket = lex_square_bracket | lex_close, // ]




