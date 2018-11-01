#ifndef ACTIVE_PARA_INFO_H
#define ACTIVE_PARA_INFO_H

#include "misc/defines.h"

#define NO_INFO -1

struct ActiveParaInfo {
    EDITOR_POS_TYPE opener_pos;
    EDITOR_POS_TYPE opener_length;

    EDITOR_POS_TYPE closer_pos;
    EDITOR_POS_TYPE closer_length;

    EDITOR_POS_TYPE start_block_num;
    EDITOR_POS_TYPE end_block_num;

    ActiveParaInfo() { clear(); }

    inline void setOpener(const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length = 0) {
        opener_pos = pos;
        opener_length = length;
    }

    inline void setCloser(const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length = 0) {
        closer_pos = pos;
        closer_length = length;
    }

    inline bool containsBlockNumber(const EDITOR_POS_TYPE & block_num) {
        return start_block_num > NO_INFO && block_num >= start_block_num && block_num <= end_block_num;
    }

    void clear() {
        opener_pos = NO_INFO;
        opener_length = 0;
        closer_pos = NO_INFO;
        closer_length = 0;
        start_block_num = NO_INFO;
        end_block_num = NO_INFO;
    }
};

#endif // ACTIVE_PARA_INFO_H
