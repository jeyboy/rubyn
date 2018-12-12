#ifndef EDITOR_SEARCH_FLAGS_H
#define EDITOR_SEARCH_FLAGS_H

enum EditorSearchFlags : int {
    esf_none = 0,
    esf_regex = 1,
    esf_match_case = 2,
    esf_words_only = 4,
    esf_unicode = 8
};

#endif // EDITOR_SEARCH_FLAGS_H
