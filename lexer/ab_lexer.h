#ifndef AB_LEXER_H
#define AB_LEXER_H

#include "ilexer.h"

class ABLexer : public ILexer {
    //    TokenList * _tokens;
    //    ParaList * _paras;
    //    Scope * _scope;
    //    Lexer * _lexer;
public:
    ABLexer();

    ~ABLexer();

    void handle(const QString & text, Highlighter * lighter);

    void calcFoldings();
};

#endif // AB_LEXER_H
