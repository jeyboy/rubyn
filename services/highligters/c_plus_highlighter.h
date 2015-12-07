#ifndef C_PLUS_HIGHLIGHTER
#define C_PLUS_HIGHLIGHTER

#include "base/ihighlighter.h"

class CPlusHighLighter : public IHighlighter {
protected:
    void initRules() {
        HighlightingRule rule;

        QTextCharFormat keywordFormat;
        keywordFormat.setForeground(Qt::darkBlue);
        keywordFormat.setFontWeight(QFont::Bold);

        //TODO: move to external static variable
        QStringList keywordPatterns;
        keywordPatterns << "char" << "class" << "const"
                        << "double" << "enum" << "explicit"
                        << "friend" << "inline" << "int"
                        << "long" << "namespace" << "operator"
                        << "private" << "protected" << "public"
                        << "short" << "signals" << "signed"
                        << "slots" << "static" << "struct"
                        << "template" << "typedef" << "typename"
                        << "union" << "unsigned" << "virtual"
                        << "void" << "volatile";
        for(QStringList::ConstIterator pattern = keywordPatterns.constBegin(); pattern != keywordPatterns.constEnd(); pattern++) {
            rule.pattern = QRegExp(QString("\\b" + (*pattern) + "\\b"));
            rule.format = keywordFormat;
            highlightingRules.append(rule);
        }

        QTextCharFormat classFormat;
        classFormat.setFontWeight(QFont::Bold);
        classFormat.setForeground(Qt::darkMagenta);
        rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
        rule.format = classFormat;
        highlightingRules.append(rule);


        QTextCharFormat quotationFormat;
        quotationFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegExp("\".*\"");
        rule.format = quotationFormat;
        highlightingRules.append(rule);

        QTextCharFormat functionFormat;
        functionFormat.setFontItalic(true);
        functionFormat.setForeground(Qt::blue);
        rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = functionFormat;
        highlightingRules.append(rule);

        rule.pattern = QRegExp("//[^\n]*");
        rule.format = singleLineCommentFormat;
        highlightingRules.append(rule);

        commentStartExpression = QRegExp("/\\*");
        commentEndExpression = QRegExp("\\*/");
    }
public:
    CPlusHighLighter(QTextDocument * parent) : IHighlighter(parent) { initRules(); }
};

#endif // C_PLUS_HIGHLIGHTER
