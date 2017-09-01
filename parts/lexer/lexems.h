#ifndef LEXEMS_H
#define LEXEMS_H

#pragma once

#include <qglobal.h>

#define LEX(val, flag) (Lexem)(val | flag)
#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

//–2,147,483,648 to 2,147,483,647

enum Lexem : quint16 {
    lex_none = 0,

    lex_key = 1 << 7,
    lex_expression = 1 << 8,
    lex_number = 1 << 9 | lex_expression,
    lex_def = 1 << 10,
//    lex_key = 1 << 11,
//    lex_key = 1 << 12,
//    lex_key = 1 << 13,
//    lex_key = 1 << 14,
    lex_end = 1 << 15,

    lex_error = 1,
    lex_warning,
    lex_notice,

    lex_datatype,

    lex_inline_commentary,

    lex_multiline_commentary,
    lex_multiline_commentary_continue,
    lex_multiline_commentary_end = lex_multiline_commentary | lex_end,

    lex_const,
//    lex_var,

    lex_block_var, // local
    lex_local_var, // local
    lex_global_var, // global
    lex_instance_var, // instance
    lex_class_var, // class or module

//    lex_local_var,
//    lex_global_var,

    lex_bool,
    lex_symb,


    lex_bin,
    lex_oct,
    lex_dec,
    lex_hex,
    lex_float,
    lex_double,

    lex_number_bin = lex_number | lex_bin,
    lex_number_oct = lex_number | lex_oct,
    lex_number_dec = lex_number | lex_dec,
    lex_number_hex = lex_number | lex_hex,
    lex_number_float = lex_number | lex_float,
    lex_number_double = lex_number | lex_double,


    lex_string, // '
    lex_string_continue,
    lex_string_end = lex_string | lex_end,

    // string with interpolation
    lex_estring, // "
    lex_estring_continue,
//    lex_estring_return, // after interpolation
    lex_estring_end = lex_estring | lex_end,

    lex_heredoc,
    lex_heredoc_continue,
//    lex_heredoc_return, // after interpolation
    lex_heredoc_end = lex_heredoc | lex_end,

    lex_regexp,
    lex_regexp_continue,
//    lex_regexp_return, // after interpolation
    lex_regexp_end = lex_regexp | lex_end,


    lex_hash,
    lex_hash_continue,
    lex_hash_end = lex_hash | lex_end,


    lex_array,
    lex_array_continue,
    lex_array_end = lex_array | lex_end,


    lex_block,
    lex_block_continue,
    lex_block_end = lex_block | lex_end,

    lex_block_args,
    lex_block_args_end = lex_block_args | lex_end,



    lex_require, // require some source
    lex_include, // include some obj
    lex_extend, // extend some obj
    lex_scope, // public, private etc



    lex_proc,
    lex_lambda,
    lex_class,
    lex_module,
    lex_method,

    lex_def_proc = lex_proc | lex_def,
    lex_def_lambda = lex_lambda | lex_def,
    lex_def_class = lex_class | lex_def,
    lex_def_module = lex_module | lex_def,
    lex_def_method = lex_method | lex_def,


    lex_access,  // .
    lex_resolution,  // ::
    lex_comma,  // ,

    lex_unary_operator,
    lex_binary_operator,
    lex_ternary_cond, // ? :
    lex_ternary_alt, // ? :


    lex_wrap, // ()
    lex_wrap_continue, // ()
    lex_wrap_end = lex_wrap | lex_end, // ()


    lex_unary_branch, // unless
    lex_unary_branch_condition,

    lex_poly_branch, // if
    lex_poly_branch_condition,
    lex_poly_branch_level, // elsif

    lex_branch_last_level, // else

    lex_undefined = lex_key - 3,
    lex_end_line = lex_key - 2,
    lex_ignore = lex_key - 1,


    lex_highlightable = lex_def | lex_method | lex_const | lex_symb | //lex_var |
        lex_key | lex_string | lex_estring | lex_number | lex_regexp |
        lex_inline_commentary | lex_multiline_commentary,
};

#endif // LEXEMS_H
