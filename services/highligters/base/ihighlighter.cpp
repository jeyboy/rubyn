#include "ihighlighter.h"

IHighlighter::IHighlighter(QTextDocument * parent) : QSyntaxHighlighter(parent) {
    singleLineCommentFormat.setForeground(Qt::red);
    multiLineCommentFormat.setForeground(Qt::red);
}

void IHighlighter::highlightBlock(const QString & text) {
    for(QVector<HighlightingRule>::ConstIterator rule = highlightingRules.constBegin(); rule != highlightingRules.constEnd(); rule++) {
        QRegularExpressionMatchIterator i = (*rule).pattern.globalMatch(text);

        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            setFormat(match.capturedStart(), match.capturedLength(), (*rule).format);
        }
    }
    setCurrentBlockState(0);

    if (!commentStartExpression.isValid()) return;

    int startIndex = 0;
    while(true) {
        if (startIndex > 0 || (startIndex == 0 && previousBlockState() != 1)) {
            QRegularExpressionMatch startMatch = commentStartExpression.match(text, startIndex);
            if (!startMatch.hasMatch()) return;
            startIndex = startMatch.capturedStart();
        }

        QRegularExpressionMatch endMatch = commentEndExpression.match(text, startIndex);
        int commentLength;

        if (!endMatch.hasMatch()) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else commentLength = endMatch.capturedEnd() - startIndex;

        setFormat(startIndex, commentLength, multiLineCommentFormat);

        if (!endMatch.hasMatch()) return;
        startIndex = endMatch.capturedEnd();
    }
}
