#ifndef MSG_INFO_H
#define MSG_INFO_H

#include <qobject.h>

struct MsgInfo {
    quint32 info_type;
    quint64 pos;
    quint32 length;
    QByteArray msg;
};

#endif // MSG_INFO_H
