#ifndef LEXEMS_H
#define LEXEMS_H

#pragma once

enum Lexem {
    lex_none = 0,

    lex_unary = (1 << 0),
    lex_poly = (1 << 1),

    lex_def = (1 << 2),
    lex_obj = (1 << 3),
    lex_parametrized = (1 << 4),
//     (1 << 5)

    lex_start = (1 << 6),
    lex_end = (1 << 7),

    lex_operator = (1 << 8),
    lex_method = (1 << 9),
    lex_module = (1 << 10),
    lex_class = (1 << 11),
    lex_proc = (1 << 12),
    lex_lambda = (1 << 13),
    lex_block = (1 << 14),
    lex_var = (1 << 15),
    lex_commentary = (1 << 16),


    lex_require = (1 << 17),
    lex_include = (1 << 18),
    lex_extend = (1 << 19),
    lex_inheritance = (1 << 20), // <

    lex_scope_visibility = (1 << 21), // private, protected

    lex_acess = (1 << 22),  // .

    lex_comma = (1 << 23),  // ,

    lex_wrap = (1 << 24), // ()

    lex_arg = (1 << 25),

    ////// MIXES

    les_def_method = lex_def | lex_method, // def
    lex_def_module = lex_def | lex_module, // module
    lex_def_class = lex_def | lex_class, // class
    lex_def_proc = lex_def | lex_proc, // proc
    lex_def_lambda = lex_def | lex_lambda, // lambda, ->

    lex_class_obj = lex_obj | lex_class, // class name
    lex_module_obj = lex_obj | lex_module, // module name
    lex_method_obj = lex_obj | lex_method, // method name


    lex_wrap_start = lex_wrap | lex_start, // (
    lex_wrap_end = lex_wrap | lex_end, // )

    lex_args_start = lex_arg | lex_start, // (
    lex_args_end = lex_arg | lex_end, // )

    lex_block_requred = lex_block | lex_require,
    lex_param_block_requred = lex_block | lex_parametrized | lex_require,

    lex_block_start = lex_block | lex_start,
    lex_block_end = lex_block | lex_end,

    lex_param_block_start = lex_block | lex_start | lex_parametrized,
    lex_param_block_end = lex_block | lex_end | lex_parametrized,

    lex_block_args_start = lex_block | lex_args_start , // |
    lex_block_args_end = lex_block | lex_args_end, // |

    lex_unary_operator = lex_operator | lex_unary, // ! not
    lex_binary_operator = lex_operator | lex_poly, // + - etc

    lex_inline_commentary_start = lex_commentary | lex_unary | lex_start, // #
    lex_inline_commentary_end = lex_commentary | lex_unary | lex_end,

    lex_multiline_commentary_start = lex_commentary | lex_poly | lex_start, // =begin
    lex_multiline_commentary_end = lex_commentary | lex_poly | lex_end, // =end









//    lex_local_variable,
//    lex_global_variable,
//    lex_instance_variable,
//    lex_class_variable,

//    lex_number,
//    lex_quote_string,
//    lex_double_quote_string,

//    lex_const,
//    lex_keyword,
//    lex_reg_exp,
//    lex_class,
//    lex_method,
//    lex_arg,
//    lex_symbol,

//    lex_sigle_comment,
//    lex_multy_comment,
};

#endif // LEXEMS_H
