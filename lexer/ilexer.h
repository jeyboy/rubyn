#ifndef ILEXER_H
#define ILEXER_H

#include <qstring.h>

#include "highlighter/ihighlighter.h"

#define ERROR_STATE(msg, lex1, lex2) msg + QByteArrayLiteral(" (") + QByteArray::number(lex1) + QByteArrayLiteral(" VS ") + QByteArray::number(lex2) + QByteArrayLiteral(")")

class ILexer {
    //unsigned int hCount(0);
    //for(QString::const_iterator itr(str.begin()); itr != str.end(); ++itr)
    //    if(*itr == '#') ++hCount;

    //C++11

    //unsigned int hCount{0}; for(const auto& c : str) if(c == '#') ++hCount;
    quint8 int_bits_offset;
protected:
    bool isBDigit(const char & c);
    bool isODigit(const char & c);
    bool isDigit(const char & c);
    bool isHDigit(const char & c);

    bool isUpper(const char & c);
    bool isLower(const char & c);
    bool isAlpha(const char & c);
    bool isAlphaNum(const char & c);

    bool isWord(const char & c, const bool & with_digits = true);

    //    inline bool isCtrl(const char & c) { return c >= 0 && c < 0x20 || c == 0x7f; }
    bool isBlank(const char & c);
    //    inline bool isSpace(const char & c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; }
        //template<typename ch_t> inline bool is_punct(ch_t c)   {   return c>='!' && c<='/' || c>=':' && c<='@' || c>='[' && c<='`' || c>='{' && c<='~';    }
        //template<typename ch_t> inline bool is_graph(ch_t c)   {   return c>='!' && c<='~';    }
        //template<typename ch_t> inline bool is_print(ch_t c)   {   return c>=' ' && c<='~';    }
        //template<typename ch_t> inline bool is_crlf(ch_t c) { return c=='\r' || c=='\n'; }

    virtual int lineState(BlockUserData * udata);
public:
    ILexer();

    virtual ~ILexer();

    virtual void handle(const QString & text, IHighlighter * lighter) = 0;

    virtual void paraOpositionStr(const PARA_TYPE & /*para*/, QString & res) { res.clear(); }

    virtual bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end) = 0;
    virtual bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end) = 0;
    virtual bool isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start) = 0;

//    virtual bool dump(QIODevice * device, ) { return false; }
};

#endif // ILEXER_H
