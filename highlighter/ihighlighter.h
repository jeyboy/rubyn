#ifndef IHIGHLIGHTER_H
#define IHIGHLIGHTER_H

#include "editor/block_user_data.h"

class IHighlighter {
protected:
    QTextCharFormat default_format;
    QVector<QTextCharFormat> format_changes;

    bool fill_styles;

    TokenList * _tokens;
    ParaList * _paras;
    ScopeList * _scopes;

    inline void initFormats(const int length) {
        if (fill_styles)
            format_changes.fill(default_format, length);
    }

    static bool adjustRange(QTextLayout::FormatRange & range, int from, int charsRemoved, int charsAdded) {
        if (range.start >= from) {
            range.start += charsAdded - charsRemoved;
            return true;
        } else if (range.start + range.length > from) {
            range.length += charsAdded - charsRemoved;
            return true;
        }
        return false;
    }
public:
    IHighlighter() : fill_styles(true), _tokens(new TokenList()), _paras(new ParaList()), _scopes(new ScopeList()) {}
    virtual ~IHighlighter();

    virtual BlockUserData * prevUserData() = 0;
    virtual BlockUserData * userData() = 0;
    virtual void setCurrentUserData(BlockUserData *) = 0;

    virtual int prevUserState() = 0;
    virtual int userState() = 0;
    virtual void setUserState(const int & state) = 0;

    virtual bool toggleFolding() { return false; }

    void setFormat(const int & start, const int & count, const QTextCharFormat & format);
    void setFormat(const int & start, const int & count, const QColor & color);
    void setFormat(const int & start, const int & count, const QFont & font);

    void initCurrentBlockUserData(BlockUserData * prev_udata, BlockUserData *& udata, const int & text_len);
};

#endif // IHIGHLIGHTER_H
