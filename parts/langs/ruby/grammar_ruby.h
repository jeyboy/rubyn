#ifndef GRAMMAR_RUBY_H
#define GRAMMAR_RUBY_H

#include "parts/lexer/grammar.h"

class GrammarRuby : public Grammar {
    GrammarRuby() : Grammar() {
        rules[lex_class_def][lex_expression] = lex_class_def_name;
        rules[lex_class_def_name][lex_end_line] = lex_block_start;
        rules[lex_class_def_name][lex_end_line] = lex_block_start;

        rules[lex_module_def][lex_expression] = lex_module_def_name;
        rules[lex_module_def_name][lex_end_line] = lex_block_start;
    }
public:
};

#endif // GRAMMAR_RUBY_H
