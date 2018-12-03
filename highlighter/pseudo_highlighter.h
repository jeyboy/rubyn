#ifndef PSEUDO_HIGHLIGHTER_H
#define PSEUDO_HIGHLIGHTER_H

#include "highlighter/ihighlighter.h"

class PseudoHighlighter : public IHighlighter {
public:
    PseudoHighlighter();
    ~PseudoHighlighter();

    QTextBlock prevBlock() const;
    QTextBlock currentBlock() const;
    QTextBlock nextBlock() const;

    bool toggleFolding(const QTextBlock & blk);

    void setFormat(const int & start, const int & count, const QTextCharFormat & format);
    void setFormat(const int & start, const int & count, const QColor & color);
    void setFormat(const int & start, const int & count, const QFont & font);

    int previousBlockState() const;
    int currentBlockState() const;
    void setCurrentBlockState(const int & new_state);
    void initBlockUserData(QTextBlock & block, BlockUserData * prev_udata, BlockUserData *& udata, const int & text_len);
};

#endif // PSEUDO_HIGHLIGHTER_H
