#ifndef LEXER_CONTROL_H
#define LEXER_CONTROL_H

//#include "misc/stack.h"
#include "state_lexems.h"
//#include "scopes/scope.h"
#include "lexer/igrammar.h"
#include "highlighter/highlighter.h"
#include "highlighter/highlight_format_factory.h"

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

struct LexerControl {
    Highlighter * lighter;

    IGrammar * grammar;

    QByteArray cached;

    StateLexem lex_prev_word;
    StateLexem lex_word;
//    StateLexem lex_prev_delimiter;
    StateLexem lex_delimiter;

//    Scope * scope;
    quint8 next_offset;

    TokenCell * stack_token;
    TokenCell * heredoc_token;

    TokenCell * token;
    ParaCell * para;
    ParaCell * control_para;

    Identifier last_uid;

    EDITOR_POS_TYPE cached_str_pos;
    EDITOR_LEN_TYPE cached_length;

    EDITOR_POS_TYPE last_light_pos;
    EDITOR_LEN_TYPE last_light_len;

    const char * start;
    const char * buffer;
    const char * prev;

    BlockUserData * user_data;

    LexerControl(IGrammar * cgrammar, BlockUserData * user_data, TokenCell * stack_token = nullptr, Highlighter * lighter = nullptr) :
        lighter(lighter), grammar(cgrammar),
        lex_prev_word(lex_none), lex_word(lex_none)/*, lex_prev_delimiter(lex_none)*/, lex_delimiter(lex_none),
        next_offset(1), stack_token(stack_token), heredoc_token(nullptr), token(user_data -> lineControlToken()), para(user_data -> lineControlPara()),
        control_para(nullptr), last_uid(hid_none), cached_str_pos(0), cached_length(0), last_light_pos(-2), last_light_len(0),
        start(nullptr), buffer(nullptr), prev(nullptr), user_data(user_data)
    {}

    ~LexerControl() {}

    inline void setBuffer(const char * buff) {
        prev = start = buffer = buff;
        cached.clear();
        cached_str_pos = cached_length = 0;
        next_offset = 1;
    }
    inline void moveBufferToEnd() {
        buffer = start + strlen(start);
    }
    inline bool isBufferStart() { return buffer == start; }
    inline bool isBufferEof() { return *buffer == 0; }

    inline void cachingPredicate(const bool & ignore_para = false) {
        cached_str_pos = bufferPos();
        cached_length = strLength();
        cached.setRawData(prev, cached_length);

        if (lex_word != lex_none) {
            lex_prev_word = lex_word;
        }

        if (cached_length) {
//            lex_prev_delimiter = lex_none;

            if (!ignore_para)
                attachPara(cached);
        }
    }
    inline void cachingDelimiter() {
//        if (lex_word == lex_none)
//            lex_prev_delimiter = lex_delimiter;

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

    inline StateLexem firstNonBlankLexem() {
        TokenCell * it = token;

        while(it) {
            if (it -> lexem < lex_tab)
                return it -> lexem;

            it = it -> prev;
        }

        return lex_none;
    }

    inline EDITOR_POS_TYPE bufferPos() { return prev - start; }
    inline EDITOR_LEN_TYPE strLength() { return static_cast<EDITOR_LEN_TYPE>(buffer - prev); }

    inline StateLexem & sublastToken() { return token -> prev -> lexem; }
    inline StateLexem & lastToken() { return token -> lexem; }
    inline void attachToken(const StateLexem & lexem, const uint & flags = slf_none) {
        if (token -> next) {
            token = token -> next;
            token -> lexem = lexem;
            token -> start_pos = cached_str_pos;
            token -> length = cached_length;
        }
        else token = TokenList::insert(token, lexem, cached_str_pos, cached_length);

        if (flags != slf_none) {
            bool stack_word = flags & slf_stack_word;
            bool stack_delimiter = flags & slf_stack_delimiter;

            if (stack_word || stack_delimiter) {
                token -> stacked_prev = stack_token;
                stack_token = token;

                stack_token -> stacked_state_lexem = lex_none; //stack_word ? lex_prev_word : lex_word;
                lex_prev_word = lex_none;
            } else {
                if (stack_token) {
                    const char blocker = stack_token -> data ? stack_token -> data -> operator[](0) : '\0';

                    if (!grammar -> stackDropable(stack_token -> lexem, lexem, blocker))
                        cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state"));
                    else {
                        lex_prev_word = stack_token -> stacked_state_lexem;

//                        if (lex_prev_word == lex_none)
//                            lex_prev_word = stack_token -> lexem;

                        stack_token = stack_token -> stacked_prev;
                    }
                } else {
                    cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state"));
                }
            }

            lex_word = lex_none;
            lex_delimiter = lex_none;
        }
    }
    inline void replaceToken(const StateLexem & lexem, const uint & flags = slf_none) {
        token -> lexem = lexem;
        token -> length += cached_length;

        if (flags != slf_none && stack_token != token) {
            token -> stacked_prev = stack_token;
            stack_token = token;
        }
    }

    void popStack() {
        if (!stack_token) return;

        stack_token = stack_token -> stacked_prev;
    }

    void relightLast(const Identifier & uid) {
        last_uid = uid;

        lighter -> setFormat(
            last_light_pos, static_cast<int>(last_light_len),
            HighlightFormatFactory::obj().getFormatFor(last_uid)
        );
    }

    inline void light(const Identifier & uid) {
        if (uid == hid_error)
            return;

        bool has_predicate = cached_length > 0;

        EDITOR_POS_TYPE new_pos = cached_str_pos - (has_predicate ? 0 : 1);

        if (last_light_pos != new_pos || uid != last_uid) {
            last_light_pos = new_pos;
            last_light_len = has_predicate ? cached_length : 1;
            last_uid = uid;

            lighter -> setFormat(
                last_light_pos, static_cast<int>(last_light_len),
                HighlightFormatFactory::obj().getFormatFor(last_uid)
            );
        }
    }
    inline void light(const StateLexem & lexem) {
        light(grammar -> toHighlightable(lexem));
    }
    inline void cacheAndLightWithMessage(const StateLexem & lexem, const QByteArray & msg) {
        cachingPredicate();
        lightWithMessage(lexem, msg);
    }
    inline void lightWithMessage(const StateLexem & lexem, const QByteArray & msg) {
        light(lexem);

        if (lexem == lex_error) {
            if (!msg.contains("error_token"))
                qWarning() << msg;
        }

        user_data -> msgs.append(MsgInfo{lexem, last_light_pos, last_light_len, msg});
    }

    inline void attachPara(const QByteArray & pos_para) {
        attachPara(ParaInfo::paraType(pos_para));
    }
    inline void attachPara(const PARA_TYPE & ptype) {
        if (!ptype) return;

        if (para -> next) {
            para = para -> next;
            para -> para_type = ptype;
            para -> pos = cached_str_pos;
        }
        else para = ParaList::insert(para, ptype, cached_str_pos);

        if (ptype & ParaInfo::pt_foldable) {
            if (!control_para)
                control_para = para;
        }
    }
};

#endif // LEXER_CONTROL_H
