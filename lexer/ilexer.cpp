#include "ilexer.h"

int ILexer::lineState(BlockUserData * udata) {
    LEXEM_TYPE lex = lex_none;

    if (udata -> stack_token)
        lex = udata -> stack_token -> lexem;
    else lex = udata -> token_end -> prev -> lexem;

    return lex |
        ((udata -> level + 1) << state_level_bits_offset);
}

ILexer::ILexer() {

}

ILexer::~ILexer() {

}
