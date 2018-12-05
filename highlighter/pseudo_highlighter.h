#ifndef PSEUDO_HIGHLIGHTER_H
#define PSEUDO_HIGHLIGHTER_H

#include "highlighter/ihighlighter.h"

class ILexer;

class PseudoHighlighter : public IHighlighter {
    QVector<QTextBlock> blocks;

    int current_block_num;
public:
    PseudoHighlighter();
    ~PseudoHighlighter();

    void analyze(ILexer * lexer, const QString & text);
    void analyze(ILexer * lexer, QIODevice * file);

    void setFillStyles(const bool & fill) { fill_styles = fill; }

    void highlightBlock(const QString & text);

    QTextBlock prevBlock() const;
    QTextBlock currentBlock() const;
    QTextBlock nextBlock() const;

    int previousBlockState() const;
    int currentBlockState() const;
    void setCurrentBlockState(const int & new_state);
};

#endif // PSEUDO_HIGHLIGHTER_H
