#ifndef LEXER_STATE_H
#define LEXER_STATE_H

#include "lexems.h"
#include "scopes/scope.h"

struct LexerState {
    QByteArray word;
    QByteArray delimiter;

    Lexem lex_state;
    Lexem lex_control_state;

    Lexem new_line_state;
    Lexem var_def_state;
    Scope * scope;
    Stack<Lexem> * stack;
    int index;
    int next_offset;

    LexerState() : new_line_state(lex_none), var_def_state(lex_none), scope(new Scope()),
        stack(new Stack<Lexem>(lex_none)), index(0), next_offset(1) { }

    ~LexerState() {
        delete scope;
        delete stack;
    }
};

#endif // LEXER_STATE_H
