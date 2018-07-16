#ifndef LEXER_REGEXP_RUBY_H
#define LEXER_REGEXP_RUBY_H

#include "lexer/regexp_lexer.h"

class LexerRegexpRuby : public RegexpLexer {
public:
    LexerRegexpRuby();
    ~LexerRegexpRuby() {}
};

#endif // LEXER_REGEXP_RUBY_H
