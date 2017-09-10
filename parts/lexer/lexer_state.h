#ifndef LEXER_STATE_H
#define LEXER_STATE_H

#include "lexems.h"
#include "scopes/scope.h"
#include "parts/editor_parts/highlighter.h"

struct LexerState {
    Highlighter * lighter;

    Lexem lex_state;
    Lexem new_line_state;
//    Lexem var_def_state;

    Scope * scope;
    Stack<Lexem> * stack;
    quint8 next_offset;

    const char * start;
    const char * buffer;
    const char * prev;

    LexerState(Highlighter * lighter = 0) : lighter(lighter), new_line_state(lex_none),
        /*var_def_state(lex_none),*/ scope(new Scope()),
        stack(new Stack<Lexem>(lex_none)), index(0), next_offset(1) { }

    inline void setBuffer(const char * buff) { prev = start = buffer = buff; }

    inline quint32 bufferLenght() const { return ; }

    ~LexerState() {
        delete scope;
        delete stack;
    }
};

#endif // LEXER_STATE_H
