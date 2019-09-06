#ifndef CSS_STATE_LEXEMS_H
#define CSS_STATE_LEXEMS_H

#pragma once

#include "misc/defines.h"

namespace Css {
    enum StateLexem : LEXEM_TYPE {
        DefaultStateLexems,

        lex_word,

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

    //    lex_chain_item, // service token

        lex_max
    };
}

#endif // CSS_STATE_LEXEMS_H
