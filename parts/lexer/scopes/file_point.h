#ifndef FILE_POINT_H
#define FILE_POINT_H

#include <qstring.h>

#include "scope_item_types.h"
#include "parts/lexer/lexems.h"
#include "file_point.h"

class File;

#define DEF_LINE -1
#define DEF_LINE_END -2

struct LexToken {
    LexToken * next;

    Lexem lexem;
    int left;
    int length;

    LexToken(const Lexem & lexem = lex_none, const int & left = 0, const int & length = 0)
        : next(0), lexem(lexem), left(left), length(length) {}

    virtual QString error() const { return QString(); }
};

struct LexError : public LexToken {
    QString err;

    LexError(const int & left, const int & length, const QString & err)
        : LexToken(lex_error, left, length), err(err) {}

    QString error() const { return err; }
};


struct VarPoint {
    ScopeItemType stype;
    int line_start;
    int left;

    VarPoint(const ScopeItemType & stype, const int & line_start, const int & left)
        : stype(stype), line_start(line_start), left(left) {}
};

struct FilePoint : public VarPoint {
    File * file;
    int line_end;

    FilePoint(const ScopeItemType & stype, File * file, const int & line_start, const int & left, const int & line_end = DEF_LINE_END)
        : VarPoint(stype, line_start, left), file(file), line_end(line_end) {}
};

#endif // FILE_POINT_H
