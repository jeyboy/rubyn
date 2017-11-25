#ifndef LEXER_STATE_H
#define LEXER_STATE_H

#include <qdebug.h>

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
        ls_cheredoc,
        ls_heredoc_intended,
        ls_eheredoc_intended,
        ls_cheredoc_intended,
        ls_percentage_presentation,
        ls_epercentage_presentation
    };

    Highlighter * lighter;

    QByteArray cached;

    Lexem lex_prev_word;
    Lexem lex_word;
    Lexem lex_prev_delimiter;
    Lexem lex_delimiter;

    Scope * scope;
    Stack<Lexem> * stack;
//    Stack<Lexem> * chain;
    quint8 next_offset;

    TokenCell * token;
    ParaCell * para;

    EDITOR_POS_TYPE cached_str_pos;
    EDITOR_LEN_TYPE cached_length;

    EDITOR_POS_TYPE last_light_pos;
    EDITOR_LEN_TYPE last_light_len;

    const char * start;
    const char * buffer;
    const char * prev;

    Status status;
    BlockUserData * user_data;

    PARA_TYPE folding_type;

    LexerState(Scope * scope, BlockUserData * user_data, Stack<Lexem> * stack_state = 0, Highlighter * lighter = 0) : lighter(lighter),
        lex_prev_word(lex_none), lex_word(lex_none), lex_prev_delimiter(lex_none), lex_delimiter(lex_none),
        scope(scope), stack(stack_state == 0 ? new Stack<Lexem>(lex_none) : new Stack<Lexem>(stack_state)),
        next_offset(1), token(user_data -> lineControlToken()), para(user_data -> lineControlPara()), cached_length(0),
        start(0), buffer(0), prev(0), status(ls_handled), user_data(user_data), folding_type(ParaInfo::pt_none)
    {}

    ~LexerState() {
        delete scope;
        delete stack;
    }

    inline void setStatus(const Status & new_status) {
        if (status != ls_error)
            status = new_status;
    }

    inline void setBuffer(const char * buff) {
        prev = start = buffer = buff;
        cached.clear();
        cached_str_pos = cached_length = 0;
        next_offset = 1;
        status = ls_handled;
    }
    inline void moveBufferToEnd() {
        buffer = start + strlen(start);
    }
    inline bool isBufferStart() { return buffer == start; }
    inline bool isBufferEof() { return *buffer == 0; }

    inline void cachingPredicate() {
        lex_prev_word = lex_word;
        cached_str_pos = bufferPos();
        cached_length = strLength();
        cached.setRawData(prev, cached_length);

        if (cached_length)
            attachPara(cached);
    }
    inline void cachingDelimiter() {
        lex_prev_delimiter = lex_delimiter;
        prev = buffer;
        buffer += next_offset;

        cached_str_pos = bufferPos();
        cached_length = strLength();

        cached.setRawData(prev, cached_length);

        if (cached_length)
            attachPara(cached);
    }
    inline void dropCached() {
        next_offset = 1;
        prev = buffer;
    }

    inline EDITOR_POS_TYPE bufferPos() { return prev - start; }
    inline EDITOR_LEN_TYPE strLength() { return buffer - prev; }

    inline Lexem & sublastToken() { return token -> prev -> lexem; }
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
//    inline void updateSubToken(const Lexem & lexem) {
//        TokenCell * prev = token -> prev;
//        prev -> lexem = lexem;
//        light(prev);
//    }

//    inline void light(TokenCell * tcell) {
//        lighter -> setFormat(
//            tcell -> start_pos,
//            tcell -> length,
//            HighlightFormatFactory::obj().getFormatFor(tcell -> lexem)
//        );
//    }

    inline void light(const Lexem & lexem) {
        bool has_predicate = cached_length > 0;

        last_light_pos = cached_str_pos - (has_predicate ? 0 : 1);
        last_light_len = has_predicate ? cached_length : 1;

        if (lexem < lex_none) {
            lighter -> setExtraFormatToCurrBlock(
                last_light_pos, last_light_len,
                HighlightFormatFactory::obj().getFormatFor(lexem)
            );
        }
        else {
            lighter -> setFormat(
                last_light_pos, last_light_len,
                HighlightFormatFactory::obj().getFormatFor(lexem)
            );
        }
    }
    inline void cacheAndLightWithMessage(const Lexem & lexem, const QByteArray & msg) {
        cachingPredicate();
        lightWithMessage(lexem, msg);
    }
    inline void lightWithMessage(const Lexem & lexem, const QByteArray & msg) {
        light(lexem);

        if (lexem == lex_error) {
            status = ls_error;

            if (!msg.contains("error_token"))
                qWarning() << msg;
        }

        user_data -> msgs.append(MsgInfo{lexem, last_light_pos, last_light_len, msg});
    }

    inline void attachPara(const QByteArray & pos_para) {
        const PARA_TYPE & ptype = ParaInfo::paraType(pos_para);
        if (!ptype)
            return;

        if (ptype & ParaInfo::pt_selectable) {
            if (para -> next) {
                para = para -> next;
                para -> para_type = ptype;
                para -> pos = cached_str_pos;
            }
            else para = ParaList::insert(para, ptype, cached_str_pos);
        }

        if (ptype & ParaInfo::pt_foldable) {
            if (folding_type) {
                qDebug() << "DOUBLE FOLDING: " << folding_type << ptype;
            }
        }

        if (ptype & ParaInfo::pt_close) {
            if (ParaInfo::oppositePara(ptype) & folding_type == folding_type) {
                // TODO something
            } else {
                qDebug() << "WRONG FOLDING CLOSE: " << folding_type << ptype;
            }
        }
    }
};

#endif // LEXER_STATE_H
