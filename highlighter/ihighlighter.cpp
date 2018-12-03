#include "ihighlighter.h"

IHighlighter::~IHighlighter() {}

void IHighlighter::initBlockUserData(QTextBlock & block, BlockUserData * prev_udata, BlockUserData *& udata, const int & text_len) {
    if (!udata) {
        udata = new BlockUserData(
            _tokens, _paras,
            prev_udata ? prev_udata -> token_end : nullptr,
            prev_udata ? prev_udata -> para_end : nullptr
        );
        block.setUserData(udata);
    }
    else {
        udata -> para_begin -> prev = prev_udata ? prev_udata -> para_end : _paras -> rootToken();
        udata -> token_begin -> prev = prev_udata ? prev_udata -> token_end : _tokens -> rootToken();
    }

    udata -> level = prev_udata ? prev_udata -> levelForNextBlock() : DEFAULT_LEVEL;
    udata -> token_end -> start_pos = text_len;
}
