#ifndef ACTIVE_PARA_INFO_H
#define ACTIVE_PARA_INFO_H

#include "misc/defines.h"

class ParaCell;

struct ActiveParaInfo {
    EDITOR_POS_TYPE opener_pos;
    EDITOR_POS_TYPE opener_length;

    EDITOR_POS_TYPE closer_pos;
    EDITOR_POS_TYPE closer_length;

    EDITOR_POS_TYPE start_block_num;
    EDITOR_POS_TYPE end_block_num;

    EDITOR_POS_TYPE level;

    ActiveParaInfo() { clear(); }

    inline bool isValid() { return start_block_num != NO_INFO; }

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

    void clear();

    ParaCell * findOpositePara(ParaCell *& para);
};

#endif // ACTIVE_PARA_INFO_H
