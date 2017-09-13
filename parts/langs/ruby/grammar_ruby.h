#ifndef GRAMMAR_RUBY_H
#define GRAMMAR_RUBY_H

#include "parts/lexer/grammar.h"

class GrammarRuby : public Grammar {
    GrammarRuby() : Grammar() {
//        for(int i = 0; i < lex_max; i++) {
//            rules[i][lex_blank] = lex_blank;
//            rules[i][lex_tab] = lex_blanks;
//        }

        rules[lex_blank][lex_blank] = lex_blanks;
        rules[lex_blank][lex_tab] = lex_blanks;


        rules[lex_class_def][lex_word] = lex_class_def_name;
        rules[lex_class_def][lex_operator_bit_left_shift] = lex_class_def_extension;
//        rules[lex_class_def][lex_blank] = lex_class_def;
//        rules[lex_class_def][lex_blanks] = lex_class_def;

        rules[lex_class_def_name][lex_operator_less] = lex_class_def_inheritance;
        rules[lex_class_def_name][lex_semicolon] = lex_block_start;
        rules[lex_class_def_name][lex_end_line] = lex_block_start;

        rules[lex_class_def_extension][lex_word] = lex_class_def_extender;
        rules[lex_class_def_extender][lex_semicolon] = lex_block_start;
        rules[lex_class_def_extender][lex_end_line] = lex_block_start;

        rules[lex_class_def_inheritance][lex_expression] = lex_class_def_ancestor;
        rules[lex_class_def_ancestor][lex_semicolon] = lex_block_start;
        rules[lex_class_def_ancestor][lex_end_line] = lex_block_start;


        rules[lex_module_def][lex_word] = lex_module_def_name;
        rules[lex_module_def_resolution][lex_word] = lex_module_def_name;
        rules[lex_module_def_name][lex_resolution] = lex_module_def_resolution;
        rules[lex_module_def_name][lex_semicolon] = lex_block_start;
        rules[lex_module_def_name][lex_end_line] = lex_block_start;


        rules[lex_method_def][lex_self] = lex_method_scope;
        rules[lex_method_def][lex_word] = lex_method_def_name;
        rules[lex_method_scope][lex_dot] = lex_method_def_scoped;
        rules[lex_method_def_scoped][lex_word] = lex_method_def_scoped_name;

        rules[lex_method_def_name][lex_dot] = lex_method_def_scoped;
        rules[lex_method_def_name][lex_wrap_start] = lex_method_def_vars_start;
        rules[lex_method_def_name][lex_operator_multiplication] = lex_method_def_var_access_type;
        rules[lex_method_def_name][lex_word] = lex_method_def_var_name;
        rules[lex_method_def_name][lex_semicolon] = lex_block_start;
        rules[lex_method_def_name][lex_end_line] = lex_block_start;

        rules[lex_method_def_scoped_name][lex_wrap_start] = lex_method_def_vars_start;
        rules[lex_method_def_scoped_name][lex_operator_multiplication] = lex_method_def_var_access_type;
        rules[lex_method_def_scoped_name][lex_word] = lex_method_def_var_name;
        rules[lex_method_def_scoped_name][lex_semicolon] = lex_block_start;
        rules[lex_method_def_scoped_name][lex_end_line] = lex_block_start;

        rules[lex_method_def_vars_start][lex_wrap_end] = lex_method_def_vars_end;
        rules[lex_method_def_vars_start][lex_operator_multiplication] = lex_method_def_var_access_type;
        rules[lex_method_def_vars_start][lex_word] = lex_method_def_var_name;

        rules[lex_method_def_var_access_type][lex_word] = lex_method_def_var_name;

        rules[lex_method_def_var_name][lex_wrap_end] = lex_method_def_vars_end;
        rules[lex_method_def_var_name][lex_comma] = lex_method_def_vars_splitter;

        rules[lex_method_def_vars_splitter][lex_operator_multiplication] = lex_method_def_var_access_type;
        rules[lex_method_def_vars_splitter][lex_word] = lex_method_def_var_name;
    }
public:
};

#endif // GRAMMAR_RUBY_H
