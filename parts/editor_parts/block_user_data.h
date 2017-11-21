#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>
#include "misc/token_list.h"
#include "misc/stack.h"

#include "para_info.h"
#include "msg_info.h"

struct BlockUserData : public QTextBlockUserData {
    enum UserDataFlags : DATA_FLAGS_TYPE {
        udf_none = 0,
        udf_has_folding = 1,
        udf_folding_opened = 2 | udf_has_folding,
        udf_folding_hovered = 4,
        udf_has_breakpoint = 8,

        udf_folding_flags = udf_has_folding | udf_folding_opened
    };

    UserDataFlags flags;

    TokenCell * begin_token;
    TokenCell * end_token;

    Stack<Lexem> * stack;

    QList<ParaInfo> pairs;
    QList<MsgInfo> msgs;

    inline BlockUserData(TokenList * file_tokens, TokenCell * prev_token = 0, UserDataFlags data_flags = udf_has_folding/*udf_none*/)
        : flags(data_flags), begin_token(0), end_token(0), stack(0)
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

    inline DATA_FLAGS_TYPE foldingState() { return flags & udf_folding_flags; }
    inline bool hasBreakpoint() { return flags & udf_has_breakpoint; }

    inline void setFoldingState(const UserDataFlags & new_state) {
        flags = (UserDataFlags)((flags & (~(udf_folding_flags))) | (new_state & udf_folding_flags));
    }

    inline void invertFoldingState() {
        if (flags & udf_folding_flags) {
            setFoldingState(
                ((flags & udf_folding_opened) == udf_folding_opened) ?
                    udf_has_folding : udf_folding_opened
            );
        }
    }
};

#endif // BLOCK_USER_DATA_H
