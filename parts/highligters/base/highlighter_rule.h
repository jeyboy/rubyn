#ifndef HIGHLIGHTER_RULE
#define HIGHLIGHTER_RULE

#include <qregularexpression.h>
#include <qtextformat.h>

struct HighlightingRule {
    QRegularExpression pattern;
    QTextCharFormat format;
};

#endif // HIGHLIGHTER_RULE
