#ifndef LEXEMS_H
#define LEXEMS_H

#pragma once

//#include <qglobal.h>
#include <qbytearray.h>

#define LEX(val, flag) (Lexem)(val | flag)
#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

 // = (1ULL << 1),

enum Lexem : quint32 {
    lex_none = 0,

    //    1 << 9,

    lex_variation = 1 << 11,

    lex_operator = 1 << 12,
    lex_unary_operator = 1 << 13 | lex_operator,
    lex_binary_operator = 1 << 14 | lex_operator,
    lex_chain = 1 << 15,

    lex_start = 1 << 16,
    lex_continue = 1 << 17,
    lex_end = 1 << 18,

    lex_key = 1 << 19,
//    lex_null = 1 << 20, // nil, undefined
    lex_def = 1 << 21,
    lex_commentary = 1 << 22,
    lex_string = 1 << 23,
    lex_def_name = 1 << 24,
    lex_symbol = 1 << 25,
    lex_regexp = 1 << 26,
    lex_method = 1 << 27,
    lex_class = 1 << 28,
    lex_predefined = 1 << 29,
    lex_name = 1 << 30,


    lex_number_bin = 1 | lex_predefined,
    lex_number_oct = 2 | lex_predefined,
    lex_number_dec = 3 | lex_predefined,
    lex_number_hex = 4 | lex_predefined,
    lex_number_float = 5 | lex_predefined,
    lex_number_double = 6 | lex_predefined,

    lex_name_symbol = 7 | lex_symbol,
    lex_name_const = 8 | lex_name,
    lex_name_scoped = 9 | lex_name, // variables in blocks and etc // |a, b|
    lex_name_local = 10, // | lex_name,
    lex_name_instance = 11 | lex_name,
    lex_name_object = 12 | lex_name,
    lex_name_global = 13 | lex_name,

    lex_require = 14 | lex_key, // require some source
    lex_include = 15 | lex_key, // include some obj
    lex_extend = 16 | lex_key, // extend some obj
    lex_undef = 17 | lex_key, // undef method
    lex_visibility = 18 | lex_key, // public, private etc // use one space pad in format // https://fabiokung.com/2010/04/05/ruby-indentation-for-access-modifiers-and-their-sections/
    lex_alias = 19 | lex_key,
    lex_self = 20 | lex_key,
    lex_super = 21 | lex_key,

    lex_class_def = 22 | lex_def | lex_key,
    lex_class_def_name = 23,

    lex_module_def = 24 | lex_def | lex_key,
    lex_module_def_name = 25,

    lex_method_def = 26 | lex_def | lex_key,
    lex_method_def_static_flag = 27,
    lex_method_def_name = 28,

    lex_lambda_def = 29 | lex_key, // -> // Lambda.new // lambda
    lex_lambda_vars_start = 30, // (

    lex_proc_def = 31 | lex_key, // Proc.new // proc

    lex_unless = 32 | lex_chain,
    lex_if = 33 | lex_chain,
    lex_then = 34,
    lex_elsif = 35,
    lex_else = 36,

    lex_inline_commentary = 37 | lex_commentary,

    lex_commentary_start = lex_commentary | lex_start,
    lex_commentary_continue = lex_commentary | lex_continue,
    lex_commentary_end = lex_commentary | lex_end,

    lex_string_start = lex_string | lex_start, // '
    lex_string_continue = lex_string | lex_continue,
    lex_string_end = 38 | lex_string | lex_end,

    lex_estring_start = 39 | lex_string | lex_start, // "
    lex_estring_continue = 40 | lex_string | lex_continue,
    lex_estring_end = 41 | lex_string | lex_end,

    lex_heredoc_start = 42 | lex_string | lex_start, // <<HEREDOC ... HEREDOC // <<-HEREDOC ... HEREDOC // <<~HEREDOC .. HEREDOC
    lex_heredoc_continue = 43 | lex_string | lex_continue,
    lex_heredoc_end = 44 | lex_string | lex_end,

    lex_regexp_start = lex_regexp | lex_start, // /\a+/
    lex_regexp_continue = lex_regexp | lex_continue,
    lex_regexp_end = lex_regexp | lex_end,

    lex_operator_assigment = 45 | lex_binary_operator, // =
    lex_operator_comparison = 46 | lex_binary_operator, // ==
    lex_operator_equality = 47 | lex_binary_operator, // ===
    lex_operator_not_equal = 48 | lex_binary_operator, // !=

