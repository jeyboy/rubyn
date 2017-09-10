#ifndef LEXER_H
#define LEXER_H

#include <qstring.h>
#include <qdatetime.h>
#include <qdebug.h>

#include "lexer_state.h"
#include "parts/formats/format_types.h"

#include "parts/highligters/highlight_format_factory.h"

#define PREV_N_CHAR(w, offset) (*(w - offset))
#define NEXT_N_CHAR(w, offset) (*(w + offset))

#define CURR_CHAR(w) (*w)
#define PREV_CHAR(w) PREV_N_CHAR(w, 1)
#define NEXT_CHAR(w) NEXT_N_CHAR(w, 1)

#define CURRCHAR CURR_CHAR(state -> buffer)
#define NEXTCHAR NEXT_CHAR(state -> buffer)
#define NEXTCHAR2 NEXT_N_CHAR(state -> buffer, 2)
#define PREVCHAR PREV_CHAR(state -> buffer)

class Lexer {
protected:
    enum LexerStatus {
        ls_none = -1,
        ls_comment = 1,
        ls_comment_ended = 2,
    };

    inline bool isBDigit(const char & c) { return c == '0' || c == '1'; }
    inline bool isODigit(const char & c) { return c >= '0' && c <= '7'; }
    inline bool isDigit(const char & c) { return c >= '0' && c <= '9'; }
    inline bool isHDigit(const char & c) { return isDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }

    inline bool isUpper(const char & c) { return c >= 'A' && c <= 'Z'; }
    inline bool isLower(const char & c) { return c >= 'a' && c <= 'z'; }
    inline bool isAlpha(const char & c) { return isLower(c) || isUpper(c); }
    inline bool isAlphaNum(const char & c) { return isAlpha(c) || isDigit(c); }

    inline bool isWord(const char & c) { return c == '_' || isAlpha(c) || isDigit(c); }

    //    inline bool isCtrl(const char & c) { return c >= 0 && c < 0x20 || c == 0x7f; }
    inline bool isBlank(const char & c) { return c == ' ' || c == '\t'; }
    //    inline bool isSpace(const char & c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; }
        //template<typename ch_t> inline bool is_punct(ch_t c)   {   return c>='!' && c<='/' || c>=':' && c<='@' || c>='[' && c<='`' || c>='{' && c<='~';    }
        //template<typename ch_t> inline bool is_graph(ch_t c)   {   return c>='!' && c<='~';    }
        //template<typename ch_t> inline bool is_print(ch_t c)   {   return c>=' ' && c<='~';    }
        //template<typename ch_t> inline bool is_crlf(ch_t c) { return c=='\r' || c=='\n'; }

    virtual LexerStatus handle(const char * window, LexerState * state, Highlighter * lighter = 0) = 0;

public:
    void handle(const QString & text, Highlighter * lighter) {
        LexerState * state = 0;

        if (lighter) {
            QTextBlock prev_block = lighter -> prevBlock();

            BlockUserData * udata = reinterpret_cast<BlockUserData *>(prev_block.userData());

            if (!udata)
                state = new LexerState(lighter);
            else
                state = new LexerState(*udata -> state);
        }
        else state = new LexerState(lighter);

        QByteArray text_val = text.toUtf8();
        const char * window = text_val.constData();
        state -> setBuffer(window);

        quint64 date = QDateTime::currentMSecsSinceEpoch();
        LexerStatus lex_status = handle(state, lighter);
        qDebug() << "SSOOS: " << (QDateTime::currentMSecsSinceEpoch() - date);

        if (lighter) {
            QTextBlock block = lighter -> currentBlock();
            BlockUserData * cdata = reinterpret_cast<BlockUserData *>(block.userData());

            state -> index = 0;
            if (!cdata)
                cdata = new BlockUserData(false, false, state);
            else
                cdata -> state = state;

            block.setUserData(cdata);
            block.setUserState(lex_status);
        }
    }

    virtual ~Lexer() {}

    virtual FormatType format() const = 0;
};

#endif // LEXER_H
