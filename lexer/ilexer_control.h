#ifndef ILEXER_CONTROL_H
#define ILEXER_CONTROL_H

//#include "misc/stack.h"
#include "lexer_stack_flags.h"

#include "lexer/igrammar.h"
#include "lexer/state_lexem.h"

#include "highlighter/ihighlighter.h"
#include "highlighter/highlight_format_factory.h"

#define ECHAR0 (*(state -> buffer))
#define ECHAR1 (*(state -> buffer + 1))
#define ECHAR2 (*(state -> buffer + 2))
#define ECHAR3 (*(state -> buffer + 3))
#define ECHAR4 (*(state -> buffer + 4))
#define ECHAR5 (*(state -> buffer + 5))
#define ECHAR_1 (*(state -> buffer - 1))
#define ECHAR_2 (*(state -> buffer - 2))

#define SCHAR0 (*(state -> prev))
#define SCHAR1 (*(state -> prev + 1))
#define SCHAR2 (*(state -> prev + 2))

struct ILexerControl {
    IHighlighter * lighter;

    quint8 next_offset;

    TokenCell * heredoc_token;
    TokenCell * stack_token;
    TokenCell * token;
    TokenCell * last_non_blank_token;

    ParaCell * heredoc_para;
    ParaCell * para;
    ParaCell * control_para;
    ParaCell * active_para;

    ScopeCell * scope;

    Identifier last_uid;

    EDITOR_POS_TYPE cached_str_pos;
    EDITOR_LEN_TYPE cached_length;

    EDITOR_POS_TYPE last_light_pos;
    EDITOR_LEN_TYPE last_light_len;

    QString::ConstIterator buffer;
    QString::ConstIterator prev;
    QString::ConstIterator start;
    QString::ConstIterator end;

    QString cached;

    BlockUserData *& user_data;

    ILexerControl(BlockUserData *& user_data, TokenCell * stack_token = nullptr, IHighlighter * lighter = nullptr) :
        lighter(lighter), next_offset(1), heredoc_token(nullptr),
        stack_token(stack_token), token(user_data -> lineControlToken()), last_non_blank_token(nullptr),
        heredoc_para(nullptr), para(user_data -> lineControlPara()), control_para(nullptr), active_para(nullptr),
        scope(user_data -> lineControlScope()), last_uid(hid_none), cached_str_pos(0), cached_length(0), last_light_pos(-2),
        last_light_len(0), user_data(user_data)
    {}

    ~ILexerControl() {}

    inline void setBuffer(const QString & buff) {
        cached.clear();

        start = prev = buffer = buff.constBegin();
        end = buff.constEnd();

        cached_str_pos = cached_length = 0;
        next_offset = 1;
    }
    inline bool moveBufferToEnd() {
        if (buffer != end) {
            buffer = end;
            return true;
        }
        else return false;
    }
    inline bool isBufferStart() { return buffer == start; }
    inline bool isBufferEof() { return buffer >= end; }
    inline bool bufferIsEmpty() { return start == end; }
    inline bool strIsEmpty() { return buffer - prev == 0; }

    virtual void postCachingPredecate() {
        //            if (lex_word != lex_none) {
        //                lex_prev_word = lex_word;
        //            }
    }
    virtual void postCachingDelimiter() {
        // //        if (lex_word == lex_none)
        // //            lex_prev_delimiter = lex_delimiter;
    }

    inline void cachingPredicate() {
        cached_str_pos = bufferPos();
        cached_length = strLength();
        cached.setRawData(prev, cached_length);

        postCachingPredecate();
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

    inline EDITOR_POS_TYPE scratchPos() { return buffer - start; }
    inline EDITOR_POS_TYPE scratchLength() { return end - buffer; }
    inline EDITOR_POS_TYPE bufferPos() { return prev - start; }
    inline EDITOR_LEN_TYPE strLength() { return static_cast<EDITOR_LEN_TYPE>(buffer - prev); }

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

        //// REMOVE ME
        if (uid == hid_error)
            return;
        ////

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
    virtual void light(const LEXEM_TYPE & lexem) = 0;
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
};

#endif // ILEXER_CONTROL_H
