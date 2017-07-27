#ifndef FILE_POINT_H
#define FILE_POINT_H

#include "parts/lexer/scopes/scope_types.h"

class File;

struct FilePoint {
    File * file;
    int line;
    int left;
    ScopeType sc_type;
};

#endif // FILE_POINT_H
