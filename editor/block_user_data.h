#ifndef BLOCK_USER_DATA_H
#define BLOCK_USER_DATA_H

#include <QTextBlockUserData>

#include "highlighter/para_list.h"
#include "highlighter/msg_info.h"

#include "misc/token_list.h"
//#include "misc/stack.h"

#define DEFAULT_LEVEL 0

struct BlockUserData : public QTextBlockUserData {
    enum UserDataFlags : DATA_FLAGS_TYPE {
        udf_none = 0,
        udf_folded = 1,
        udf_unfolded = 2, // used for choosing of icon
        udf_folding_hovered = 4, // used for choosing of icon
        udf_has_breakpoint = 16,
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

    bool inPartialBlock();

    TokenCell * tokenForPos(const EDITOR_POS_TYPE & pos);
    ParaCell * paraForPos(const EDITOR_POS_TYPE & pos);

    // maybe better to remove full tokens sequence in another thread instead of use sync and etc ???
    TokenCell * lineControlToken();
    ParaCell * lineControlPara();

    void syncLine(TokenCell * stack_sync_token, TokenCell * sync_token, ParaCell * sync_para, ParaCell * control_sync_para);

    inline DATA_FLAGS_TYPE foldingState() {
        DATA_FLAGS_TYPE res = flags & udf_folded;
        return res > udf_none ? res : (hasFolding() ? udf_unfolded : udf_none);
    }
    inline bool hasFolding() { return para_control && para_control -> is_opener; }
    inline bool isFolded() { return hasFolding() && (flags & udf_folded) == udf_folded; }
    inline void setFolded(const bool & on) { setFlag(udf_folded, on); }
    inline void invertFoldingState() { setFolded(!isFolded()); }

    inline bool hasBreakpoint() { return flags & udf_has_breakpoint; }
    inline void setBreakpoint(const bool & on) { setFlag(udf_has_breakpoint, on); }
    inline void invertBreakpointState() { setBreakpoint(!hasBreakpoint()); }

    void removeTokenSequence(TokenCell * tkn);
    void removeParaSequence(ParaCell * tkn);

    inline int levelForNextBlock() {
        return level + (para_control && para_control -> is_opener && !para_control -> is_oneliner ? 1 : 0);
    }

    void setFlag(const UserDataFlags & flag, const bool & on);
};

#endif // BLOCK_USER_DATA_H
