#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>
#include "misc/token_list.h"

struct BlockUserData : public QTextBlockUserData {
    bool has_folding;
    bool has_break_point;

    TokenCell * begin_token;
    TokenCell * end_token;
public:
    inline BlockUserData(TokenList * file_tokens, TokenCell * prev_token = 0, bool has_break_point = false, bool has_folding = false)
        : has_folding(has_folding), has_break_point(has_break_point), begin_token(0), end_token(0)
    {
        file_tokens -> registerLine(begin_token, end_token, prev_token);
    }

    inline TokenCell * lineControlToken() { return end_token -> prev; }

    inline Lexem prevLineState() {
        TokenCell * curr = begin_token -> prev -> prev;
        return curr ? curr -> lexem : lex_none;
    }

    inline ~BlockUserData() {
        TokenList::removeLine(begin_token, end_token);
    }
};

#endif // BLOCK_USER_DATA_H
