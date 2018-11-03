#include "code_editor_cache.h"

#include "editor/block_user_data.h"
#include "highlighter/para_list.h"

void CodeEditorCacheCell::setUserData(BlockUserData * udata) {
    user_data = udata;

    if (user_data && user_data -> para_control) {
        if (!user_data -> para_control -> is_opener) {
            if (is_folding_partial) {
                level_offset += 1;
                is_folding_partial = false;
            }
        } else if (!is_folding_partial && !user_data -> para_control -> is_blockator) {
            level_offset -= 1;
            is_folding_partial = true;
        }
    }
}

CodeEditorCache::CodeEditorCache() : root(nullptr), last(nullptr), length(0), top_block_number(-1), bottom_block_number(-1), partialy_filled(false) {
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
    partialy_filled = false;

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
