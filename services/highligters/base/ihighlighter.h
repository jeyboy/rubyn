#ifndef IHIGHLIGHTER_H
#define IHIGHLIGHTER_H

#include <qsyntaxhighlighter.h>
#include <qstringbuilder.h>

#include "highlighter_rule.h"

//class QTextDocument;

class IHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

protected:
//    virtual QStringList mimeTypes() = 0;
//    QStringList mimeTypes() {
//        QStringList list;
//        list << "h" << "cpp";
//        return list;
//    }

    virtual void initRules() = 0;

    void highlightBlock(const QString & text) Q_DECL_OVERRIDE;

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;
public:
    IHighlighter(QTextDocument * parent);
};

#endif // IHIGHLIGHTER_H
