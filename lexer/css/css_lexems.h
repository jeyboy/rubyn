#ifndef CSS_LEXEMS_H
#define CSS_LEXEMS_H

#pragma once

#include <qbytearray.h>

#include "misc/defines.h"

enum LexemsCss : LEXEM_TYPE {
    lex_none = 0,

    ////////// highlightable
    yml_lex_error,
    yml_lex_warning,
    yml_lex_notice,

//    lex_mark,
    lex_key,
    lex_predefined,
    lex_name,
//    lex_def_name,
    lex_commentary,
    lex_string,
//    lex_regexp,
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

    lex_undefined,
    lex_end_line,
    lex_end_doc,
    lex_tab,
    lex_blank,
    lex_blanks,
    lex_ignore,
//    lex_chain_item, // service token

    lex_max
};

#endif // CSS_LEXEMS_H
