#ifndef RUBY_REGEXP_LEXER_H
#define RUBY_REGEXP_LEXER_H

#include "lexer/regexp_lexer.h"

class RubyRegexpLexer : public RegexpLexer {
public:
    RubyRegexpLexer();
    ~RubyRegexpLexer() {}
};

#endif // RUBY_REGEXP_LEXER_H
