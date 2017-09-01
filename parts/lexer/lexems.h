#ifndef LEXEMS_H
#define LEXEMS_H

#pragma once

#include <qglobal.h>



#define LEX(val, flag) (Lexem)(val | flag)
#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

enum Lexem : quint64 {
    lex_none = 0,

    lex_error = (1ULL << 0),
    lex_warning = (1ULL << 1),
    lex_notice = (1ULL << 2),

    lex_start = (1ULL << 3),
    lex_end = (1ULL << 4),
    lex_continue = (1ULL << 5),

    lex_unary = (1ULL << 6),
    lex_poly = (1ULL << 7),

    lex_operator = (1ULL << 8),
    lex_method = (1ULL << 9),
    lex_module = (1ULL << 10),
    lex_class = (1ULL << 11),
    lex_proc = (1ULL << 12),
    lex_lambda = (1ULL << 13),
    lex_block = (1ULL << 14),
    lex_var = (1ULL << 15),
    lex_commentary = (1ULL << 16),

    lex_key = (1ULL << 17),

    lex_def = (1ULL << 18),
    lex_obj = (1ULL << 19) | lex_var,
    lex_local = (1ULL << 20),
    lex_global = (1ULL << 21),
    lex_parametrized = (1ULL << 22),
    lex_conditional = (1ULL << 23),

    lex_require = (1ULL << 24),

    lex_scope_visibility = (1ULL << 25), // private, protected

    lex_access = (1ULL << 26),  // .
    lex_chain = (1ULL << 27),  // ::
    lex_ternary = (1ULL << 28), // ? :

    lex_comma = (1ULL << 29),  // ,

    lex_wrap = (1ULL << 30), // ()

    lex_datatype = lex_def | lex_obj,

    lex_const = (1ULL << 31),

    lex_bool = (1ULL << 32),
    lex_string = (1ULL << 33),
    lex_number = (1ULL << 34),
    lex_regexp = (1ULL << 35),
    lex_hash = (1ULL << 36),
    lex_array = (1ULL << 37),
    lex_symb = (1ULL << 38),


    // lex_ = (1ULL << 39),
    // lex_ = (1ULL << 40),
    // lex_ = (1ULL << 41),
    // lex_ = (1ULL << 42),
    // lex_ = (1ULL << 43),
    // lex_ = (1ULL << 44),
    // lex_ = (1ULL << 45),
    // lex_ = (1ULL << 46),
    // lex_ = (1ULL << 47),
    // lex_ = (1ULL << 48),
    // lex_ = (1ULL << 49),
    // lex_ = (1ULL << 50),
    // lex_ = (1ULL << 51),
    // lex_ = (1ULL << 52),
    // lex_ = (1ULL << 53),



    lex_bin = (1ULL << 54) | lex_number,
    lex_oct = (1ULL << 55) | lex_number,
    lex_dec = (1ULL << 56) | lex_number,
    lex_hex = (1ULL << 57) | lex_number,

    lex_float = (1ULL << 58) | lex_dec,
//    lex_double = (1ULL << 59) | lex_number,

    lex_undefined =(1ULL << 60),
    lex_end_line = (1ULL << 61),
    lex_ignore =(1ULL << 62),

    ////// MIXES

//    les_def_method = lex_def | lex_method, // def
//    lex_def_module = lex_def | lex_module, // module
//    lex_def_class = lex_def | lex_class, // class

    lex_method_start = lex_method | lex_start,
    lex_module_start = lex_module | lex_start,
    lex_class_start = lex_class | lex_start,

    lex_def_start = lex_method_start | lex_module_start | lex_class_start,
//    lex_def_end = lex_end | lex_method | lex_module | lex_class | lex_block,

//    lex_def_proc = lex_def | lex_proc, // proc
    lex_def_lambda = lex_def | lex_lambda, // lambda, ->
//    lex_class_obj = lex_obj | lex_class, // class name
//    lex_module_obj = lex_obj | lex_module, // module name
//    lex_method_obj = lex_obj | lex_method, // method name

    lex_method_with_params = lex_method | lex_parametrized,

    lex_block_var = lex_var | lex_block, // local
    lex_local_var = lex_var | lex_local, // local
    lex_global_var = lex_var | lex_global, // global
    lex_instance_var = lex_var | lex_obj, // instance
    lex_class_var = lex_var | lex_def, // class or module

