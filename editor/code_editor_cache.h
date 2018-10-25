#ifndef CODE_EDITOR_CACHE_H
#define CODE_EDITOR_CACHE_H

struct CodeEditorCacheCell {
    CodeEditorCacheCell * prev;
    CodeEditorCacheCell * next;

    CodeEditorCacheCell(CodeEditorCacheCell * prev_token = nullptr) : prev(prev_token), next(nullptr) {
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

    inline CodeEditorCacheCell * append() {
        return new CodeEditorCacheCell(last -> prev);
    }

    inline static CodeEditorCacheCell * insert(CodeEditorCacheCell * left) {
        return new CodeEditorCacheCell(left);
    }
};

#endif // CODE_EDITOR_CACHE_H
