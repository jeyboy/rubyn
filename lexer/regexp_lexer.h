#ifndef REGEXP_LEXER_H
#define REGEXP_LEXER_H

#include "ilexer.h"

#include "highlighter/highlight_rule.h"

typedef QVector<HighlightingRule*> RulesList;

class RegexpLexer : public ILexer {
    QVector<HighlightingRule *> _rules;
protected:
    inline void addRule(HighlightingRule * rule) { _rules.append(rule); }

public:
    RegexpLexer();
    virtual ~RegexpLexer();

    void handle(const QString & text, Highlighter * lighter);
};

#endif // REGEXP_LEXER_H
