#ifndef FILE_POINT_H
#define FILE_POINT_H

#include "parts/lexer/scopes/scope_item_types.h"

class File;

struct FilePoint {
    File * file;
    int line;
    int left;
    int length;
};

#endif // FILE_POINT_H
