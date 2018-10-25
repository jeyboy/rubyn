#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>

#include "highlighter/para_list.h"
#include "highlighter/msg_info.h"

#include "misc/token_list.h"
//#include "misc/stack.h"

#define DEFAULT_LEVEL 0

struct BlockUserData : public QTextBlockUserData {
// TODO: refactor me: udf_has_folding not needed - we have para_control for that
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

    TokenCell * stack_token;
    TokenCell * token_begin;
    TokenCell * token_end;

    ParaCell * para_begin;
    ParaCell * para_end;
    ParaCell * para_control;

    QList<MsgInfo> msgs;
    int level;

    BlockUserData(TokenList * tokens, ParaList * paras, TokenCell * token_prev = nullptr, ParaCell * para_prev = nullptr, const UserDataFlags & data_flags = udf_none);

    ~BlockUserData();

    TokenCell * tokenForPos(const EDITOR_POS_TYPE & pos);
    ParaCell * paraForPos(const EDITOR_POS_TYPE & pos);

    // maybe better to remove full tokens sequence in another thread instead of use sync and etc ???
    TokenCell * lineControlToken();
    ParaCell * lineControlPara();

    void syncLine(TokenCell * stack_sync_token, TokenCell * sync_token, ParaCell * sync_para, ParaCell * control_sync_para);

    inline bool hasFolding() { return para_control; }
    inline bool folded() { return para_control && (foldingState() & udf_folding_opened) != udf_folding_opened; }

    DATA_FLAGS_TYPE foldingState();
    void setFoldingState(const UserDataFlags & new_state);
    void invertFoldingState();

    bool hasBreakpoint();
    void setBreakpoint(const bool & set);
    void invertBreakpointState();

    void removeTokenSequence(TokenCell * tkn);
    void removeParaSequence(ParaCell * tkn);

    inline int levelForNextBlock() {
        return level + (para_control && para_control -> is_opener && !para_control -> is_oneliner ? 1 : 0);
    }
};

#endif // BLOCK_USER_DATA_H
