#include "highlighter.h"

#include "parts/lexer/lexer.h"
#include "highlight_format_factory.h"

Highlighter::Highlighter(QTextDocument * parent, Lexer * lexer)
    : QSyntaxHighlighter(parent), lexer(lexer), lexer_state(new LexerState()) {}

Highlighter::~Highlighter() { delete lexer; }

void Highlighter::highlightBlock(const QString & text) {
//    qDebug() << "*** " << currentBlock().firstLineNumber();

//    currentBlock().userData();

    LexToken * lexems = lexer -> analize(text, lexer_state);

    while(lexems) {
        LexToken * curr = lexems;
        lexems = lexems -> next;

        setFormat(curr -> left, curr -> length, HighlightFormatFactory::obj().getFormatFor(curr -> lexem));

        delete curr;
    }

//    const QVector<HighlightingRule> & highlightingRules = preset -> rules();
//    for(QVector<HighlightingRule>::ConstIterator rule = highlightingRules.constBegin(); rule != highlightingRules.constEnd(); rule++) {
//        QRegularExpressionMatchIterator i = (*rule).pattern.globalMatch(text);

//        while (i.hasNext()) {
//            QRegularExpressionMatch match = i.next();
//            setFormat(match.capturedStart(), match.capturedLength(), (*rule).format);
//        }
//    }
//    setCurrentBlockState(0);

//    if (!preset -> commentStartExpression().isValid()) return;

//    int startIndex = 0;
//    while(true) {
//        if (startIndex > 0 || (startIndex == 0 && previousBlockState() != 1)) {
//            QRegularExpressionMatch startMatch = preset -> commentStartExpression().match(text, startIndex);
//            if (!startMatch.hasMatch()) return;
//            startIndex = startMatch.capturedStart();
//        }

//        QRegularExpressionMatch endMatch = preset -> commentEndExpression().match(text, startIndex);
//        int commentLength;

//        if (!endMatch.hasMatch()) {
//            setCurrentBlockState(1);
//            commentLength = text.length() - startIndex;
//        }
//        else commentLength = endMatch.capturedEnd() - startIndex;

//        setFormat(startIndex, commentLength, HighlightFormatFactory::obj().getFormatFor(format_multy_line_comment));

//        if (!endMatch.hasMatch()) return;
//        startIndex = endMatch.capturedEnd();
//    }
}
