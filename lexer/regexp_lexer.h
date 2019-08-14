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

    void handle(const QString & text, IHighlighter * lighter);

    bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end);
    bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & /*at_end*/);
    bool isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start);
};

#endif // REGEXP_LEXER_H
