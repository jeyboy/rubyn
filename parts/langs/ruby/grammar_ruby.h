#ifndef GRAMMAR_RUBY_H
#define GRAMMAR_RUBY_H

#include "parts/lexer/grammar.h"

class GrammarRuby : public Grammar {
    GrammarRuby() : Grammar() {
        rules[lex_none][lex_class_def] = lex_class_def;
        rules[lex_class_def][lex_expression] = lex_class_def_name;
        rules[lex_class_def_name][lex_end_line] = lex_block_start;
    }
public:
};

#endif // GRAMMAR_RUBY_H
