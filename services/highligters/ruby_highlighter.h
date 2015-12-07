#ifndef RUBY_HIGHLIGHTER
#define RUBY_HIGHLIGHTER

#include "base/ihighlighter.h"

class RubyHighLighter : public IHighlighter {
protected:
    void initRules() {
        HighlightingRule rule;

        QTextCharFormat keywordFormat;
        keywordFormat.setForeground(Qt::darkBlue);
        keywordFormat.setFontWeight(QFont::Bold);
        QStringList keywordPatterns;

        //TODO: move to external static variable
        keywordPatterns << "alias" << "and" << "BEGIN"
                        << "begin" << "break" << "case"
                        << "class" << "def" << "define_method"
                        << "defined" << "do" << "each"
                        << "else" << "elsif" << "END"
                        << "end" << "ensure" << "false"
                        << "for" << "if" << "in"
                        << "module" << "new" << "next"
                        << "nil" << "not" << "or"
                        << "raise" << "redo" << "rescue"
                        << "retry" << "return" << "self"
                        << "super" << "then" << "throw"
                        << "true" << "undef" << "unless"
                        << "until" << "when" << "while"
                        << "yield";
        for(QStringList::ConstIterator pattern = keywordPatterns.constBegin(); pattern != keywordPatterns.constEnd(); pattern++) {
            rule.pattern = QRegExp("\\b" % (*pattern) % "\\b");
            rule.format = keywordFormat;
            highlightingRules.append(rule);
        }

        QTextCharFormat variableFormat; // need to check
        variableFormat.setFontWeight(QFont::Bold);
        variableFormat.setForeground(Qt::darkYellow);
        rule.pattern = QRegExp("\\$|@@|@)\\w+");
        rule.format = variableFormat;
        highlightingRules.append(rule);


        QTextCharFormat symbolFormat; // need to check
        symbolFormat.setFontWeight(QFont::Bold);
        symbolFormat.setForeground(Qt::darkCyan);
        rule.pattern = QRegExp(":[a-z][A-Za-z0-9_]*");
        rule.format = symbolFormat;
        highlightingRules.append(rule);

//        'Array Bignum Binding Class Continuation Dir Exception FalseClass File::Stat File Fixnum Fload Hash Integer IO MatchData Method Module NilClass Numeric Object Proc Range Regexp String Struct::TMS Symbol ThreadGroup Thread Time TrueClass'
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

        QTextCharFormat singleQuotationFormat;
        singleQuotationFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegExp("'.*'"); // need to check
        rule.format = singleQuotationFormat;
        highlightingRules.append(rule);

        QTextCharFormat functionFormat; // this block should be more complex
        functionFormat.setFontItalic(true);
        functionFormat.setForeground(Qt::blue);
        rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
        rule.format = functionFormat;
        highlightingRules.append(rule);

        rule.pattern = QRegExp("#[^\n]*");
        rule.format = singleLineCommentFormat;
        highlightingRules.append(rule);

        commentStartExpression = QRegExp("=begin");
        commentEndExpression = QRegExp("=end");
    }
public:
    RubyHighLighter(QTextDocument * parent) : IHighlighter(parent) { initRules(); }
};


#endif // RUBY_HIGHLIGHTER
