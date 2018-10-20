#include "block_user_data.h"

BlockUserData::BlockUserData(TokenList * tokens, ParaList * paras, TokenCell * token_prev, ParaCell * para_prev, const UserDataFlags & data_flags)
    : flags(data_flags), stack_token(nullptr), token_begin(nullptr), token_end(nullptr), para_begin(nullptr), para_end(nullptr), para_control(nullptr), level(0)
{
    tokens -> registerLine(token_begin, token_end, token_prev);
    paras -> registerLine(para_begin, para_end, para_prev);
}

BlockUserData::~BlockUserData() {
    TokenList::removeLine(token_begin, token_end);
    ParaList::removeLine(para_begin, para_end);
}

TokenCell * BlockUserData::tokenForPos(const EDITOR_POS_TYPE & pos) {
    TokenCell * it = token_end -> prev;
    EDITOR_POS_TYPE length = it -> start_pos + it -> length;

    if (length - pos < length / 2) {
        TokenCell * stop_it = token_begin;

        while(it != stop_it) {
            if (pos > it -> start_pos)
                return it;

            it = it -> prev;
        }
    } else {
        it = token_begin -> next;

        while(it != token_end) {
            if (pos <= it -> start_pos)
                return it -> prev;

            it = it -> next;
        }
    }

    return nullptr;
}

// maybe better to remove full tokens sequence in another thread instead of use sync and etc ???
TokenCell * BlockUserData::lineControlToken() {
    msgs.clear();

    token_end -> prev -> next = nullptr; // detach end line
    return token_begin;
}

ParaCell * BlockUserData::lineControlPara() {
    para_end -> prev -> next = nullptr; // detach end line
    return para_begin;
}

void BlockUserData::syncLine(TokenCell * stack_sync_token, TokenCell * sync_token, ParaCell * sync_para, ParaCell * control_sync_para) {
    stack_token = stack_sync_token;
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

DATA_FLAGS_TYPE BlockUserData::foldingState() { return flags & udf_folding_flags; }
void BlockUserData::setFoldingState(const UserDataFlags & new_state) {
    flags = static_cast<UserDataFlags>((flags & (~(udf_folding_flags))) | (new_state & udf_folding_flags));
}
void BlockUserData::invertFoldingState() {
    if (flags & udf_folding_flags) {
        setFoldingState(
            ((flags & udf_folding_opened) == udf_folding_opened) ?
                udf_has_folding : udf_folding_opened
        );
    }
}

bool BlockUserData::hasBreakpoint() { return flags & udf_has_breakpoint; }
void BlockUserData::setBreakpoint(const bool & set) { // not tested
    bool has_flag = flags & udf_has_breakpoint;

    if ((has_flag && set) || (!has_flag && !set))
        return;

    if (set) {
        flags = static_cast<UserDataFlags>(flags | udf_has_breakpoint);
    } else {
        flags = static_cast<UserDataFlags>(flags - udf_has_breakpoint);
    }
}
void BlockUserData::invertBreakpointState() { setBreakpoint(!hasBreakpoint()); }
