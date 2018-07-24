#ifndef LEXER_CONTROL_H
#define LEXER_CONTROL_H

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

    IGrammar * grammar;

    QByteArray cached;

    StateLexem lex_prev_word;
    StateLexem lex_word;
    StateLexem lex_prev_delimiter;
    StateLexem lex_delimiter;

//    Scope * scope;
    Stack<StateLexem> * stack;
//    Stack<Lexem> * chain;
    quint8 next_offset;

    TokenCell * token;
    ParaCell * para;
    ParaCell * control_para;

    EDITOR_POS_TYPE cached_str_pos;
    EDITOR_LEN_TYPE cached_length;

    EDITOR_POS_TYPE last_light_pos;
    EDITOR_LEN_TYPE last_light_len;

    const char * start;
    const char * buffer;
    const char * prev;

    Status status;
    BlockUserData * user_data;

    LexerControl(IGrammar * cgrammar, BlockUserData * user_data, Stack<StateLexem> * stack_state = nullptr, Highlighter * lighter = nullptr) :
        lighter(lighter), grammar(cgrammar),
        lex_prev_word(lex_none), lex_word(lex_none), lex_prev_delimiter(lex_none), lex_delimiter(lex_none),
        stack(stack_state == nullptr ? new Stack<StateLexem>(lex_none) : new Stack<StateLexem>(stack_state)),
        next_offset(1), token(user_data -> lineControlToken()), para(user_data -> lineControlPara()),
        control_para(nullptr), cached_str_pos(0), cached_length(0), last_light_pos(0), last_light_len(0),
        start(nullptr), buffer(nullptr), prev(nullptr), status(ls_handled), user_data(user_data)
    {}

    ~LexerControl() {}

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

    inline void cachingPredicate(const bool & ignore_para = false) {
        lex_prev_word = lex_word;
        cached_str_pos = bufferPos();
        cached_length = strLength();
        cached.setRawData(prev, cached_length);

        if (!ignore_para && cached_length)
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
    inline EDITOR_LEN_TYPE strLength() { return (EDITOR_LEN_TYPE)(buffer - prev); }

    inline StateLexem & sublastToken() { return token -> prev -> lexem; }
    inline StateLexem & lastToken() { return token -> lexem; }
    inline void attachToken(const StateLexem & lexem) {
        if (token -> next) {
            token = token -> next;
            token -> lexem = lexem;
            token -> start_pos = cached_str_pos;
            token -> length = cached_length;
        }
        else token = TokenList::insert(token, lexem, cached_str_pos, cached_length);
    }
    inline void replaceToken(const StateLexem & lexem) {
        token -> lexem = lexem;
        token -> length += cached_length;
    }

    inline void light(const Identifier & uid) {
        bool has_predicate = cached_length > 0;

        last_light_pos = cached_str_pos - (has_predicate ? 0 : 1);
        last_light_len = has_predicate ? cached_length : 1;

        if (uid >= hid_error) {
            lighter -> setExtraFormatToCurrBlock(
                last_light_pos, (int)last_light_len,
                HighlightFormatFactory::obj().getFormatFor(uid)
            );
        }
        else {
            lighter -> setFormat(
                last_light_pos, (int)last_light_len,
                HighlightFormatFactory::obj().getFormatFor(uid)
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

//        parasha.append(" ").append(ParaInfo::toString(ptype));

        if (para -> next) {
            para = para -> next;
            para -> para_type = ptype;
            para -> pos = cached_str_pos;
        }
        else para = ParaList::insert(para, ptype, cached_str_pos);

        if (ptype & ParaInfo::pt_foldable) {
            if (control_para) {
                qDebug() << "DOUBLE FOLDING: " << control_para -> para_type << ptype;
            }

            control_para = para;
        }
        else if (control_para && ptype & ParaInfo::pt_close) {
            if ((ParaInfo::oppositePara(ptype) & control_para -> para_type) != control_para -> para_type) {
                qDebug() << "WRONG FOLDING CLOSE: " << control_para -> para_type << ptype;
            }
            else control_para = nullptr;
        }
    }
};

#endif // LEXER_CONTROL_H
