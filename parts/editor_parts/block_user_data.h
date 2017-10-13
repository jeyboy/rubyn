#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>
#include "misc/token_list.h"

struct BlockUserData : public QTextBlockUserData {
    bool has_folding;
    bool has_break_point;

    TokenCell * begin;
    TokenCell * end;
public:
    BlockUserData(TokenList * file_tokens, TokenCell * prev = 0, bool has_break_point = false, bool has_folding = false)
        : has_folding(has_folding), has_break_point(has_break_point), begin(0), end(0)
    {
        file_tokens -> registerLine(begin, end, prev);
    }

    ~BlockUserData() {
        TokenList::removeLine(begin, end);
    }
};

#endif // BLOCK_USER_DATA_H
