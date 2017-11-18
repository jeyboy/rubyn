#ifndef PARA_INFO_H
#define PARA_INFO_H

#include <qobject.h>

struct ParaInfo {
    char symbol;
    quint64 pos;

    static char paraSymbol(const char & ch) {
        switch(ch) {
            case '(': return ')';
            case '[': return ']';
            case '{': return '}';

            default: return ch;
        };
    }

    inline char paraSymbol() { return ParaInfo::paraSymbol(symbol); }
};

#endif // PARA_INFO_H
