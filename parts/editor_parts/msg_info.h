#ifndef MSG_INFO_H
#define MSG_INFO_H

#include "misc/defines.h"

struct MsgInfo {
    LEXEM_TYPE info_type;
    EDITOR_POS_TYPE pos;
    EDITOR_LEN_TYPE length;
    QByteArray msg;
};

#endif // MSG_INFO_H
