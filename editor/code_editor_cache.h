#ifndef CODE_EDITOR_CACHE_H
#define CODE_EDITOR_CACHE_H

#include <qrect.h>
#include "misc/defines.h"

class BlockUserData;
class QTextLayout;

struct CodeEditorCacheCell {
    CodeEditorCacheCell * prev;
    CodeEditorCacheCell * next;

    int block_number;
    EDITOR_POS_TYPE block_pos;
    EDITOR_POS_TYPE block_length;

    BlockUserData * user_data;
    QTextLayout * layout;

    QRectF bounding_rect;
    QString folding_overlay_text;

    bool is_service;
    bool is_visible;
    bool is_folding_selected;

    CodeEditorCacheCell(const int & block_number, CodeEditorCacheCell * prev_token = nullptr)
        : prev(prev_token), next(nullptr), block_number(block_number), user_data(nullptr), layout(nullptr), is_service(false), is_visible(true), is_folding_selected(false)
    {
        if (prev) {
            if ((next = prev -> next))
                next -> prev = this;

            prev -> next = this;
        }
    }

    ~CodeEditorCacheCell() {
//        if (prev)
//            prev -> next = next;

//        if (next)
//            next -> prev = prev;
    }
};

class CodeEditorCache {
    CodeEditorCacheCell * root, * last;

    int length;
public:
    int top_block_number;
    int bottom_block_number;
    int fill_bottom;
    bool partialy_filled;

    CodeEditorCache();

    ~CodeEditorCache();

    void clear();

    inline int size() { return length; }

    inline CodeEditorCacheCell * begin() { return root -> next; }
    inline CodeEditorCacheCell * end() { return last -> prev; }

    inline CodeEditorCacheCell * append(const int & number) {
        ++length;
        return new CodeEditorCacheCell(number, last -> prev);
    }

    CodeEditorCacheCell * cacheForBlockNumber(const int & number) {
        CodeEditorCacheCell * it = root -> next;

        if (root -> next == last || number < root -> next -> block_number || number > last -> prev -> block_number)
            return nullptr;

        while(it != last) {
            if (it -> block_number == number)
                return it;

            it = it -> next;
        }

        return nullptr;
    }

//    inline static CodeEditorCacheCell * insert(CodeEditorCacheCell * left) {
//        return new CodeEditorCacheCell(left);
//    }
};

#endif // CODE_EDITOR_CACHE_H
