#ifndef REGEXP_LEXER_H
#define REGEXP_LEXER_H

#include "ilexer.h"

#include <QTextCharFormat>
#include <QRegularExpression>

class RegexpLexer : public ILexer {
public:
    RegexpLexer();

    void handle(const QString & text, Highlighter * lighter);
private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> rules;


//    QRegularExpression commentStartExpression;
//    QRegularExpression commentEndExpression;

//    QTextCharFormat keywordFormat;
//    QTextCharFormat classFormat;
//    QTextCharFormat singleLineCommentFormat;
//    QTextCharFormat multiLineCommentFormat;
//    QTextCharFormat quotationFormat;
//    QTextCharFormat functionFormat;
};

#endif // REGEXP_LEXER_H
