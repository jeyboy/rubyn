#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>

#include "para_list.h"
#include "msg_info.h"

#include "misc/token_list.h"
#include "misc/stack.h"

struct BlockUserData : public QTextBlockUserData {
    enum UserDataFlags : DATA_FLAGS_TYPE {
        udf_none = 0,
        udf_has_folding = 1,
        udf_folding_opened = 2 | udf_has_folding,
        udf_folding_hovered = 4,
        udf_folding_dropped = 8,
        udf_has_breakpoint = 16,

        udf_folding_flags = udf_has_folding | udf_folding_opened
    };

    UserDataFlags flags;

    TokenCell * token_begin;
    TokenCell * token_end; // maybe no need to store end token ?

    ParaCell * para_begin;
    ParaCell * para_end; // maybe no need to store end token ?
    ParaCell * para_control;

    Stack<Lexem> * stack;

    QList<MsgInfo> msgs;

    inline BlockUserData(TokenList * tokens, ParaList * paras, TokenCell * token_prev = 0, ParaCell * para_prev = 0, UserDataFlags data_flags = udf_none)
        : flags(data_flags), token_begin(0), token_end(0), para_begin(0), para_end(0), para_control(0), stack(0)
    {
        tokens -> registerLine(token_begin, token_end, token_prev);
        paras -> registerLine(para_begin, para_end, para_prev);
    }

    inline ~BlockUserData() {
        delete stack;
        TokenList::removeLine(token_begin, token_end);
    }

    // maybe better to remove full tokens sequence in another thread instead of use sync and etc ???
    inline TokenCell * lineControlToken() {
        token_end -> prev -> next = 0; // detach end line
        return token_begin;
    }

    inline ParaCell * lineControlPara() {
        para_end -> prev -> next = 0; // detach end line
        return para_begin;
    }

    inline void syncLine(TokenCell * sync_token, ParaCell * sync_para, ParaCell * control_sync_para, Stack<Lexem> * stack_state) {
        delete stack;
        stack = stack_state;

        //////// SYNC CONTROL PARA /////////

        para_control = control_sync_para;

        if (control_sync_para) {
            if (!foldingState())
                setFoldingState(udf_folding_opened);
        }
        else {
            //TODO: need to expand folding on repaint if flag eql to the udf_folding_dropped and
            //replace it with udf_none after that
            setFoldingState((foldingState() == udf_has_folding) ? udf_none : udf_folding_dropped);
        }

        //////// SYNC TOKENS /////////////
        TokenCell * sync = sync_token -> next;

        if (sync) {
            while(sync -> next) {
                sync = sync -> next;
                delete sync -> prev;
            }

            delete sync;
        }

        token_end -> prev = sync_token;
        token_end -> prev -> next = token_end;


        /////// SYNC PARA //////////
        ParaCell * psync = sync_para -> next;

        if (psync) {
            while(psync -> next) {
                psync = psync -> next;
                delete psync -> prev;
            }

            delete psync;
        }

        para_end -> prev = sync_para;
        para_end -> prev -> next = para_end;
    }

    inline Stack<Lexem> * stackState() { return stack; }

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
