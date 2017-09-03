#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <qsyntaxhighlighter.h>
#include "parts/editor_parts/block_user_data.h"

class Lexer;
class LexerState;

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT
protected:
    void highlightBlock(const QString & text) Q_DECL_OVERRIDE;

    Lexer * lexer;

    friend class Lexer;
public:
    Highlighter(QTextDocument * parent, Lexer * lexer);
    ~Highlighter();

    QTextBlock prevBlock() const {
        return QSyntaxHighlighter::currentBlock().previous();
    }

    QTextBlock currentBlock() const {
        return QSyntaxHighlighter::currentBlock();
    }

    QTextBlock nextBlock() const {
        return QSyntaxHighlighter::currentBlock().next();
    }

    inline void setFormat(const int & start, const int & count, const QTextCharFormat & format) {
        QSyntaxHighlighter::setFormat(start, count, format);
    }

signals:

    void forceBlockRehighlightion(const QTextBlock &);
};

#endif // IHIGHLIGHTER_H