    lex_wrap_start = lex_wrap | lex_start, // (
    lex_wrap_end = lex_wrap | lex_end, // )

    lex_args_start = lex_wrap_start, // (
    lex_args_end = lex_wrap_end, // )

    lex_class_required = lex_class | lex_require,
    lex_module_required = lex_module | lex_require,
    lex_class_or_module_required = lex_class_required | lex_module_required,

    lex_block_requred = lex_block | lex_require,
    lex_param_block_requred = lex_block | lex_parametrized | lex_require,

    lex_param_block_start = lex_block | lex_start | lex_parametrized,
    lex_block_start = lex_block | lex_start,
    lex_block_end = lex_block | lex_end,

    lex_block_args_start = lex_block | lex_args_start , // |
    lex_block_args_end = lex_block | lex_args_end, // |

    lex_unary_operator = lex_operator | lex_unary, // ! not
    lex_binary_operator = lex_operator | lex_poly, // + - etc

    lex_inline_commentary_start = lex_commentary | lex_unary | lex_start, // #
    lex_inline_commentary_end = lex_commentary | lex_unary | lex_end,

    lex_multiline_commentary_start = lex_commentary | lex_poly | lex_start, // =begin
    lex_multiline_commentary_end = lex_commentary | lex_poly | lex_end, // =end
    lex_multiline_commentary_continious = lex_multiline_commentary_start | lex_continue, // if row continues at next row

    lex_string_start = lex_string | lex_start,
    lex_string_end = lex_string | lex_end,
    lex_string_continious = lex_string_start | lex_continue, // if row continues at next row
    lex_string_def_required = lex_string | lex_def | lex_require,

    lex_heredoc = lex_string | lex_poly,
    lex_heredoc_start = lex_string_start | lex_poly,
    lex_heredoc_end = lex_string_end | lex_poly,
    lex_heredoc_continious = lex_heredoc_start | lex_require, // if row continues at next row

    lex_regexp_start = lex_regexp | lex_start,
    lex_regexp_end = lex_regexp | lex_end,
    lex_regexp_continious = lex_regexp_start | lex_continue, // if row continues at next row
    lex_regexp_def_required = lex_regexp | lex_def | lex_require,

    lex_array_start = lex_array | lex_start,
    lex_array_end = lex_array | lex_end,

    lex_hash_start = lex_hash | lex_start,
    lex_hash_end = lex_hash | lex_end,

//    lex_resolution = lex_chain | lex_access, // ModuleName::ClassName

    lex_ternary_start = lex_ternary | lex_start,
    lex_ternary_end = lex_ternary | lex_end,


    lex_chain_block = lex_chain | lex_block,

    lex_chain_unary_start = lex_chain_block | lex_unary | lex_start, // this chain support only one additional level // if else
    lex_chain_poly_start = lex_chain_block | lex_poly | lex_start, // this chain support additional levels // if elseif ... else

    lex_conditional_chain_level = lex_chain_block | lex_conditional, // elseif() ...
    lex_chain_level = lex_chain_block, // else ...
//    lex_chain_end = lex_chain | lex_end,


    lex_var_chain_start = lex_start | lex_chain | lex_var,
    lex_var_chain_end = lex_end | lex_chain | lex_var,
//    lex_var_chain_sep = lex_comma | lex_chain | lex_var,

    lex_highlightable = lex_def | lex_module | lex_class | lex_method | lex_const | //lex_var |
        lex_key | lex_string | lex_number | lex_regexp | lex_symb | lex_commentary,
};



//#define LEX(val, flag) (Lexem)(val | flag)
//#define EXCLUDE_BIT(val, flag) (Lexem)(val & ~flag)

////–2,147,483,648 to 2,147,483,647

//enum Lexem : quint16 {
//    lex_none = 0,

//    lex_key = 1 << 7,
//    lex_expression = 1 << 8,
//    lex_number = 1 << 9 | lex_expression,
//    lex_def = 1 << 10,
////    lex_key = 1 << 11,
////    lex_key = 1 << 12,
////    lex_key = 1 << 13,
////    lex_key = 1 << 14,
//    lex_end = 1 << 15,

