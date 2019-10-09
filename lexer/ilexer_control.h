#ifndef ILEXER_CONTROL_H
#define ILEXER_CONTROL_H

//#include "misc/stack.h"
#include "lexer_stack_flags.h"
//#include "scopes/scope.h"
#include "lexer/igrammar.h"
#include "highlighter/ihighlighter.h"
#include "highlighter/highlight_format_factory.h"

//#define STREAM_N_CHAR(w, offset) (*(w + offset))

#define ECHAR0 *(state -> buffer)
#define ECHAR1 *(state -> buffer + 1)
#define ECHAR2 *(state -> buffer + 2)
#define ECHAR3 *(state -> buffer + 3)
#define ECHAR4 *(state -> buffer + 4)
#define ECHAR5 *(state -> buffer + 5)
#define ECHAR_1 *(state -> buffer - 1)

#define SCHAR0 *(state -> prev)
#define SCHAR1 *(state -> prev + 1)
#define SCHAR2 *(state -> prev + 2)

struct ILexerControl {
    IHighlighter * lighter;

    IGrammar * grammar;

    QByteArray cached;

    LEXEM_TYPE lex_prev_word;
    LEXEM_TYPE lex_word;
    LEXEM_TYPE lex_delimiter;

    quint8 next_offset;

    TokenCell * heredoc_token;
    TokenCell * stack_token;
    TokenCell * last_non_blank_token;
    TokenCell * token;

    TokenCell * scope_token;
    TokenCell * scope_stack_token;

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

    ILexerControl(IGrammar * cgrammar, BlockUserData *& user_data, TokenCell * stack_token = nullptr, IHighlighter * lighter = nullptr) :
        lighter(lighter), grammar(cgrammar),
        lex_prev_word(lex_none), lex_word(lex_none)/*, lex_prev_delimiter(DEFAULT_LEX_STATE)*/, lex_delimiter(lex_none),
        next_offset(1), heredoc_token(nullptr), stack_token(stack_token), last_non_blank_token(nullptr), token(user_data -> lineControlToken()),
        scope_token(user_data -> lineControlScope()), para(user_data -> lineControlPara()), control_para(nullptr), active_para(nullptr),
        last_uid(hid_none), cached_str_pos(0), cached_length(0), last_light_pos(-2),
        last_light_len(0), start(nullptr), buffer(nullptr), prev(nullptr), user_data(user_data)
    {}

    ~ILexerControl() {}


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

    inline EDITOR_POS_TYPE scratchPos() { return buffer - start; }
    inline EDITOR_POS_TYPE bufferPos() { return prev - start; }
    inline EDITOR_LEN_TYPE strLength() { return static_cast<EDITOR_LEN_TYPE>(buffer - prev); }

    inline LEXEM_TYPE & sublastToken() { return token -> prev -> lexem; }
    inline LEXEM_TYPE & lastToken() { return token -> lexem; }
    inline LEXEM_TYPE lastNonBlankLexem() {
        if (last_non_blank_token)
            return last_non_blank_token -> lexem;

        TokenCell * it = token;

        while(it) {
            if (it -> lexem >= lex_none)
                return (last_non_blank_token = it) -> lexem;

            it = it -> prev;
        }

        return lex_none;
    }

