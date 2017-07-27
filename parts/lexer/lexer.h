#ifndef LEXER_H
#define LEXER_H

#include <qstring.h>
#include <qdatetime.h>

#include "scopes/scope_node.h"

//template<typename ch_t> inline bool is_cntr(ch_t c)    {   return c>=0 && c<0x20 || c==0x7f;   }
//template<typename ch_t> inline bool is_blank(ch_t c)   {   return c==' ' || c=='\t';   }
//template<typename ch_t> inline bool is_space(ch_t c)   {   return c==' ' || c=='\t' || c=='\n' || c=='\r' || c=='\f' || c=='\v';   }
//template<typename ch_t> inline bool is_upper(ch_t c)   {   return c>='A' && c<='Z';    }
//template<typename ch_t> inline bool is_lower(ch_t c)   {   return c>='a' && c<='z';    }
//template<typename ch_t> inline bool is_alpha(ch_t c)   {   return c>='a' && c<='z' || c>='A' && c<='Z';    }
//template<typename ch_t> inline bool is_digit(ch_t c)   {   return c>='0' && c<='9';    }
//template<typename ch_t> inline bool is_xdigit(ch_t c)  {   return c>='0' && c<='9' || c>='a' && c<='f' || c>='A' && c<='F';    }
//template<typename ch_t> inline bool is_alnum(ch_t c)   {   return is_alpha(c) || is_digit(c);    }
//template<typename ch_t> inline bool is_punct(ch_t c)   {   return c>='!' && c<='/' || c>=':' && c<='@' || c>='[' && c<='`' || c>='{' && c<='~';    }
//template<typename ch_t> inline bool is_graph(ch_t c)   {   return c>='!' && c<='~';    }
//template<typename ch_t> inline bool is_print(ch_t c)   {   return c>=' ' && c<='~';    }
//template<typename ch_t> inline bool is_crlf(ch_t c) { return c=='\r' || c=='\n'; }


class Lexer {

    bool parseStr(const char * window) {
        const char & end_cmb = *window;

        while(*++window) {
            switch(*window) {
                case '"':
                case '\'': {
                    if (*window == end_cmb && *(window - 1) != '\\')
                        return true;
                break;}

                default:;
            }
        }

        return false;
    }
public:
    void analize(const QString & text) {
        QByteArray text_val = text.toUtf8();
        analize(text_val);
    }

    void analize(const QByteArray & text) {
        ScopeNode * scope = new ScopeNode(0);

        quint64 date = QDateTime::currentMSecsSinceEpoch();
        const char * window = text.constData(), * prev = window;

        while(window) {
            switch(*window) {
                case ' ': {
                    int i = 0;
                break;}

                case '.': {
                    int i = 0;
                break;}

                case ',': {
                    int i = 0;
                break;}

                case '\'':
                case '"': {
                    int i = 0;
                    parseStr(window); // if false return error
                break;}

                case ':': {
                    int i = 0;
                break;}

                case '=': {
                    int i = 0;
                break;}
                case '|': {
                    int i = 0;
                break;}
                case '&': {
                    int i = 0;
                break;}
                case '!': {
                    int i = 0;
                break;}
                case '?': {
                    int i = 0;
                break;}
                case '<': {
                    int i = 0;
                break;}
                case '>': {
                    int i = 0;
                break;}


                case '[': {
                    int i = 0;
                break;}
                case ']': {
                    int i = 0;
                break;}

                case '(': {
                    int i = 0;
                break;}
                case ')': {
                    int i = 0;
                break;}

                case '{': {
                    int i = 0;
                break;}
                case '}': {
                    int i = 0;
                break;}

                case '#': {
                    int i = 0;
                break;}

                case '*':
                case '/':
                case '+':
                case '-': {
                    int i = 0;
                break;}

                case '@': {
                    int i = 0;
                break;}
                case '$': {
                    int i = 0;
                break;}

                case '\\': {
                    int i = 0;
                break;}

                case '~': {
                    int i = 0;
                break;}

                case ';': {
                    int i = 0;
                break;}

                default:;
            }

            ++window;
        }

        qDebug() << (QDateTime::currentMSecsSinceEpoch() - date);
    }
};

#endif // LEXER_H
