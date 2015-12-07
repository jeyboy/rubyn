#ifndef HIGHLIGHTER_RULE
#define HIGHLIGHTER_RULE

#include <qtextformat.h>

struct HighlightingRule {
    QRegExp pattern;
    QTextCharFormat format;
};

#endif // HIGHLIGHTER_RULE
