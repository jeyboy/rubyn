#ifndef ERROR_INFO_H
#define ERROR_INFO_H

#include <qobject.h>

struct ErrorInfo {
    quint64 pos;
    quint32 length;
    QByteArray msg;
};

#endif // ERROR_INFO_H
