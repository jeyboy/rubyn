#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include <qglobal.h>
#include "parts/lexer/lexems.h"

#define TOKEN_TYPE quint32
#define TOKEN_LENGTH_TYPE quint16

struct TokenCell {
    TokenCell * prev;
    TokenCell * next;

    Lexem lexem;
    TOKEN_TYPE start_pos;
    TOKEN_LENGTH_TYPE length;

    TokenCell(const Lexem & lexem, const TOKEN_TYPE & start_pos,
              const TOKEN_LENGTH_TYPE & length, TokenCell * prev_token = 0)
        : prev(0), next(0), lexem(lexem), start_pos(start_pos), length(length)
    {
        if ((prev = prev_token)) {
            if ((next = prev -> next))
                next -> prev = this;

            prev -> next = this;
        }
    }

    ~TokenCell() {
        if (prev)
            prev -> next = next;

        if (next)
            next -> prev = prev;
    }
};

class TokenList {
    TokenCell * root, * last;
public:
    inline TokenList() : root(0), last(0) {
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

    void registerLine(TokenCell *& left, TokenCell *& right, TokenCell * prev_end = 0) {
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

    TokenCell * append(const Lexem & lexem, const TOKEN_TYPE & start_pos, const TOKEN_LENGTH_TYPE & length) {
        return new TokenCell(lexem, start_pos, length, last -> prev);
    }

    static TokenCell * insert(TokenCell * left, const Lexem & lexem, const TOKEN_TYPE & start_pos, const TOKEN_LENGTH_TYPE & length) {
        return new TokenCell(lexem, start_pos, length, left);
    }
};

#endif // TOKEN_LIST_H
