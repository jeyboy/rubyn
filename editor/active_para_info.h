#ifndef ACTIVE_PARA_INFO_H
#define ACTIVE_PARA_INFO_H

#include "misc/defines.h"
#include <qhash.h>

class ParaCell;

struct JPos {
    EDITOR_POS_TYPE block_num;
    EDITOR_POS_TYPE pos;
    EDITOR_POS_TYPE length;

    JPos(const EDITOR_POS_TYPE & block_num = NO_INFO, const EDITOR_POS_TYPE & pos = NO_INFO, const EDITOR_POS_TYPE & length = NO_INFO)
        : block_num(block_num), pos(pos), length(length) { }
};

struct ActiveParaInfo {
    EDITOR_POS_TYPE opener_pos;
    EDITOR_POS_TYPE opener_length;

    EDITOR_POS_TYPE closer_pos;
    EDITOR_POS_TYPE closer_length;

    EDITOR_POS_TYPE start_block_num;
    EDITOR_POS_TYPE end_block_num;

    EDITOR_POS_TYPE level;

    QList<JPos> middles;
    bool update_requires;

    ActiveParaInfo() : update_requires(false) { clear(); }

    inline bool isValid() { return start_block_num != NO_INFO; }

    inline void setOpener(const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length = 0) {
        opener_pos = pos;
        opener_length = length;
    }

    inline void setCloser(const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length = 0) {
        closer_pos = pos;
        closer_length = length;
    }

    inline void addMiddle(const EDITOR_POS_TYPE & block_num, const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length) {
       middles.append(JPos(block_num, pos, length));
    }

    inline bool containsBlockNumber(const EDITOR_POS_TYPE & block_num) {
        return start_block_num > NO_INFO && block_num >= start_block_num && block_num <= end_block_num;
    }

    void clear();

    ParaCell * findOpositePara(ParaCell *& para);
};

#endif // ACTIVE_PARA_INFO_H
