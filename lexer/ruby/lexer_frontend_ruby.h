#ifndef LEXER_FRONTEND_RUBY_H
#define LEXER_FRONTEND_RUBY_H

#include "lexer/ilexer.h"



class LexerFrontendRuby : public ILexer {
    TokenList * _tokens;
    ParaList * _paras;
    Scope * _scope;

    void lexicate(const QString & text, Highlighter * lighter);
public:
    LexerFrontendRuby();

    void handle(const QString & text, Highlighter * lighter);
};

#endif // LEXER_FRONTEND_RUBY_H
