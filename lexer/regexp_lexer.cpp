#include "regexp_lexer.h"

#include "highlighter/highlight_format_factory.h"

RegexpLexer::RegexpLexer() : ILexer() {
//    HighlightingRule rule;

//    keywordFormat.setForeground(Qt::darkBlue);
//    keywordFormat.setFontWeight(QFont::Bold);
//    QStringList keywordPatterns;
//    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
//                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
//                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
//                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
//                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
//                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
//                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
//                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
//                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
//                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b";
//    foreach (const QString &pattern, keywordPatterns) {
//        rule.pattern = QRegularExpression(pattern);
//        rule.format = keywordFormat;
//        highlightingRules.append(rule);
//    }

//    classFormat.setFontWeight(QFont::Bold);
//    classFormat.setForeground(Qt::darkMagenta);
//    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
//    rule.format = classFormat;
//    highlightingRules.append(rule);

//    singleLineCommentFormat.setForeground(Qt::red);
//    rule.pattern = QRegularExpression("//[^\n]*");
//    rule.format = singleLineCommentFormat;
//    highlightingRules.append(rule);

//    multiLineCommentFormat.setForeground(Qt::red);

//    quotationFormat.setForeground(Qt::darkGreen);
//    rule.pattern = QRegularExpression("\".*\"");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

//    functionFormat.setFontItalic(true);
//    functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = functionFormat;
//    highlightingRules.append(rule);

//    commentStartExpression = QRegularExpression("/\\*");
//    commentEndExpression = QRegularExpression("\\*/");
}

RegexpLexer::~RegexpLexer() {
    qDeleteAll(_rules);
    _rules.clear();
}

void RegexpLexer::handle(const QString & text, Highlighter * lighter) {
    lighter -> setCurrentBlockState(0);

    for(RulesList::ConstIterator it = _rules.cbegin(); it != _rules.cend(); it++) {
        const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor((*it) -> format_uid);

        if ((*it) -> end_pattern) {
            int start_index = 0;
            if (lighter -> previousBlockState() != 1)
                start_index = text.indexOf(*(*it) -> start_pattern);

            while (start_index >= 0) {
                QRegularExpressionMatch match = (*it) -> end_pattern -> match(text, start_index);

                int end_index = match.capturedStart();
                int captured_length = 0;

                if (end_index == -1) {
                    lighter -> setCurrentBlockState(1);
                    captured_length = text.length() - start_index;
                } else {
                    captured_length =
                        end_index - start_index + match.capturedLength();
                }

                lighter -> setFormat(start_index, captured_length, format);
                start_index = text.indexOf(*(*it) -> start_pattern, start_index + captured_length);
            }
        } else {
            QRegularExpressionMatchIterator match_iterator = (*it) -> start_pattern -> globalMatch(text);

            while (match_iterator.hasNext()) {
                QRegularExpressionMatch match = match_iterator.next();
                lighter -> setFormat(match.capturedStart(), match.capturedLength(), format);
            }
        }
    }

//    foreach (const HighlightingRule &rule, highlightingRules) {
//
//        while (matchIterator.hasNext()) {
//            QRegularExpressionMatch match = matchIterator.next();
//            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
//        }
//    }
//    setCurrentBlockState(0);

//    int startIndex = 0;
//    if (previousBlockState() != 1)
//        startIndex = text.indexOf(commentStartExpression);

//    while (startIndex >= 0) {
//        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
//        int endIndex = match.capturedStart();
//        int commentLength = 0;
//        if (endIndex == -1) {
//            setCurrentBlockState(1);
//            commentLength = text.length() - startIndex;
//        } else {
//            commentLength = endIndex - startIndex
//                            + match.capturedLength();
//        }
//        setFormat(startIndex, commentLength, multiLineCommentFormat);
//        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
//    }
}
