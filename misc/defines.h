#ifndef DEFINES_H
#define DEFINES_H

#include <qdebug.h>
#include <qobject.h>
#include <qstringbuilder.h>

#define DefaultStateLexems lex_min = -12, lex_undefined = -11, lex_end_line = -10, lex_end_doc = -9, lex_tab = -8, lex_tabs = -7, lex_blank = -6, lex_blanks = -5, lex_ignore = -4, lex_default = -3, lex_notice = -2, lex_warning = -1, lex_error = 0, lex_none = 1

#define NO_INFO -1

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