    inline void attachToken(const LEXEM_TYPE & lexem, const uint & flags = slf_none) {
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

        if (token -> lexem >= lex_none)
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

//            lex_word = lex_none;
//            lex_delimiter = lex_none;
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

//    void popStack() {
//        if (!stack_token) return;

//        stack_token = stack_token -> stacked_prev;
//    }

    void relightLast(const Identifier & uid) {
        last_uid = uid;

        lighter -> setFormat(
            last_light_pos, int(last_light_len),
            HighlightFormatFactory::obj().getFormatFor(last_uid)
        );
    }

    inline void light(const Identifier & uid) {
        if (uid == hid_none)
            return;

//        if (uid == hid_error)
//            return;

        bool has_predicate = cached_length > 0;

        EDITOR_POS_TYPE new_pos = cached_str_pos - (has_predicate ? 0 : 1);

        if (last_light_pos != new_pos || uid != last_uid) {
            last_light_pos = new_pos;
            last_light_len = has_predicate ? cached_length : 1;
            last_uid = uid;

            lighter -> setFormat(
                last_light_pos, int(last_light_len),
                HighlightFormatFactory::obj().getFormatFor(last_uid)
            );
        }
    }
    inline void light(const int & pos, const int & len, const Identifier & uid) {
        lighter -> setFormat(
            pos, len,
            HighlightFormatFactory::obj().getFormatFor(uid)
        );
    }
    inline void light(const LEXEM_TYPE & lexem) {
        light(grammar -> toHighlightable(lexem));
    }
    inline void cacheAndLightWithMessage(const LEXEM_TYPE & lexem, const QByteArray & msg) {
        cachingPredicate();
        lightWithMessage(lexem, msg);
    }
    inline void lightWithMessage(const LEXEM_TYPE & lexem, const QByteArray & msg) {
        light(lexem);

        if (lexem == lex_error) {
            return;
            //TODO: return me later
//            if (!msg.contains("error_token"))
//                qWarning() << msg;
        }

        user_data -> addMessage(MsgInfo{lexem, last_light_pos, last_light_len, msg});
    }


    inline ParaCell * prevFoldableInActiveParaLine(ParaCell * pcell) {
        ParaCell * it = pcell;

        while(it && it -> para_type != pt_none) {
            it = it -> prev;

            if (it -> is_foldable && it -> is_opener)
                return it;
        }

        return nullptr;
    }

//    inline ParaCell * lastNonClosedPara(const bool & replaceable) {
//        ParaCell * it = !replaceable && active_para ? active_para : para -> prev;

//        while(it) {
//            if (!it -> close && ((replaceable && it -> para_type == pt_none) || (!replaceable && it -> pos != -1))) {
//                return it;
//            }

//            it = it -> prev;
//        }

//        return nullptr;
//    }
//    inline bool paraInActiveParaLine(ParaCell * pcell) {
//        ParaCell * it = active_para;

//        while(it && it -> para_type != pt_max) {
//            if (it == pcell)
//                return true;

//            it = it -> next;
//        }

//        return false;
//    }
//    inline bool paraIsNextToActiveParaLine(ParaCell * pcell) {
//        ParaCell * it = active_para;

//        if (it) {
//            while(it -> para_type != pt_none && (it = it -> next));
//            return it == pcell;
//        }

//        return false;
//    }

    inline ParaCell * paraParent(int & lines_between, ParaCell * para, const bool & foldable, const bool & only_blockators = false) {
        ParaCell * it = para -> prev;
        lines_between = 0;

        while(it) {
            if (it -> pos == -1) {
                ++lines_between;
                it = it -> prev;

                if (it && it -> pos == -1)
                    it = it -> prev;
            } else {
                if (it -> is_opener && it -> is_foldable == foldable) {
                    if (!only_blockators || (only_blockators && it -> is_blockator))
                        return it;
                }

                if (!it -> is_opener && it -> closer) {
                    it = it -> closer;
                    // this broke foldable curly brackets
//                    lines_between += (it -> closer -> is_oneliner && it -> closer -> is_foldable ? 0 : 1);
                }

                it = it -> prev;
            }
        }

        return nullptr;
    }

    inline void attachPara(const ParaType & ptype, const uint & flags, const bool & closable) {
        if (!ptype) return;

        bool replaceable = flags & slf_replace_word;

        if (!replaceable || (replaceable && closable)) {
            if (para -> next) {
                para = para -> next;

                if (!para -> is_opener)
                    para -> closer = nullptr;

                para -> para_type = ptype;
                para -> pos = cached_str_pos;
                para -> length = quint8(cached_length); // 8 bits should be enough for any type of para

                para -> is_foldable = false;
                para -> is_oneliner = false;
            }
            else para = ParaList::insert(para, ptype, cached_str_pos, quint8(cached_length));

            para -> is_blockator = !replaceable;
        }

        para -> is_opener = !closable;
        para -> is_foldable = ptype & pt_foldable;

        if (closable) {
            int lines_between;
            ParaCell * parent = paraParent(lines_between, para, para -> is_foldable, false);

            if (parent) {
                if (para -> is_foldable) {
                    if (!replaceable && parent -> is_blockator == false) {
                        user_data -> level -= lines_between > 0 ? 2 : 1;

                        parent -> is_oneliner = parent -> is_blockator ? lines_between == 1 : lines_between < 2;

                        if (para -> is_foldable)
                            parent = paraParent(lines_between, para, true, true);
                    } else if (lines_between > 0 && parent -> is_blockator != replaceable) {
                        parent -> is_oneliner = lines_between < 2;
                        --user_data -> level;
                    }
                }

                if (parent) {
                    parent -> is_oneliner = parent -> is_oneliner || lines_between == 0;

                    if (!replaceable) {
                        if (parent -> closer && parent -> closer != para)
                            parent -> closer -> closer = nullptr;

                        parent -> closer = para;

                        if (para -> closer && para -> closer != parent)
                            para -> closer -> closer = nullptr;

                        para -> closer = parent;
                    }
                }
            }
            else para -> closer = nullptr;

            if (parent && parent -> is_oneliner && para -> is_foldable) {
                control_para = prevFoldableInActiveParaLine(parent);
                return;
            }
        }

        if (para -> is_foldable) {
            control_para = para;
        }
    }
};

#endif // ILEXER_CONTROL_H
