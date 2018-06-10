#ifndef HIGHLIGHT_RULE_H
#define HIGHLIGHT_RULE_H

#include "parts/lexer/lexems.h"

#include <QRegularExpression>

struct HighlightingRule {
    QRegularExpression * start_pattern;
    QRegularExpression * end_pattern;
    Lexem format_lexem;

    HighlightingRule() : start_pattern(0), end_pattern(0), format_lexem(lex_none) {}

    HighlightingRule(QRegularExpression * spattern, const Lexem & format_token, QRegularExpression * epattern = 0)
        : start_pattern(spattern), end_pattern(epattern), format_lexem(format_token) { }

    ~HighlightingRule() {
        delete start_pattern;
        delete end_pattern;
    }
};

#endif // HIGHLIGHT_RULE_H
