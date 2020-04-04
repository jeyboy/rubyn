#ifndef DEFINES_H
#define DEFINES_H

#include <qdebug.h>
#include <qobject.h>
#include <qstringbuilder.h>

#define TREE_FOLDER_UID Qt::UserRole
#define TREE_LEVEL_UID Qt::UserRole + 1
#define TREE_PATH_UID Qt::UserRole + 2
#define TREE_SEARCH_MATCH_POS_UID Qt::UserRole + 10
#define TREE_SEARCH_MATCH_LEN_UID Qt::UserRole + 11
#define TREE_EXPAND_STATE_UID Qt::UserRole + 12
#define TREE_COLOR_UID Qt::UserRole + 20
#define TREE_HAS_ERROR_UID Qt::UserRole + 21

#define PROJECT_SEARCH_MATCH_POS_UID Qt::UserRole
#define PROJECT_SEARCH_MATCH_LEN_UID Qt::UserRole + 1
#define PROJECT_SEARCH_PATH_UID Qt::UserRole + 2
#define PROJECT_SEARCH_PATH_POS_UID Qt::UserRole + 3



#define LEXEM_MEAN_TYPE quint16
#define LEXEM_TYPE int

// first 16 bits registered for lexems
// 16 - 24 bits registered for level
// 24 - 32 bits registereg for scope
#define state_level_bits_offset 16 //sizeof(LEXEM_TYPE) / 2 * 8
#define state_scope_bits_offset 25 //sizeof(LEXEM_TYPE) / 4 * 3 * 8

#define DefaultStateLexems lex_min = -8, lex_end_line = -7, lex_end_doc = -6, lex_spacing = -5, lex_tab = -4, lex_tabs = -3, lex_blank = -2, lex_blanks = -1, lex_none = 0, lex_error = 1, lex_warning, lex_notice, lex_undefined, lex_ignore, lex_default, lex_reserved = 10

#define NO_INFO -1

#define PROJECT_FORMAT_TYPE quint8

#define PARA_TYPE quint32

#define DefaultParaLexems pt_max = 1 << 28, pt_close = 1 << 29, pt_foldable = 1 << 30, pt_max_end = pt_max | pt_close, pt_none = 0, pt_reserved = 128

#define SCOPE_TYPE quint32

#define DefaultScopeLexems sc_none = 0, sc_max = 1 << 30



#define OVERLAY_POS_TYPE quint8

#define UID_TYPE qint8
#define STACK_INT_TYPE uint

#define EDITOR_POS_TYPE int
#define EDITOR_LEN_TYPE uint

#define DATA_FLAGS_TYPE quint8

////////////////////////////////

#define USTR(str) QStringLiteral(str)
#define LSTR(str) QLatin1Literal(str)
#define QSTR_TO_CHAR(str) str.toUtf8().constData()

typedef QPair<EDITOR_POS_TYPE, EDITOR_POS_TYPE> TextPart;
typedef QList<TextPart> TextParts;

#endif // DEFINES_H
