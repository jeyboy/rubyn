#ifndef ILEXER_H
#define ILEXER_H

#include <qstring.h>

#include "highlighter/highlighter.h"

#define ERROR_STATE(msg, lex1, lex2) msg + QByteArrayLiteral(" (") + Lexems::toStr(lex1) + QByteArrayLiteral(" VS ") + Lexems::toStr(lex2) + QByteArrayLiteral(")")

class ILexer {

    //unsigned int hCount(0);
    //for(QString::const_iterator itr(str.begin()); itr != str.end(); ++itr)
    //    if(*itr == '#') ++hCount;

    //C++11

    //unsigned int hCount{0}; for(const auto& c : str) if(c == '#') ++hCount;

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

public:
    ILexer();

    inline virtual ~ILexer() {}

    virtual void handle(const QString & text, Highlighter * lighter) = 0;

//    virtual bool dump(QIODevice * device, ) { return false; }

    virtual void calcFoldings() {}
};

#endif // ILEXER_H
