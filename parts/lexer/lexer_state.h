#ifndef LEXER_STATE_H
#define LEXER_STATE_H

#include "lexems.h"
#include "scopes/scope.h"
#include "parts/editor_parts/highlighter.h"
#include "parts/highligters/highlight_format_factory.h"

#define STREAM_N_CHAR(w, offset) (*(w + offset))

#define STREAM_CURR_CHAR(w) (*w)
#define STREAM_PREV_CHAR(w) STREAM_N_CHAR(w, -1)
#define STREAM_NEXT_CHAR(w) STREAM_N_CHAR(w, 1)

#define ECHAR0 STREAM_CURR_CHAR(state -> buffer)
#define ECHAR1 STREAM_NEXT_CHAR(state -> buffer)
#define ECHAR2 STREAM_N_CHAR(state -> buffer, 2)
#define ECHAR3 STREAM_N_CHAR(state -> buffer, 3)
#define ECHAR4 STREAM_N_CHAR(state -> buffer, 4)
#define ECHAR5 STREAM_N_CHAR(state -> buffer, 5)
#define ECHAR_PREV1 STREAM_PREV_CHAR(state -> buffer)

#define SCHAR0 STREAM_CURR_CHAR(state -> prev)
#define SCHAR1 STREAM_NEXT_CHAR(state -> prev)
#define SCHAR2 STREAM_N_CHAR(state -> prev, 2)

#define LEXER_INT_TYPE quint32

struct LexerState {
    Highlighter * lighter;

    QByteArray cached;

    Lexem lex_state;
    Lexem new_line_state;
//    Lexem var_def_state;

    Scope * scope;
    Stack<Lexem> * stack;
    quint8 next_offset;

//    LEXER_INT_TYPE cached_str_pos;
    LEXER_INT_TYPE cached_length;

    const char * start;
    const char * buffer;
    const char * prev;

    LexerState(Highlighter * lighter = 0) : lighter(lighter), new_line_state(lex_none),
        /*var_def_state(lex_none),*/ scope(new Scope()),
        stack(new Stack<Lexem>(lex_none)), next_offset(1), cached_length(0) { }

    inline void setBuffer(const char * buff) { prev = start = buffer = buff; }

    inline void cachingPredicate() {
//        cached_str_pos = bufferPos();
        cached_length = strLength();
        cached.setRawData(prev, cached_length);
    }

    inline void cachingDelimiter() {
        prev = buffer;
        buffer += next_offset;
        cachingPredicate();
    }

    inline void dropCached() {
        next_offset = 1;
        prev = buffer;
    }

    inline LEXER_INT_TYPE bufferPos() { return prev - start; }
    inline LEXER_INT_TYPE strLength() { return buffer - prev; }

//    inline quint32 bufferLenght() const { return ; }

    inline void light(const Lexem & lexem) {
//        qDebug() << "!!!!" << bufferPos() << cached_length;

        lighter -> setFormat(
            bufferPos(),
            cached_length,
            HighlightFormatFactory::obj().getFormatFor(lexem)
        );
    }

    inline void cacheAndLightWithMessage(const Lexem & lexem, const QByteArray & msg) {
        cachingPredicate();
        lightWithMessage(lexem, msg);
    }

    inline void lightWithMessage(const Lexem & lexem, const QByteArray & /*msg*/) {
        light(lexem);
        //TODO: attach message
    }

    ~LexerState() {
        delete scope;
        delete stack;
    }
};

#endif // LEXER_STATE_H
