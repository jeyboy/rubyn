#ifndef CODE_EDITOR_CACHE_H
#define CODE_EDITOR_CACHE_H

#include <qrect.h>

class BlockUserData;

struct CodeEditorCacheCell {
    CodeEditorCacheCell * prev;
    CodeEditorCacheCell * next;

    int block_number;
    int offset;

    BlockUserData * user_data;

    QRectF screen_bounding_rect;

    bool is_service;
    bool is_visible;

    CodeEditorCacheCell(const int & block_number, const int & offset, CodeEditorCacheCell * prev_token = nullptr)
        : prev(prev_token), next(nullptr), block_number(block_number), offset(offset), user_data(nullptr), is_service(false), is_visible(true)
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
public:
    CodeEditorCache();

    ~CodeEditorCache();

    void clear();

    inline CodeEditorCacheCell * append(const int & number, const int & offset) {
        return new CodeEditorCacheCell(number, offset, last -> prev);
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
