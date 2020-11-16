#ifndef CSS_STATE_LEXEMS_H
#define CSS_STATE_LEXEMS_H

#pragma once

#include <qbytearray.h>

#include "lexer/state_lexem.h"

namespace Css {
    enum StateLexem : LEXEM_TYPE {

//        1 << 9,// 512
//        1 << 10,// 1024
//        1 << 11// 2048
//        1 << 12// 4096
//        1 << 13// 8192
//        1 << 14// 16384
//        1 << 15// 32768

        DefaultStateLexems,

//        lex_symbol_key              = (lex_reserved + 1) | lex_ruby_division_breaker | lex_ruby_ternary_braker,

//        lex_loop,
    };
}

#endif // CSS_STATE_LEXEMS_H
