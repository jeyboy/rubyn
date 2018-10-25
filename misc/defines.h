#ifndef DEFINES_H
#define DEFINES_H

#include <qdebug.h>
#include <qobject.h>
#include <qstringbuilder.h>

#define PROJECT_FORMAT_TYPE quint8

#define PARA_TYPE quint32

#define OVERLAY_POS_TYPE quint8

#define UID_TYPE qint8
#define LEXEM_MEAN_TYPE quint16
#define LEXEM_TYPE int
#define STACK_INT_TYPE uint

#define EDITOR_POS_TYPE int
#define EDITOR_LEN_TYPE uint

#define DATA_FLAGS_TYPE quint8

////////////////////////////////

#define USTR(str) QStringLiteral(str)
#define LSTR(str) QLatin1Literal(str)
#define QSTR_TO_CHAR(str) str.toUtf8().constData()

#endif // DEFINES_H
