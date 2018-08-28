#ifndef LEXER_REGEXP_RUBY_H
#define LEXER_REGEXP_RUBY_H

#include "lexer/regexp_lexer.h"

namespace Ruby {
    class LexerRegexp : public RegexpLexer {
    public:
        LexerRegexp();
        ~LexerRegexp();
    };
}

#endif // LEXER_REGEXP_RUBY_H
