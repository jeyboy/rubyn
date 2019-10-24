#include "custom_iblock.h"

using namespace Custom;

IBlock::IBlock(IBlock * prev_block) : prev(prev_block), next(nullptr) {
    if (prev) {
        if ((next = prev -> next))
            next -> prev = this;

        prev -> next = this;
    }
}

IBlock::~IBlock() {
    if (prev)
        prev -> next = next;

    if (next)
        next -> prev = prev;
}
