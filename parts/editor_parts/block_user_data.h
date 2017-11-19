#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>
#include "misc/token_list.h"
#include "misc/stack.h"

#include "para_info.h"
#include "msg_info.h"

struct BlockUserData : public QTextBlockUserData {
    bool has_folding;
    bool has_break_point;

    TokenCell * begin_token;
    TokenCell * end_token;
    Stack<Lexem> * stack;

    QList<ParaInfo> pairs;
    QList<MsgInfo> msgs;
public:
    inline BlockUserData(TokenList * file_tokens, TokenCell * prev_token = 0, bool has_break_point = false, bool has_folding = false)
        : has_folding(has_folding), has_break_point(has_break_point), begin_token(0), end_token(0), stack(0)
    {
        file_tokens -> registerLine(begin_token, end_token, prev_token);
    }

    inline TokenCell * lineControlToken() {
        end_token -> prev -> next = 0; // detach end line
        return begin_token;
    }

    inline void syncLine(TokenCell * last_sync, Stack<Lexem> * stack_state) {
        delete stack;
        stack = stack_state;

        TokenCell * sync = last_sync -> next;

        if (sync) {
            while(sync -> next) {
                sync = sync -> next;
                delete sync -> prev;
            }

            delete sync;
        }

        end_token -> prev = last_sync;
        end_token -> prev -> next = end_token;
    }

    inline Stack<Lexem> * stackState() { return stack; }

    inline ~BlockUserData() {
        delete stack;
        TokenList::removeLine(begin_token, end_token);
    }
};

#endif // BLOCK_USER_DATA_H
