#ifndef RUBY_LEXER_REGEXP_H
#define RUBY_LEXER_REGEXP_H

#include "lexer/regexp_lexer.h"

namespace Ruby {
    class LexerRegexp : public RegexpLexer {
    public:
        LexerRegexp();
        ~LexerRegexp();
    };
}

#endif // RUBY_LEXER_REGEXP_H
