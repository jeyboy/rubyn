#ifndef DEFINES_H
#define DEFINES_H

#include <qdebug.h>
#include <qobject.h>
#include <qstringbuilder.h>

#define DefaultStateLexems lex_min = -7, lex_end_line = -6, lex_end_doc = -5, lex_tab = -4, lex_tabs = -3, lex_blank = -2, lex_blanks = -1, lex_boundaries = lex_tab | lex_tabs | lex_blank | lex_blanks, lex_none = 0, lex_error, lex_warning, lex_notice, lex_undefined, lex_ignore, lex_default

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
