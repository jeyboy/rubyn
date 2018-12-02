#ifndef COMPLETER_INFO_H
#define COMPLETER_INFO_H

#include "misc/defines.h"

struct CompleterInfo {
    bool at_word_end;
    LEXEM_TYPE lex;
    EDITOR_POS_TYPE cursor_pos;
    EDITOR_POS_TYPE word_start;
    EDITOR_POS_TYPE word_length;
};

#endif // COMPLETER_INFO_H
