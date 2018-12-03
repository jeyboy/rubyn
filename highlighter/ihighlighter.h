#ifndef IHIGHLIGHTER_H
#define IHIGHLIGHTER_H

#include "editor/block_user_data.h"

class IHighlighter {
    QTextCharFormat default_format;
protected:
    QVector<QTextCharFormat> format_changes;

    bool fill_styles;

    TokenList * _tokens;
    ParaList * _paras;
//    Scope * _scope;

    inline void initFormats(const int length) {
        if (fill_styles)
            format_changes.fill(default_format, length);
    }
public:
    IHighlighter() : fill_styles(true), _tokens(new TokenList()), _paras(new ParaList()) {}
    virtual ~IHighlighter();

    virtual QTextBlock prevBlock() const = 0;
    virtual QTextBlock currentBlock() const = 0;
    virtual QTextBlock nextBlock() const = 0;

    virtual int previousBlockState() const = 0;
    virtual int currentBlockState() const = 0;
    virtual void setCurrentBlockState(const int & new_state) = 0;

    virtual bool toggleFolding(const QTextBlock & /*blk*/) { return false; }

    void setFormat(const int & start, const int & count, const QTextCharFormat & format);
    void setFormat(const int & start, const int & count, const QColor & color);
    void setFormat(const int & start, const int & count, const QFont & font);

    void initBlockUserData(QTextBlock & block, BlockUserData * prev_udata, BlockUserData *& udata, const int & text_len);
};

#endif // IHIGHLIGHTER_H
