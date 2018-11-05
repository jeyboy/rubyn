#include "code_editor_cache.h"

#include "editor/block_user_data.h"
#include "editor/text_document_layout.h"

#include "highlighter/para_list.h"

void CodeEditorCacheCell::setUserData(BlockUserData * udata) {
    user_data = udata;

    if (user_data && user_data -> para_control) {
        if (!user_data -> para_control -> is_opener) {
            if (user_data -> level > 0)
                parent -> block_offsets.resize(user_data -> level);
        } else if (!user_data -> para_control -> is_oneliner) {
            is_folding_opener = true;

            if (user_data -> level >= 0) {
                int indent_len = user_data -> indentSize();

                if (indent_len > 0) {
                    parent -> block_offsets.resize(user_data -> level + 1);
                    parent -> block_offsets[user_data -> level] = indent_len * parent -> symbol_width;
                }
            }
        }
    }
}

void CodeEditorCacheCell::initLevels(const QTextBlock & block) {
    user_data = TextDocumentLayout::getUserDataForBlock(block);

    ParaCell * it = user_data ? user_data -> parentPara() : nullptr;

    if (it) {
        if (user_data -> level > 0) {
            int curr_level = user_data -> level;
            parent -> block_offsets.fill(0, curr_level + 1);
            QTextBlock blk = block.previous();

            while(blk.isValid()) {
                BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);

                if (udata -> level < curr_level) {
                    curr_level = udata -> level;
                    parent -> block_offsets[curr_level] = udata -> indentSize() * parent -> symbol_width;

                    if (curr_level <= 0)
                        break;
                }

                blk = blk.previous();
            }
        }
    }
}

CodeEditorCache::CodeEditorCache() : root(nullptr), last(nullptr), length(0), top_block_number(NO_INFO), bottom_block_number(NO_INFO), partialy_filled(false) {
    block_offsets.reserve(10);

    root = new CodeEditorCacheCell(this, NO_INFO);
    root -> is_service = true;
    last = new CodeEditorCacheCell(this, NO_INFO, root);
    last -> is_service = true;
}

CodeEditorCache::~CodeEditorCache() {
    clear();

    delete root;
    delete last;
}

void CodeEditorCache::clear() {
    block_offsets.clear();
    partialy_filled = false;

    top_block_number = NO_INFO;
    bottom_block_number = NO_INFO;
    fill_bottom = NO_INFO;

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
