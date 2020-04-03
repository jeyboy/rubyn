#ifndef FILE_SEARCH_RESULT_H
#define FILE_SEARCH_RESULT_H

#include "misc/defines.h"

struct FileSearchResult {
    QString path;
    EDITOR_POS_TYPE match_pos;
    EDITOR_LEN_TYPE match_length;

    QString result;
    EDITOR_POS_TYPE result_pos;
};

#endif // FILE_SEARCH_RESULT_H
