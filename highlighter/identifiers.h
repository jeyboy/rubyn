#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#pragma once

#include "misc/defines.h"

enum Identifier : LEXEM_TYPE {
    hid_none = 0,

    hid_error,
    hid_warning,
    hid_notice,

    hid_label,
    hid_name_def,
    hid_name_call,
    hid_var,
    hid_const,
    hid_symbol,
    hid_keyword,
    hid_numeric,
    hid_string,
    hid_regexp,
    hid_commentary,
    hid_scope_visibility

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
};

#endif // IDENTIFIERS_H
