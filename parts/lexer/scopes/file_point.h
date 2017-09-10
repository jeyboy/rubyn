#ifndef FILE_POINT_H
#define FILE_POINT_H

#include <qstring.h>

#include "parts/lexer/lexems.h"
#include "file_point.h"

class File;

#define DEF_LINE -1
#define DEF_LINE_END -2

struct VarPoint {
    Lexem stype;
    int line_start;
    int left;

    VarPoint(const Lexem & stype, const int & line_start, const int & left)
        : stype(stype), line_start(line_start), left(left) {}
};

struct FilePoint : public VarPoint {
    File * file;
    int line_end;

    FilePoint(const Lexem & stype, File * file, const int & line_start, const int & left, const int & line_end = DEF_LINE_END)
        : VarPoint(stype, line_start, left), file(file), line_end(line_end) {}
};

#endif // FILE_POINT_H
