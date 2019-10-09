#include "block_user_data.h"

//#include <QtConcurrent/QtConcurrent>

BlockUserData::BlockUserData(TokenList * tokens, TokenList * scopes, ParaList * paras, TokenCell * token_prev, TokenCell * scope_prev, ParaCell * para_prev, const UserDataFlags & data_flags)
    : flags(data_flags), stack_token(nullptr), token_begin(nullptr), token_end(nullptr),
      scope_token(nullptr), scope_begin(nullptr), scope_end(nullptr),
      para_control(nullptr), para_begin(nullptr), para_end(nullptr),
      level(DEFAULT_LEVEL), can_have_debug_point(true), msgs(nullptr)
{
    tokens -> registerLine(token_begin, token_end, token_prev);
    scopes -> registerLine(scope_begin, scope_end, scope_prev);
    paras -> registerLine(para_begin, para_end, para_prev);
}

BlockUserData::~BlockUserData() {
    TokenList::removeLine(token_begin, token_end);
    ParaList::removeLine(para_begin, para_end);
}

ParaCell * BlockUserData::parentPara() {
    ParaCell * it = para_begin;

    while(it) {
        if (it -> para_type != pt_max && it -> para_type != pt_none && it -> is_foldable && it -> is_opener)
            return it;

        it = it -> prev;
    }

    return nullptr;
}

TokenCell * BlockUserData::tokenForPos(const EDITOR_POS_TYPE & pos) {
    TokenCell * it = token_end -> prev;
    EDITOR_POS_TYPE length = it -> start_pos + static_cast<int>(it -> length);

    if (token_begin -> next == token_end)
        return nullptr;

    if (pos == 0)
        return token_begin -> next;

    if (length - pos < length / 2) {
        while(true) {
            if (pos > it -> start_pos)
                return it;

            if (it == token_begin)
                break;

            it = it -> prev;
        }
    } else {
        it = token_begin -> next;

        while(true) {
            if (pos <= it -> start_pos)
                return it -> prev;

            if (it == token_end)
                break;

            it = it -> next;
        }
    }

    return nullptr;
}

ParaCell * BlockUserData::paraForPos(const EDITOR_POS_TYPE & pos) {
    ParaCell * it = para_end -> prev;
    EDITOR_POS_TYPE length = it -> pos + it -> length;

    if (length - pos < length / 2) {
        while(it != para_begin) {
            if (pos >= it -> pos && pos <= it -> pos + it -> length)
                return it;

            it = it -> prev;
        }
    } else {
        it = para_begin -> next;

        while(it != para_end) {
            if (pos >= it -> pos && pos <= it -> pos + it -> length)
                return it;

            it = it -> next;
        }
    }

    return nullptr;
}

TokenCell * BlockUserData::lineControlToken() {
    if (msgs) {
        delete msgs;
        msgs = nullptr;
    }

    token_end -> prev -> next = nullptr; // detach end line
    return token_begin;
}


TokenCell * BlockUserData::lineControlScope() {
    scope_end -> prev -> next = nullptr; // detach end line

    return scope_begin;
}



ParaCell * BlockUserData::lineControlPara() {
    para_end -> prev -> next = nullptr; // detach end line

    return para_begin;
}

void BlockUserData::syncLine(TokenCell * stack_sync_token, TokenCell * sync_token, TokenCell * stack_sync_scope, TokenCell * sync_scope,  ParaCell * control_sync_para, ParaCell * sync_para) {
    stack_token = stack_sync_token;
    scope_token = stack_sync_scope;
    para_control = control_sync_para;

//    if (control_sync_para) {
//        if (!foldingState())
//            setFoldingState(udf_unfolded);
//    }


    //////// SYNC SCOPES /////////////
    removeTokenSequence(sync_scope -> next);

    scope_end -> prev = sync_scope;
    scope_end -> prev -> next = scope_end;


    //////// SYNC TOKENS /////////////
//    QtConcurrent::run(this, &BlockUserData::removeTokenSequence, sync_token -> next);
    removeTokenSequence(sync_token -> next);

    token_end -> prev = sync_token;
    token_end -> prev -> next = token_end;

    /////// SYNC PARA //////////
//    QtConcurrent::run(this, &BlockUserData::removeParaSequence, sync_para -> next);
    removeParaSequence(sync_para -> next);

    para_end -> prev = sync_para;
    para_end -> prev -> next = para_end;
}

void BlockUserData::removeTokenSequence(TokenCell * tkn) {
    if (tkn) {
        while(tkn -> next) {
            tkn = tkn -> next;
            delete tkn -> prev;
        }

        delete tkn;
    }
}
void BlockUserData::removeParaSequence(ParaCell * tkn) {
    if (tkn) {
        while(tkn -> next) {
            tkn = tkn -> next;
            delete tkn -> prev;
        }

        delete tkn;
    }
}

void BlockUserData::setFlag(const UserDataFlags & flag, const bool & on) {
    bool has_flag = flags & flag;

    if ((has_flag && on) || (!has_flag && !on))
        return;

    if (on) {
        flags = static_cast<UserDataFlags>(flags | flag);
    } else {
        flags = static_cast<UserDataFlags>(flags - flag);
    }
}

void BlockUserData::addMessage(const MsgInfo & msg) {
    if (!msgs)
        msgs = new QList<MsgInfo>();

    msgs -> append(msg);
}