    lex_operator_less = 49 | lex_binary_operator, // <
    lex_operator_less_eql = 50 | lex_binary_operator, // <=
    lex_operator_great = 51 | lex_binary_operator, // >
    lex_operator_great_eql = 52 | lex_binary_operator, // >=

    lex_operator_sort = 53 | lex_binary_operator, // <=>

    lex_operator_addition = 54 | lex_binary_operator, // +
    lex_operator_addition_assigment = 55 | lex_binary_operator, // +=
    lex_operator_increase = 56 | lex_unary_operator, // ++
    lex_operator_substraction = 57 | lex_binary_operator, // -
    lex_operator_substraction_assigment = 58 | lex_binary_operator, // -=
    lex_operator_decrease = 59 | lex_unary_operator, // --
    lex_operator_multiplication = 60 | lex_binary_operator, // *
    lex_operator_multiplication_assigment = 61 | lex_binary_operator, // *=
    lex_operator_division = 62 | lex_binary_operator, // /
    lex_operator_division_assigment = 63 | lex_binary_operator, // /=
    lex_operator_exponentiation = 64 | lex_binary_operator, // **
    lex_operator_exponentiation_assigment = 65 | lex_binary_operator, // **=
    lex_operator_modulus = 66 | lex_binary_operator, // %
    lex_operator_modulus_assigment = 67 | lex_binary_operator, // %=

    lex_safe_navigation = 68 | lex_binary_operator, // &. // ruby 2.3+

    lex_operator_bit_and = 69 | lex_binary_operator, // &
    lex_operator_bit_or = 70 | lex_binary_operator, // |
    lex_operator_bit_exclusive_or = 71 | lex_binary_operator, // ^
    lex_operator_bit_not = 72 | lex_unary_operator, // ~
    lex_operator_bit_left_shift = 73 | lex_binary_operator, // <<
    lex_operator_bit_right_shift = 74 | lex_binary_operator, // >>

    lex_operator_and = 75 | lex_binary_operator, // &&
    lex_operator_or = 76 | lex_binary_operator, // ||
    lex_operator_or_assigment = 77 | lex_binary_operator, // ||=
    lex_operator_not = 78 | lex_unary_operator, // !

    lex_global_pre_hook = 79 | lex_key,
    lex_global_post_hook = 80 | lex_key,
    lex_end_of_code = 81 | lex_key,

    lex_block_start = 82 | lex_key, // begin
    lex_block_end = 83 | lex_key, // end

//    lex_switch = 84 | lex_key,
    lex_case = 85 | lex_key,
    lex_when = 86 | lex_key,

    lex_while = 87 | lex_key,
    lex_until = 88 | lex_key,
    lex_for = 89 | lex_key,
    lex_in = 90 | lex_key,

    lex_break = 91 | lex_key,
    lex_retry = 92 | lex_key,
    lex_redo = 93 | lex_key,
    lex_next = 94 | lex_key,
    lex_rescue = 95 | lex_key,
    lex_ensure = 96 | lex_key,

    lex_return = 97 | lex_key,




    lex_expression = 98, // abstract

    lex_dot,  // .
    lex_dot_dot,  // ..
    lex_dot_dot_dot,  // ...
    lex_rocket,  // =>
    lex_colon,  // :
    lex_semicolon,  // ;
    lex_resolution,  // ::
    lex_comma,  // ,
    lex_inheritance, // <
    lex_interpolation, // #{

    lex_inline_block_start, // {
    lex_inline_block_end, // }

    lex_block_vars_start,
//    lex_block_var,
    lex_block_vars_end,

    lex_wrap_start, // (
    lex_wrap_end, // )

    lex_hash_start,
    lex_hash_end,

    lex_array_start,
    lex_array_end,

    lex_ternary_main_branch, // ? :
    lex_ternary_alt_branch, // ? :

    lex_error,
    lex_warning,
    lex_notice,

    lex_undefined,
    lex_end_line,
    lex_ignore,


    lex_highlightable = lex_key | lex_method | lex_name | lex_commentary |
        lex_string | lex_predefined | lex_regexp | lex_symbol | lex_def_name,


    lex_max
};

struct Lexems {
    QByteArray toStr(const Lexem & lexem) {
        switch(lexem) {
            default: return QByteArrayLiteral("Undefined");
        }
    }
};

#endif // LEXEMS_H
