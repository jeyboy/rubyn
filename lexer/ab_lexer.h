#ifndef AB_LEXER_H
#define AB_LEXER_H

#include "ilexer.h"

//#include "misc/token_list.h"
//#include "parts/lexer/scopes/scope.h"
//#include "parts/formats/format_types.h"

class ABLexer : public ILexer {
    //    TokenList * _tokens;
    //    ParaList * _paras;
    //    Scope * _scope;
    //    Lexer * _lexer;
public:
    ABLexer();

    ~ABLexer();

    virtual void handle(const QString & text, Highlighter * lighter) = 0;

//    void calcFoldings();
};

#endif // AB_LEXER_H
