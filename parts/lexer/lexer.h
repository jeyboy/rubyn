#ifndef LEXER_H
#define LEXER_H

#include <qstring.h>
#include <qdatetime.h>
#include <qdebug.h>

#include "lexer_state.h"
#include "parts/formats/format_types.h"

#define PREV_N_CHAR(w, offset) (*(w - offset))
#define NEXT_N_CHAR(w, offset) (*(w + offset))

#define CURR_CHAR(w) (*w)
#define PREV_CHAR(w) PREV_N_CHAR(w, 1)
#define NEXT_CHAR(w) NEXT_N_CHAR(w, 1)

#define CURRCHAR CURR_CHAR(window)
#define NEXTCHAR NEXT_CHAR(window)
#define PREVCHAR PREV_CHAR(window)

// TODO: use ++state -> index && *(++window)
#define ITERATE {\
        ++state -> index; \
        ++window;\
    }
#define MOVE(offset) {\
        state -> index += offset; \
        window += offset; \
    }


#define APPEND_ERR(err) \
    lexems_cursor = (\
        lexems_cursor -> next =\
            new LexError(\
                state -> index,\
                word_length,\
                err\
            )\
    );

class Lexer {
protected:
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

    virtual LexToken * parse(const char * window, LexerState * state) = 0;

public:
    LexToken * analize(const QString & text, LexerState * state = new LexerState()) {
        QByteArray text_val = text.toUtf8();
        const char * window = text_val.constData();

        quint64 date = QDateTime::currentMSecsSinceEpoch();
        LexToken * root = parse(window, state);
        qDebug() << "SSOOS: " << (QDateTime::currentMSecsSinceEpoch() - date);
        return root;
    }

    virtual ~Lexer() {}

    virtual FormatType format() const = 0;
};

#endif // LEXER_H
