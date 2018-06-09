#ifndef REGEXP_LEXER_H
#define REGEXP_LEXER_H

#include "ilexer.h"

class RegexpLexer : public ILexer {
public:
    RegexpLexer();

    void handle(const QString & text, Highlighter * lighter);
};

#endif // REGEXP_LEXER_H
