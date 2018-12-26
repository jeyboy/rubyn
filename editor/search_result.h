#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include "misc/defines.h"

struct SearchResult {
    uint revision;
    PairList mappings;

    SearchResult(const uint & new_revision) : revision(new_revision) {

    }
};

#endif // SEARCH_RESULT_H
