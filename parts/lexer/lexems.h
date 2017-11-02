#ifndef LEXEMS_H
#define LEXEMS_H

#pragma once

//#include <qglobal.h>
#include <qbytearray.h>

#define LEX(val, flag) (Lexem)(val | flag)
#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

 // = (1ULL << 1),

enum Lexem : quint32 {
    // lex_to_stack,
    // lex_from_stack

    lex_error = 0,
    lex_warning,
    lex_notice,

    lex_none,


//    ////////// highlightable
    lex_mark,
    lex_key,
    lex_predefined,
    lex_name,
    lex_def_name,
    lex_commentary,
    lex_string,
    lex_regexp,
    lex_method,



//    lex_key = 1 << 19,
//    lex_block = 1 << 20,
//    lex_def = 1 << 21,
//    lex_commentary = 1 << 22,
//    lex_string = 1 << 23,
//    lex_def_name = 1 << 24,
//    lex_symbol = 1 << 25,
//    lex_regexp = 1 << 26,
//    lex_method = 1 << 27,
//    lex_class = 1 << 28,
//    lex_predefined = 1 << 29,
//    lex_name = 1 << 30,
//    //////////

    lex_super,
    lex_self,

    lex_expression, // abstract
    lex_predefined_expression, // abstract
    lex_word, // names and etc

    lex_unary_operator,
    lex_binary_operator,

    lex_bin,
    lex_oct,
    lex_dec,
    lex_hex,
    lex_float,
    lex_double,

    lex_symbol,
    lex_const,
    lex_var_scoped, // variables in blocks and etc // |a, b|
    lex_var_local,
    lex_var_instance,
    lex_var_object,
    lex_var_global,

    lex_interpolation, // #{

    lex_dot,  // .
    lex_dot_dot,  // ..
    lex_dot_dot_dot,  // ...
    lex_rocket,  // =>
    lex_colon,  // :
    lex_semicolon,  // ;
    lex_resolution,  // ::
    lex_comma,  // ,
    lex_open_curly_bracket, // {
    lex_close_curly_bracket, // }
    lex_open_square_bracket, // [
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

    lex_operator_addition, // +
    lex_operator_addition_assigment, // +=
    lex_operator_increase, // ++
    lex_operator_substraction, // -
    lex_operator_substraction_assigment, // -=
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
    lex_method_def_scope,
    lex_method_def_scoped,
    lex_method_def_name,
    lex_method_def_scoped_name,
    lex_method_def_block,
    lex_method_def_block_end,
    lex_method_def_vars_start,
    lex_method_def_var_attr, // const
    lex_method_def_var_type, // int
    lex_method_def_var_access_type, // * & and etc
    lex_method_def_var_name,
    lex_method_def_vars_splitter,
    lex_method_def_vars_end,


    lex_predefined_method_call_name,

    lex_method_call_name,
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


    lex_class_def,
    lex_class_def_name,
    lex_class_def_extension,
    lex_class_def_extender,
    lex_class_def_inheritance,
    lex_class_def_ancestor,
    lex_class_def_block,
    lex_class_def_block_end,

    lex_class_def_short,
    lex_class_def_short_accessing,
    lex_class_def_short_method,
    lex_class_def_short_block,
    lex_class_def_short_block_end,


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

    lex_commentary_start,
    lex_commentary_continue,
    lex_commentary_end,

    lex_command_start,
    lex_command_continue,
    lex_command_end,

    lex_string_start,
    lex_string_continue,
    lex_string_end,

    lex_estring_start, // "
    lex_estring_continue,
    lex_estring_end,

    lex_percent_presentation_start, // %n/.../
    lex_percent_presentation_continue,
    lex_percent_presentation_end,

    lex_epercent_presentation_start, // %N/.../
    lex_epercent_presentation_continue,
    lex_epercent_presentation_end,

    // <<HEREDOC ... HEREDOC // <<-HEREDOC ... HEREDOC // <<~HEREDOC .. HEREDOC
    lex_heredoc_mark,
    lex_heredoc_start,
    lex_heredoc_continue,
    lex_heredoc_end,

    lex_heredoc_intended_mark,
    lex_heredoc_intended_start,
    lex_heredoc_intended_continue,

    lex_eheredoc_mark,
    lex_eheredoc_start,
    lex_eheredoc_continue,

    lex_eheredoc_intended_mark,
    lex_eheredoc_intended_start,
    lex_eheredoc_intended_continue,

    lex_cheredoc_mark,
    lex_cheredoc_start,
    lex_cheredoc_continue,

    lex_cheredoc_intended_mark,
    lex_cheredoc_intended_start,
    lex_cheredoc_intended_continue,
    //////////////////////////////////////


    lex_regexp_start, // /\a+/
    lex_regexp_continue,
    lex_regexp_end,


    lex_require, // require some source
    lex_require_path,

    lex_include, // include some obj
    lex_include_obj, // part of name
    lex_include_resolution, // ::
    lex_include_name, // full name

    lex_extend, // extend some obj
    lex_extend_obj, // part of name
    lex_extend_resolution, // ::
    lex_exyend_name, // full name

    lex_undef, // undef method
    lex_undef_name,

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
    lex_do_block_end,

    lex_inline_do_block_start,
    lex_inline_do_block_vars_start,
    lex_inline_do_block_var_access_type, // * & and etc
    lex_inline_do_block_var_name,
    lex_inline_do_block_vars_splitter,
    lex_inline_do_block_vars_end,
    lex_inline_do_block_end,


    lex_begin,
    lex_end,

    lex_block_start,
    lex_block_rescue,
    lex_block_ensure,
    lex_block_retry,
    lex_block_end,


    lex_return,


    lex_global_pre_hook,
    lex_global_post_hook,
    lex_end_of_code,


    lex_undefined,
    lex_end_line,
    lex_end_doc,
    lex_tab,
    lex_blank,
    lex_blanks,
    lex_ignore,
    lex_chain_item, // service token

    lex_max
};

//struct Lexems {
//    QByteArray toStr(const Lexem & lexem) {
//        switch(lexem) {


//            default: return QByteArrayLiteral("Undefined");
//        }
//    }
//};

#endif // LEXEMS_H
