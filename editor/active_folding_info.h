#ifndef ACTIVE_FOLDING_INFO_H
#define ACTIVE_FOLDING_INFO_H

#include "misc/defines.h"

struct ActiveFoldingInfo {
    EDITOR_POS_TYPE level;
    EDITOR_POS_TYPE start_block_num;
    EDITOR_POS_TYPE end_block_num;

    ActiveFoldingInfo() { clear(); }

    inline bool isValid() { return start_block_num != NO_INFO; }

    void clear() {
        if (!isValid()) return;

        level = NO_INFO;
        start_block_num = NO_INFO;
        end_block_num = NO_INFO;
    }

    inline bool containsBlockNumber(const EDITOR_POS_TYPE & block_num) {
        return start_block_num > NO_INFO &&
                    block_num >= start_block_num &&
                        (end_block_num < 0 || block_num <= end_block_num);
    }
};

#endif // ACTIVE_FOLDING_INFO_H
