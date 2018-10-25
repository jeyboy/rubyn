#include "code_editor_cache.h"

CodeEditorCache::CodeEditorCache() : root(nullptr), last(nullptr) {
    root = new CodeEditorCacheCell();
    last = new CodeEditorCacheCell(root);
}

CodeEditorCache::~CodeEditorCache() {
    clear();

    delete root;
    delete last;
}

void CodeEditorCache::clear() {
    CodeEditorCacheCell * curr;

    while(last -> prev != root) {
        curr = last;
        last = last -> prev;
        delete curr;
    }
}
