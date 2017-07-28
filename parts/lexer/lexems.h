#ifndef LEXEMS_H
#define LEXEMS_H

#pragma once

enum Lexems {
    lex_none = 0,

    lex_require,
    lex_include,
    lex_extend,
    lex_inheritance,

    lex_scope_visibility, // private, protected

    lex_call,  // .
    lex_comma,  // .

    lex_module,
    lex_module_name,
    lex_class,
    lex_class_name,
    lex_proc,
    lex_lambda,

    lex_lambda_attrs_start,
    lex_lambda_attrs_end,

    lex_block_start,
    lex_block_stop,
    lex_block_attrs_start,
    lex_block_attrs_stop,

    lex_var,
    lex_symb,
    lex_operator,









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
