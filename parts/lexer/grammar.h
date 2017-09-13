#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "misc/singleton.h"
#include "parts/lexer/lexems.h"

class Grammar : public Singleton<Grammar> {
protected:
    Lexem rules[lex_max][lex_max] = {{lex_error}};
public:
    inline Lexem translate(const Lexem & state, const Lexem & input) {
        return rules[state][input];
    }
};

#endif // GRAMMAR_H
