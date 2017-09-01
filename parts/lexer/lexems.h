#ifndef LEXEMS_H
#define LEXEMS_H

#pragma once

#include <qglobal.h>

#define LEX(val, flag) (Lexem)(val | flag)
#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

//–2,147,483,648 to 2,147,483,647

enum Lexem : quint16 {
    lex_none = 0,

    lex_key = 1 << 6,
    lex_expression = 1 << 7,
    lex_number = 1 << 8,
//    lex_key = 1 << 9,
//    lex_key = 1 << 10,
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

    lex_key,
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

    lex_include, // include some source
    lex_scope, // public, private etc

    lex_def_proc,
    lex_def_lambda,
    lex_def_class,
    lex_def_module,
    lex_def_method,


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


    lex_branch_start, // if unless etc
    lex_branch_condition,
    lex_branch_level, // elsif
    lex_branch_last_level, // else
    lex_branch_block = lex_block,


    lex_undefined = 61,
    lex_end_line = 62,
    lex_ignore = 63,

    ////// MIXES

////    les_def_method = lex_def | lex_method, // def
////    lex_def_module = lex_def | lex_module, // module
////    lex_def_class = lex_def | lex_class, // class

//    lex_method_start = lex_method | lex_start,
//    lex_module_start = lex_module | lex_start,
//    lex_class_start = lex_class | lex_start,

//    lex_def_start = lex_method_start | lex_module_start | lex_class_start,
////    lex_def_end = lex_end | lex_method | lex_module | lex_class | lex_block,

////    lex_def_proc = lex_def | lex_proc, // proc
//    lex_def_lambda = lex_def | lex_lambda, // lambda, ->
////    lex_class_obj = lex_obj | lex_class, // class name
////    lex_module_obj = lex_obj | lex_module, // module name
////    lex_method_obj = lex_obj | lex_method, // method name

//    lex_method_with_params = lex_method | lex_parametrized,

//    lex_block_var = lex_var | lex_block, // local
//    lex_local_var = lex_var | lex_local, // local
//    lex_global_var = lex_var | lex_global, // global
//    lex_instance_var = lex_var | lex_obj, // instance
//    lex_class_var = lex_var | lex_def, // class or module

//    lex_chain_block = lex_chain | lex_block,

//    lex_chain_unary_start = lex_chain_block | lex_unary | lex_start, // this chain support only one additional level // if else
//    lex_chain_poly_start = lex_chain_block | lex_poly | lex_start, // this chain support additional levels // if elseif ... else

//    lex_conditional_chain_level = lex_chain_block | lex_conditional, // elseif() ...
//    lex_chain_level = lex_chain_block, // else ...
////    lex_chain_end = lex_chain | lex_end,


//    lex_var_chain_start = lex_start | lex_chain | lex_var,
//    lex_var_chain_end = lex_end | lex_chain | lex_var,
////    lex_var_chain_sep = lex_comma | lex_chain | lex_var,

    lex_highlightable = lex_def | lex_module | lex_class | lex_method | lex_const | //lex_var |
        lex_key | lex_string | lex_estring | lex_number | lex_regexp | lex_symb |
        lex_inline_commentary | lex_multiline_commentary,
};

#endif // LEXEMS_H
