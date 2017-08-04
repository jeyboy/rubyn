#ifndef LEXER_H
#define LEXER_H

#include <qstring.h>
#include <qdatetime.h>

#include "misc/stack.h"
#include "lexems.h"
#include "scopes/scope.h"

#define PREV_N_CHAR(w, offset) (*(w - offset))
#define NEXT_N_CHAR(w, offset) (*(w + offset))

#define PREV_CHAR(w) PREV_N_CHAR(w, 1)
#define NEXT_CHAR(w) NEXT_N_CHAR(w, 1)

class Lexer {
protected:
//    bool parseStr(const char * window) {
//        const char & end_cmb = *window;

//        while(*++window) {
//            switch(*window) {
//                case '"':
//                case '\'': {
//                    if (*window == end_cmb && *(window - 1) != '\\')
//                        return true;
//                break;}

//                default:;
//            }
//        }

//        return false;
//    }
    inline bool isBDigit(const char & c) { return c == '0' || c == '1'; }
    inline bool isODigit(const char & c) { return c >= '0' && c <= '7'; }
    inline bool isDigit(const char & c) { return c >= '0' && c <= '9'; }
    inline bool isHDigit(const char & c) { return isDigit(c) || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F'; }

    inline bool isUpper(const char & c) { return c >= 'A' && c <= 'Z'; }
    inline bool isLower(const char & c) { return c >= 'a' && c <= 'z'; }
    inline bool isAlpha(const char & c) { return isLower(c) || isUpper(c); }
    inline bool isAlphaNum(const char & c) { return isAlpha(c) || isDigit(c); }

    //    inline bool isCtrl(const char & c) { return c >= 0 && c < 0x20 || c == 0x7f; }
    //    inline bool isBlank(const char & c) { return c == ' ' || c == '\t'; }
    //    inline bool isSpace(const char & c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; }
        //template<typename ch_t> inline bool is_punct(ch_t c)   {   return c>='!' && c<='/' || c>=':' && c<='@' || c>='[' && c<='`' || c>='{' && c<='~';    }
        //template<typename ch_t> inline bool is_graph(ch_t c)   {   return c>='!' && c<='~';    }
        //template<typename ch_t> inline bool is_print(ch_t c)   {   return c>=' ' && c<='~';    }
        //template<typename ch_t> inline bool is_crlf(ch_t c) { return c=='\r' || c=='\n'; }

    virtual LexToken * parse(const char * window, Lexem lex_state, Scope * scope) = 0;

public:
    LexToken * analize(const QString & text, const Lexem & init = lex_none, Scope * scope = new Scope()) {
        QByteArray text_val = text.toUtf8();
        const char * window = text_val.constData();

        quint64 date = QDateTime::currentMSecsSinceEpoch();
        LexToken * root = parse(window, init, scope);
        qDebug() << (QDateTime::currentMSecsSinceEpoch() - date);
        return root;
    }
};

#endif // LEXER_H
