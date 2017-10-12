#ifndef LEXER_H
#define LEXER_H

#include <qstring.h>
#include <qdatetime.h>
#include <qdebug.h>

#include "misc/token_list.h"

#include "lexer_state.h"
#include "parts/formats/format_types.h"
#include "parts/lexer/scopes/scope.h"


//unsigned int hCount(0);
//for(QString::const_iterator itr(str.begin()); itr != str.end(); ++itr)
//    if(*itr == '#') ++hCount;

//C++11

//unsigned int hCount{0}; for(const auto& c : str) if(c == '#') ++hCount;


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

    virtual void handle(LexerState * state) = 0;

    TokenList * tokens;
    Scope * scope;
public:
    void handle(const QString & text, Highlighter * lighter) {
        LexerState * state = 0;

        if (lighter) {
            QTextBlock block = lighter -> currentBlock();

            BlockUserData * udata = reinterpret_cast<BlockUserData *>(block.userData());

            if (!udata) {
                QTextBlock prev_block = lighter -> prevBlock();
                udata = reinterpret_cast<BlockUserData *>(prev_block.userData());
                udata = new BlockUserData(tokens, udata ? udata -> end : 0);

                block.setUserData(udata);
            }

            state = new LexerState(scope, udata -> begin, lighter);
        }

        state = new LexerState(scope, 0, lighter);

        QByteArray text_val = text.toUtf8();
        const char * window = text_val.constData();
        state -> setBuffer(window);

        quint64 date = QDateTime::currentMSecsSinceEpoch();
        handle(state);
        qDebug() << "SSOOS: " << (QDateTime::currentMSecsSinceEpoch() - date);

        if (lighter) {
            QTextBlock block = lighter -> currentBlock();
            block.setUserState(state -> status);
        }
    }

    Lexer() : tokens(new TokenList()), scope(new Scope()) {}

    virtual ~Lexer() {
        delete scope;
        delete tokens;
    }

    virtual FormatType format() const = 0;
};

#endif // LEXER_H
