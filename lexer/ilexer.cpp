#include "ilexer.h"

bool ILexer::isBDigit(const char & c) { return c == '0' || c == '1'; }
bool ILexer::isODigit(const char & c) { return c >= '0' && c <= '7'; }
bool ILexer::isDigit(const char & c) { return c >= '0' && c <= '9'; }
bool ILexer::isHDigit(const char & c) { return isDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }

bool ILexer::isUpper(const char & c) { return c >= 'A' && c <= 'Z'; }
bool ILexer::isLower(const char & c) { return c >= 'a' && c <= 'z'; }
bool ILexer::isAlpha(const char & c) { return isLower(c) || isUpper(c); }
bool ILexer::isAlphaNum(const char & c) { return isAlpha(c) || isDigit(c); }

bool ILexer::isWord(const char & c) { return c == '_' || isAlpha(c) || isDigit(c); }

//    bool ILexer::isCtrl(const char & c) { return c >= 0 && c < 0x20 || c == 0x7f; }
bool ILexer::isBlank(const char & c) { return c == ' ' || c == '\t'; }
//    bool ILexer::isSpace(const char & c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; }
    //template<typename ch_t> inline bool is_punct(ch_t c)   {   return c>='!' && c<='/' || c>=':' && c<='@' || c>='[' && c<='`' || c>='{' && c<='~';    }
    //template<typename ch_t> inline bool is_graph(ch_t c)   {   return c>='!' && c<='~';    }
    //template<typename ch_t> inline bool is_print(ch_t c)   {   return c>=' ' && c<='~';    }
    //template<typename ch_t> inline bool is_crlf(ch_t c) { return c=='\r' || c=='\n'; }

ILexer::ILexer() {

}

ILexer::~ILexer() {

}

void ILexer::calcFoldings() {

}
