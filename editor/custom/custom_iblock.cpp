#include "custom_iblock.h"

using namespace Custom;

IBlock::IBlock(IBlock * prev_block) : _prev(prev_block), _next(nullptr) {
    if (_prev) {
        if ((_next = _prev -> _next))
            _next -> _prev = this;

        _prev -> _next = this;
    }
}

IBlock::~IBlock() {
    if (_prev)
        _prev -> _next = _next;

    if (_next)
        _next -> _prev = _prev;
}

int IBlock::blockNumber() {
    int n = 0;
    IBlock * it = this;


    while(it) {
        it = it -> prev();
        ++n;
    }

    return n;
}
