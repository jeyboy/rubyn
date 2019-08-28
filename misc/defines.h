#ifndef DEFINES_H
#define DEFINES_H

#include <qdebug.h>
#include <qobject.h>
#include <qstringbuilder.h>

#define NO_INFO -1

#define LEX_MIN -10
#define LEX_UNDEFINED_STATE -9
#define LEX_END_LINE_STATE -8
#define LEX_END_DOC_STATE -7
#define LEX_TAB -6
#define LEX_TABS -5
#define LEX_BLANK -4
#define LEX_BLANKS -3
#define LEX_IGNORE -2
#define LEX_DEFAULT_STATE -1
#define LEX_ERROR_STATE 0
#define LEX_NONE_STATE 1

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

typedef QPair<EDITOR_POS_TYPE, EDITOR_POS_TYPE> Pair;
typedef QList<Pair> PairList;

#endif // DEFINES_H
