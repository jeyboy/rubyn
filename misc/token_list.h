#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "defines.h"
#include "lexer/state_lexems.h"

struct TokenCell {
    TokenCell * prev;
    TokenCell * next;

    TokenCell * stacked_prev;

    StateLexem lexem;
    EDITOR_POS_TYPE start_pos;
    EDITOR_LEN_TYPE length;

    QByteArray * data;

    TokenCell(const StateLexem & lexem, const EDITOR_POS_TYPE & start_pos,
              const EDITOR_LEN_TYPE & length, TokenCell * prev_token = nullptr)
        : prev(nullptr), next(nullptr), stacked_prev(nullptr),
          lexem(lexem), start_pos(start_pos), length(length), data(nullptr)
    {
        if ((prev = prev_token)) {
            if ((next = prev -> next))
                next -> prev = this;

            prev -> next = this;
        }
    }

    ~TokenCell() {
        delete data;

        if (prev)
            prev -> next = next;

        if (next)
            next -> prev = prev;
    }

    inline bool isStackState() { return stacked_prev != nullptr; }

    TokenCell * toPrevStackState() {
        TokenCell * t = stacked_prev;

        if (!t) {
            t = prev;

            while(!t -> stacked_prev) {
                t = t -> prev;
            }
        }

        return t;
    }
};

class TokenList {
    TokenCell * root, * last;
public:
    inline TokenList() : root(nullptr), last(nullptr) {
        root = new TokenCell(lex_none, 0, 0);
        last = new TokenCell(lex_end_doc, 0, 0, root);
    }

    inline ~TokenList() {
        clear();

        delete root;
        delete last;
    }

    inline void clear() {
        TokenCell * curr;

        while(last -> prev != root) {
            curr = last;
            last = last -> prev;
            delete curr;
        }
    }

    void registerLine(TokenCell *& left, TokenCell *& right, TokenCell * prev_end = nullptr) {
        if (!prev_end)
            prev_end = last -> prev;

        left = new TokenCell(lex_none, 0, 0, prev_end);
        right = new TokenCell(lex_end_line, 0, 0, left);
    }

    static void removeLine(TokenCell * left, TokenCell * right) {
        while(left && left != right) {
            TokenCell * curr = left;
            left = left -> next;

            delete curr;
        }

        delete right;
    }

    TokenCell * append(const StateLexem & lexem, const EDITOR_POS_TYPE & start_pos, const EDITOR_LEN_TYPE & length) {
        return new TokenCell(lexem, start_pos, length, last -> prev);
    }

    static TokenCell * insert(TokenCell * left, const StateLexem & lexem, const EDITOR_POS_TYPE & start_pos, const EDITOR_LEN_TYPE & length) {
        return new TokenCell(lexem, start_pos, length, left);
    }
};

#endif // TOKEN_LIST_H
