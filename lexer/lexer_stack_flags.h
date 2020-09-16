#ifndef LEXER_STACK_FLAGS_H
#define LEXER_STACK_FLAGS_H

#include "misc/defines.h"

enum StackLexemFlag : uint {   
    slf_none = 0,

    slf_stack_word = 1,
    slf_stack_delimiter = 2,

    slf_unstack_word = 4,
    slf_unstack_delimiter = 8,

    slf_replace_word = 16,

    slf_word_related = slf_stack_word | slf_unstack_word | slf_replace_word,
    slf_delimiter_related = slf_stack_delimiter | slf_unstack_delimiter,

    slf_stackable = slf_stack_word | slf_stack_delimiter | slf_replace_word,
    slf_unstackable = slf_unstack_word | slf_unstack_delimiter | slf_replace_word
};

#endif // LEXER_STACK_FLAGS_H
