#ifndef IHIGHLIGHTER_H
#define IHIGHLIGHTER_H

#include "editor/block_user_data.h"

class IHighlighter {
protected:
    TokenList * _tokens;
    ParaList * _paras;
//    Scope * _scope;
public:
    IHighlighter() : _tokens(new TokenList()), _paras(new ParaList()) {}
    virtual ~IHighlighter();

    virtual QTextBlock prevBlock() const = 0;
    virtual QTextBlock currentBlock() const = 0;
    virtual QTextBlock nextBlock() const = 0;

    virtual bool toggleFolding(const QTextBlock & blk) = 0;

    virtual void setFormat(const int & start, const int & count, const QTextCharFormat & format) = 0;
    virtual void setFormat(const int & start, const int & count, const QColor & color) = 0;
    virtual void setFormat(const int & start, const int & count, const QFont & font) = 0;


    virtual int previousBlockState() const = 0;
    virtual int currentBlockState() const = 0;
    virtual void setCurrentBlockState(const int & new_state) = 0;
    virtual void initBlockUserData(QTextBlock & block, BlockUserData * prev_udata, BlockUserData *& udata, const int & text_len) = 0;
};

#endif // IHIGHLIGHTER_H