//    lex_error = 1,
//    lex_warning = 2,
//    lex_notice = 3,

//    lex_datatype = 4,

//    lex_inline_commentary = 5,

//    lex_multiline_commentary = 6,
//    lex_multiline_commentary_continue = 7,
//    lex_multiline_commentary_end = lex_multiline_commentary | lex_end,

//    lex_const = 8 | lex_expression,
////    lex_var = 9,

//    lex_block_var = 10, // local
//    lex_local_var = 11, // local
//    lex_global_var = 12, // global
//    lex_instance_var = 13, // instance
//    lex_class_var = 14, // class or module

////    lex_local_var = 15,
////    lex_global_var = 16,

//    lex_symb = 17,


//    lex_bin = 18 | lex_number,
//    lex_oct = 19 | lex_number,
//    lex_dec = 20 | lex_number,
//    lex_hex = 21 | lex_number,
//    lex_float = 22 | lex_number,
//    lex_double = 23 | lex_number,


//    lex_string = 24 | lex_expression, // '
//    lex_string_continue = 25,
//    lex_string_end = lex_string | lex_end,

//    // string with interpolation
//    lex_estring = 26 | lex_expression, // "
//    lex_estring_continue = 27,
////    lex_estring_return = 28, // after interpolation
//    lex_estring_end = lex_estring | lex_end,

//    lex_heredoc = 29 | lex_expression,
//    lex_heredoc_continue = 30,
////    lex_heredoc_return = 31, // after interpolation
//    lex_heredoc_end = lex_heredoc | lex_end,

//    lex_regexp = 32 | lex_expression,
//    lex_regexp_continue = 33,
////    lex_regexp_return = 34, // after interpolation
//    lex_regexp_end = lex_regexp | lex_end,


//    lex_hash = 35 | lex_expression,
////    lex_hash_continue = 36,
//    lex_hash_end = lex_hash | lex_end,


//    lex_array = 37 | lex_expression,
////    lex_array_continue = 38,
//    lex_array_end = lex_array | lex_end,


//    lex_block = 39 | lex_expression,
////    lex_block_continue = 40,
//    lex_block_end = lex_block | lex_end,

//    lex_block_args = 41,
//    lex_block_args_end = lex_block_args | lex_end,


//    // 42
//    // 43
//    // 44
//    // 45


//    lex_require = 46, // require some source
//    lex_include = 47, // include some obj
//    lex_extend = 48, // extend some obj
//    lex_scope = 49, // public, private etc



//    lex_proc = 50 | lex_expression,
//    lex_lambda = 51 | lex_expression,
//    lex_class = 52 | lex_expression,
//    lex_module = 53 | lex_expression,
//    lex_method = 54 | lex_expression,

//    lex_def_proc = lex_proc | lex_def,
//    lex_def_lambda = lex_lambda | lex_def,
//    lex_def_class = lex_class | lex_def,
//    lex_def_module = lex_module | lex_def,
//    lex_def_method = lex_method | lex_def,


//    lex_access = 55,  // .
//    lex_resolution = 56,  // ::
//    lex_comma = 57,  // ,

//    lex_unary_operator = 58,
//    lex_binary_operator = 59,
//    lex_ternary_cond = 60, // ? :
//    lex_ternary_alt = 61, // ? :

//    // 62
//    // 63

//    lex_wrap = 64, // ()
////    lex_wrap_continue, // ()
//    lex_wrap_end = lex_wrap | lex_end, // ()


//    lex_unary_branch = 65 | lex_expression, // unless
//    lex_unary_branch_condition = 66,

//    // 67
//    // 68

//    lex_poly_branch = 69 | lex_expression, // if
//    lex_poly_branch_condition = 70,
//    lex_poly_branch_level = 71, // elsif

//    lex_branch_last_level = 72, // else

//    lex_undefined = lex_key - 3,
//    lex_end_line = lex_key - 2,
//    lex_ignore = lex_key - 1,


//    lex_highlightable = lex_def | lex_method | lex_const | lex_symb | //lex_var |
//        lex_key | lex_string | lex_estring | lex_number | lex_regexp |
//        lex_inline_commentary | lex_multiline_commentary,
//};

#endif // LEXEMS_H
