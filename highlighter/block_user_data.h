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

    Stack<StateLexem> * stack;

    QList<MsgInfo> msgs;

    BlockUserData(TokenList * tokens, ParaList * paras, TokenCell * token_prev = nullptr, ParaCell * para_prev = nullptr, const UserDataFlags & data_flags = udf_none);

    ~BlockUserData();

    // maybe better to remove full tokens sequence in another thread instead of use sync and etc ???
    TokenCell * lineControlToken();

    ParaCell * lineControlPara();

    void syncLine(TokenCell * sync_token, ParaCell * sync_para, ParaCell * control_sync_para, Stack<StateLexem> * stack_state);

    Stack<StateLexem> * stackState();

    DATA_FLAGS_TYPE foldingState();
    bool hasBreakpoint();

    void setFoldingState(const UserDataFlags & new_state);

    void invertFoldingState();
};

#endif // BLOCK_USER_DATA_H
