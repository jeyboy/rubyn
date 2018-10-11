#ifndef ILEXER_H
#define ILEXER_H

#include <qstring.h>

#include "highlighter/highlighter.h"

#define ERROR_STATE(msg, lex1, lex2) msg + QByteArrayLiteral(" (") + QByteArray::number(lex1) + QByteArrayLiteral(" VS ") + QByteArray::number(lex2) + QByteArrayLiteral(")")

class ILexer {
    //unsigned int hCount(0);
    //for(QString::const_iterator itr(str.begin()); itr != str.end(); ++itr)
    //    if(*itr == '#') ++hCount;

    //C++11

    //unsigned int hCount{0}; for(const auto& c : str) if(c == '#') ++hCount;

protected:
    bool isBDigit(const char & c);
    bool isODigit(const char & c);
    bool isDigit(const char & c);
    bool isHDigit(const char & c);

    bool isUpper(const char & c);
    bool isLower(const char & c);
    bool isAlpha(const char & c);
    bool isAlphaNum(const char & c);

    bool isWord(const char & c);

    //    inline bool isCtrl(const char & c) { return c >= 0 && c < 0x20 || c == 0x7f; }
    bool isBlank(const char & c);
    //    inline bool isSpace(const char & c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; }
        //template<typename ch_t> inline bool is_punct(ch_t c)   {   return c>='!' && c<='/' || c>=':' && c<='@' || c>='[' && c<='`' || c>='{' && c<='~';    }
        //template<typename ch_t> inline bool is_graph(ch_t c)   {   return c>='!' && c<='~';    }
        //template<typename ch_t> inline bool is_print(ch_t c)   {   return c>=' ' && c<='~';    }
        //template<typename ch_t> inline bool is_crlf(ch_t c) { return c=='\r' || c=='\n'; }

public:
    ILexer();

    virtual ~ILexer();

    virtual void handle(const QString & text, Highlighter * lighter) = 0;

    virtual bool getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_LEN_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos)  { return false; }

//    virtual bool dump(QIODevice * device, ) { return false; }
};

#endif // ILEXER_H
