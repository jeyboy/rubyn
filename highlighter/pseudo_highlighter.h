#ifndef PSEUDO_HIGHLIGHTER_H
#define PSEUDO_HIGHLIGHTER_H

#include "highlighter/ihighlighter.h"

class PseudoHighlighter : public IHighlighter {
    QVector<QTextBlock> blocks;

    QTextBlock current_block;
public:
    PseudoHighlighter();
    ~PseudoHighlighter();

    void analyze(const QString & text);
    void analyze(QIODevice * file);

    void setFillStyles(const bool & fill) { fill_styles = fill; }

    QTextBlock prevBlock() const;
    QTextBlock currentBlock() const;
    QTextBlock nextBlock() const;

    int previousBlockState() const;
    int currentBlockState() const;
    void setCurrentBlockState(const int & new_state);
};

#endif // PSEUDO_HIGHLIGHTER_H
