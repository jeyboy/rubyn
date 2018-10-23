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
    StateLexem lex_delimiter;

//    Scope * scope;
    quint8 next_offset;

    TokenCell * heredoc_token;
    TokenCell * stack_token;
    TokenCell * token;
    TokenCell * last_non_blank_token;

    ParaCell * para;
    ParaCell * control_para;
    ParaCell * active_para;

    Identifier last_uid;

    EDITOR_POS_TYPE cached_str_pos;
    EDITOR_LEN_TYPE cached_length;

    EDITOR_POS_TYPE last_light_pos;
    EDITOR_LEN_TYPE last_light_len;

    const char * start;
    const char * buffer;
    const char * prev;

    BlockUserData *& user_data;

    LexerControl(IGrammar * cgrammar, BlockUserData *& user_data, TokenCell * stack_token = nullptr, Highlighter * lighter = nullptr) :
        lighter(lighter), grammar(cgrammar),
        lex_prev_word(lex_none), lex_word(lex_none)/*, lex_prev_delimiter(lex_none)*/, lex_delimiter(lex_none), next_offset(1),
        heredoc_token(nullptr), stack_token(stack_token), token(user_data -> lineControlToken()), last_non_blank_token(nullptr),
        para(user_data -> lineControlPara()), control_para(nullptr), active_para(nullptr),
        last_uid(hid_none), cached_str_pos(0), cached_length(0), last_light_pos(-2),
        last_light_len(0), start(nullptr), buffer(nullptr), prev(nullptr), user_data(user_data)
    {}

    ~LexerControl() {}


    inline void setBuffer(const char * buff) {
        cached.clear();
        prev = start = buffer = buff;
        cached_str_pos = cached_length = 0;
        next_offset = 1;
    }
    inline void moveBufferToEnd() { buffer = start + strlen(start); }
    inline bool isBufferStart() { return buffer == start; }
    inline bool isBufferEof() { return *buffer == 0; }
    inline bool bufferIsEmpty() { return *start == '\0'; }

    inline void cachingPredicate() {
        cached_str_pos = bufferPos();
        cached_length = strLength();
        cached.setRawData(prev, cached_length);

        if (lex_word != lex_none) {
            lex_prev_word = lex_word;
        }

        if (cached_length) {
//            lex_prev_delimiter = lex_none;
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
    }
    inline void dropCached() {
        next_offset = 1;
        prev = buffer;
    }

    inline EDITOR_POS_TYPE bufferPos() { return prev - start; }
    inline EDITOR_LEN_TYPE strLength() { return static_cast<EDITOR_LEN_TYPE>(buffer - prev); }

    inline StateLexem & sublastToken() { return token -> prev -> lexem; }
    inline StateLexem & lastToken() { return token -> lexem; }
    inline StateLexem lastNonBlankLexem() {
        if (last_non_blank_token)
            return last_non_blank_token -> lexem;

        TokenCell * it = token;

        while(it) {
            if (it -> lexem < lex_tab)
                return (last_non_blank_token = it) -> lexem;

            it = it -> prev;
        }

        return lex_none;
    }
    inline ParaCell * lastNonClosedPara(const bool & replaceable) {
        ParaCell * it = !replaceable && active_para ? active_para : para -> prev;

        while(it) {
            if (!it -> close && ((replaceable && it -> para_type == pt_none) || (!replaceable && it -> pos != -1))) {
                return it;
            }

            it = it -> prev;
        }

        return nullptr;
    }
    inline bool paraInActiveParaLine(ParaCell * pcell) {
        ParaCell * it = active_para;

        while(it && it -> para_type != pt_max) {
            if (it == pcell)
                return true;

            it = it -> next;
        }

        return false;
    }
    inline bool paraIsNextToActiveParaLine(ParaCell * pcell) {
        ParaCell * it = active_para;

        if (it) {
            while(it -> para_type != pt_none && (it = it -> next));
            return it == pcell;
        }

        return false;
    }


    inline void attachToken(const StateLexem & lexem, const uint & flags = slf_none) {
        if (token -> next) {
            token = token -> next;
            token -> lexem = lexem;
            token -> start_pos = cached_str_pos;
            token -> length = cached_length;

            if (token -> data) {
                delete token -> data;
                token -> data = nullptr;
            }
        }
        else token = TokenList::insert(token, lexem, cached_str_pos, cached_length);

        if (token -> lexem < lex_tab)
            last_non_blank_token = token;

        if (flags != slf_none) {
            bool stackable = flags & slf_stackable;
            bool unstackable = flags & slf_unstackable;

            if (unstackable) {
                if (stack_token) {
                    attachPara(grammar -> paraType(lexem), flags, true);

                    if (!grammar -> stackDropable(stack_token -> lexem, lexem))
                        cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state"));
                    else {
//                        lex_prev_word = stack_token -> stacked_state_lexem;

//                        if (lex_prev_word == lex_none)
//                            lex_prev_word = stack_token -> lexem;

                        stack_token = stack_token -> stacked_prev;
                    }
                } else {
                    cacheAndLightWithMessage(lex_error, QByteArrayLiteral("Wrong stack state"));
                }
            }

            if (stackable) {
                if (!heredoc_token) {
                    heredoc_token = token;
                }

                token -> stacked_prev = stack_token;
                stack_token = token;

//                stack_token -> stacked_state_lexem = lex_none; //stack_word ? lex_prev_word : lex_word;
                lex_prev_word = lex_none;

                attachPara(grammar -> paraType(lexem), flags, false);
            }

            lex_word = lex_none;
            lex_delimiter = lex_none;
        }
    }
//    inline void replaceToken(const StateLexem & lexem, const uint & flags = slf_none) {
//        token -> lexem = lexem;
//        token -> length += cached_length;

//        if (flags != slf_none && stack_token != token) {
//            token -> stacked_prev = stack_token;
//            stack_token = token;
//        }
//    }

    inline void validateHeredocState() {
        //TODO: remove all stack values till we have heredoc start on the top
        if (stack_token) {
            switch(stack_token -> lexem) {
                case lex_heredoc_intended_start:
                case lex_heredoc_start:
                case lex_cheredoc_intended_start:
                case lex_cheredoc_start:
                case lex_eheredoc_intended_start:
                case lex_eheredoc_start: { break;}

                default: {
                    lightWithMessage(
                        lex_error,
                        QByteArrayLiteral("Wrong stack state for begin of heredoc")
                    );
                }
            }
        }
    }
    inline void registerHeredocMark(const StateLexem & lexem, QByteArray * name) {
        StateLexem doc_lex = lex_none;

        switch(lexem) {
            case lex_heredoc_intended_mark:     { doc_lex = lex_heredoc_intended_start; break;}
            case lex_heredoc_mark:              { doc_lex = lex_heredoc_start; break;}
            case lex_cheredoc_intended_mark:    { doc_lex = lex_cheredoc_intended_start; break;}
            case lex_cheredoc_mark:             { doc_lex = lex_cheredoc_start; break;}
            case lex_eheredoc_intended_mark:    { doc_lex = lex_eheredoc_intended_start; break;}
            case lex_eheredoc_mark:             { doc_lex = lex_eheredoc_start; break;}
            default:;
        };

        if (doc_lex != lex_none) {
            TokenCell * new_heredoc =
                TokenList::insert(user_data -> token_begin, doc_lex, -1, 0);

            new_heredoc -> data = name;

            if (!heredoc_token) {
                new_heredoc -> stacked_prev = stack_token;
                heredoc_token = stack_token = new_heredoc;
            } else {
                new_heredoc -> stacked_prev = heredoc_token -> stacked_prev;
                heredoc_token -> stacked_prev = new_heredoc;
                heredoc_token = new_heredoc;
            }
        } else {
            int i = 0;
        }
    }

//    void popStack() {
//        if (!stack_token) return;

//        stack_token = stack_token -> stacked_prev;
//    }

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
            //TODO: return me later
//            if (!msg.contains("error_token"))
//                qWarning() << msg;
        }

        user_data -> msgs.append(MsgInfo{lexem, last_light_pos, last_light_len, msg});
    }

    inline void attachPara(const ParaType & ptype, const uint & flags, const bool & closable) {
        if (!ptype) return;

        bool replaceable = flags & slf_replace_word;

        if (!replaceable || (replaceable && closable)) {
            if (para -> next) {
                para = para -> next;

                para -> para_type = ptype;
                para -> pos = cached_str_pos;

                if (para -> close) {
                    para -> close -> close = nullptr;
                    para -> close = nullptr;
                }

                para -> is_foldable = false;
                para -> is_oneliner = false;
            }
            else para = ParaList::insert(para, ptype, cached_str_pos);

            para -> is_blockator = !replaceable;
        }

        if (closable) {
            para -> is_opener = false;

            if (!active_para || active_para -> close) {
                active_para = lastNonClosedPara(false);

                if (!active_para) {
                    qDebug() << "Can't find nonclosed active para token";
                    return;
                }
            }

            if (active_para -> is_blockator) {
                if (!para -> is_blockator)
                    active_para = para;
            } else {
                active_para -> is_oneliner = paraInActiveParaLine(para);

                ParaCell * potential_closer = nullptr;

                if (replaceable || !active_para -> is_blockator) {
                    if (active_para -> is_oneliner) {
                        if (para -> next) {
                            para = para -> next;

                            para -> para_type = pt_close;
                            para -> pos = cached_str_pos;

                            if (para -> close) {
                                para -> close -> close = nullptr;
                                para -> close = nullptr;
                            }

                            para -> is_foldable = false;
                            para -> is_oneliner = false;
                        }
                        else para = ParaList::insert(para, pt_close, cached_str_pos);

                        potential_closer = para;
                        active_para -> is_oneliner = true;
                    } else {
                        potential_closer = lastNonClosedPara(true);

                        if (!potential_closer) {
                            qDebug() << "Can't find closer for replaceable";
                            return;
                        }

                        active_para -> is_oneliner = paraIsNextToActiveParaLine(potential_closer);
                    }
                } else {
                    potential_closer = para;
                }

                active_para -> close = potential_closer;
                potential_closer -> close = active_para;

                if (active_para -> is_foldable && (replaceable || (!replaceable && !active_para -> is_oneliner)))
                    --user_data -> level;

                if (!replaceable) {
                    active_para = lastNonClosedPara(false);
                }
            }

            if (!replaceable && active_para && active_para -> is_blockator) {
                active_para -> close = para;
                active_para -> is_oneliner = paraInActiveParaLine(para);

                if (active_para -> is_foldable && !active_para -> is_oneliner)
                    --user_data -> level;

                para -> close = active_para;
            }
        } else {
            para -> is_opener = true;
            active_para = para;

            if (!control_para && (para -> is_foldable = ptype & pt_foldable)) {
                control_para = para;
            }
        }
    }
};

#endif // LEXER_CONTROL_H
