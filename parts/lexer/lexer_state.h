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
    enum Status {
        ls_none = -1,
        ls_error = 1,
        ls_handled,
        ls_comment,
        ls_string,
        ls_estring,
        ls_command,
        ls_regexp,
        ls_heredoc,
        ls_eheredoc,
        ls_cheredoc
    };

    Highlighter * lighter;

    QByteArray cached;

    Lexem lex_word;
    Lexem lex_delimiter;

    Scope * scope;
    Stack<Lexem> * stack;
//    Stack<Lexem> * chain;
    quint8 next_offset;

    TokenCell * token;

    LEXER_INT_TYPE cached_str_pos;
    LEXER_INT_TYPE cached_length;

    const char * start;
    const char * buffer;
    const char * prev;

    Status status;

    LexerState(Scope * scope, TokenCell * token, Stack<Lexem> * stack_state = 0, Highlighter * lighter = 0) : lighter(lighter),
        lex_word(lex_none), lex_delimiter(lex_none),
        scope(scope), stack(stack_state == 0 ? new Stack<Lexem>(lex_none) : new Stack<Lexem>(stack_state)),
        next_offset(1), token(token), cached_length(0),
        start(0), buffer(0), prev(0), status(ls_handled) { }

    ~LexerState() {
        delete scope;
        delete stack;
    }

    inline void setBuffer(const char * buff) {
        prev = start = buffer = buff;
        cached.clear();
        cached_str_pos = cached_length = 0;
        next_offset = 1;
        status = ls_handled;
    }
//    inline bool isBufferStart() { return buffer == start; }
    inline bool isBufferEof() { return *buffer == 0; }

    inline void cachingPredicate() {
        cached_str_pos = bufferPos();
        cached_length = strLength();
        cached.setRawData(prev, cached_length);
    }
    inline void cachingDelimiter() {
        prev = buffer;
        buffer += next_offset;

        cached_str_pos = bufferPos();
        cached_length = strLength();

        cached.setRawData(prev, cached_length);
    }
    inline void dropCached() {
        next_offset = 1;
        prev = buffer;
    }

    inline LEXER_INT_TYPE bufferPos() { return prev - start; }
    inline LEXER_INT_TYPE strLength() { return buffer - prev; }

    inline Lexem & lastToken() { return token -> lexem; }
    inline void attachToken(const Lexem & lexem) {
        if (token -> next) {
            token = token -> next;
            token -> lexem = lexem;
            token -> start_pos = cached_str_pos;
            token -> length = cached_length;
        }
        else token = TokenList::insert(token, lexem, cached_str_pos, cached_length);
    }
    inline void replaceToken(const Lexem & lexem) {
        token -> lexem = lexem;
        token -> length += cached_length;
    }

    inline void light(const Lexem & lexem) {
//        qDebug() << "!!!!" << bufferPos() << cached_length;

        lighter -> setFormat(
            cached_str_pos,
            cached_length > 0 ? cached_length : 1,
            HighlightFormatFactory::obj().getFormatFor(lexem)
        );
    }
    inline void cacheAndLightWithMessage(const Lexem & lexem, const QByteArray & msg) {
        cachingPredicate();
        lightWithMessage(lexem, msg);
    }
    inline void lightWithMessage(const Lexem & lexem, const QByteArray & /*msg*/) {
        light(lexem);

        if (lexem == lex_error)
            status = ls_error;

        //TODO: attach message
    }
};

#endif // LEXER_STATE_H
