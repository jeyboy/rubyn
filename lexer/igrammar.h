#ifndef IGRAMMAR_H
#define IGRAMMAR_H

#include "misc/singleton.h"
#include "lexer/state_lexems.h"
#include "highlighter/identifiers.h"

class IGrammar {
protected:
    StateLexem rules[lex_max][lex_max] = {{lex_error}};
    virtual ~IGrammar();
public:
    StateLexem translate(const StateLexem & state, const StateLexem & input);
    virtual bool stackDropable(const StateLexem & state, const StateLexem & input, const char & ch = '\0');

    virtual Identifier toHighlightable(const StateLexem & /*lexem*/) = 0;
};

#endif // IGRAMMAR_H
