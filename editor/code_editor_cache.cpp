#include "code_editor_cache.h"

CodeEditorCache::CodeEditorCache() : root(nullptr), last(nullptr), top_block_number(-1), bottom_block_number(-1) {
    root = new CodeEditorCacheCell(-1);
    root -> is_service = true;
    last = new CodeEditorCacheCell(-1, root);
    last -> is_service = true;
}

CodeEditorCache::~CodeEditorCache() {
    clear();

    delete root;
    delete last;
}

void CodeEditorCache::clear() {
    CodeEditorCacheCell * curr;
    CodeEditorCacheCell * it = last -> prev;

    while(it != root) {
        curr = it;
        it = it -> prev;
        delete curr;
    }

    if (root -> next != last) {
        last -> prev = root;
        root -> next = last;
    }

    length = 0;
}
