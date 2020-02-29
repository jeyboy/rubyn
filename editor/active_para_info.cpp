#include "active_para_info.h"

#include <qdebug.h>

#include "misc/para_list.h"

void ActiveParaInfo::clear() {
    if (!isValid()) return;

    level = NO_INFO;
    opener_pos = NO_INFO;
    opener_length = 0;
    closer_pos = NO_INFO;
    closer_length = 0;
    start_block_num = NO_INFO;
    end_block_num = NO_INFO;
    middles.clear();
}

ParaCell * ActiveParaInfo::findOpositePara(ParaCell *& para) {
    ParaCell * stoper = nullptr;

    if (para -> is_opener) {
        stoper = para -> next;

        while(stoper) {
            if (stoper -> is_opener) {
                if (stoper -> closer)
                    stoper = stoper -> closer;
            } else {
                if (!stoper -> closer && stoper -> pos != -1 && stoper -> is_blockator == para -> is_blockator)
                    break;
            }

            stoper = stoper -> next;
        }

        if (!stoper) {
            qDebug() << "NEED PARA EXTRA CHECK";
        }
    } else {
        stoper = para -> prev;

        while(stoper) {
            if (!stoper -> is_opener) {
                if (stoper -> closer)
                    stoper = stoper -> closer;
            } else {
                if (!stoper -> closer && stoper -> pos != -1 && stoper -> is_blockator == para -> is_blockator)
                    break;
            }

            stoper = stoper -> prev;
        }

        if (!stoper) {
            qDebug() << "NEED PARA EXTRA CHECK";
        }
    }

    if (stoper) {
        para -> closer = stoper;
        stoper -> closer = para;
    }

    return stoper;
}
