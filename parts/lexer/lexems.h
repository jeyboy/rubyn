#ifndef LEXEMS_H
#define LEXEMS_H

#pragma once

enum Lexems {
    lex_unknown = 0,

    lex_local_variable,
    lex_global_variable,
    lex_instance_variable,
    lex_class_variable,

    lex_number,
    lex_quote_string,
    lex_double_quote_string,

    lex_const,
    lex_keyword,
    lex_reg_exp,
    lex_class,
    lex_method,
    lex_arg,
    lex_symbol,

    lex_sigle_comment,
    lex_multy_comment,
};

#endif // LEXEMS_H
