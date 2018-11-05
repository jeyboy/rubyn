#ifndef CODE_EDITOR_CACHE_H
#define CODE_EDITOR_CACHE_H

#include <qrect.h>
#include <qvector.h>
#include "misc/defines.h"

class BlockUserData;
class QTextLayout;

//enum CodeEditorCacheCellFlag : quint8 {
//    cecf_none = 0,
//    cecf_service = 1,
//    cecf_folding_selected = 2,
//    cecf_folding_partial_opener = 4,
//    cecf_folding_partial = 8,
//    cecf_visible = 16
//};

class CodeEditorCache;
class QTextBlock;

struct CodeEditorCacheCell {
    CodeEditorCache * parent;

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
    bool is_folding_opener;

    CodeEditorCacheCell(CodeEditorCache * parent, const int & block_number, CodeEditorCacheCell * prev_token = nullptr)
        : parent(parent), prev(prev_token), next(nullptr), block_number(block_number), user_data(nullptr), layout(nullptr), is_service(false), is_visible(true), is_folding_selected(false), is_folding_opener(false)
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

    void setUserData(BlockUserData * udata);

    void initLevels(const QTextBlock & block);
};

class CodeEditorCache {
    CodeEditorCacheCell * root, * last;
    QVector<qint16> block_offsets;

    qreal symbol_width;
    int tab_length;
    int length;

    friend struct CodeEditorCacheCell;
public:   
    int top_block_number;
    int bottom_block_number;
    int fill_bottom;
    bool partialy_filled;

    CodeEditorCache();

    ~CodeEditorCache();

    void clear();

    void setTab(const QLatin1String & tab_str, const qreal & def_symbol_width) {
        tab_length = tab_str.size();
        symbol_width = def_symbol_width;
    }

    inline int size() { return length; }
    inline int levelIndent(const int & level) { return level >= block_offsets.size() || level < 0 ? 0 : block_offsets[level]; }
    inline bool hasLevels() { return block_offsets.size() > 0; }

    inline CodeEditorCacheCell * begin() { return root -> next; }
    inline CodeEditorCacheCell * end() { return last -> prev; }

    inline CodeEditorCacheCell * append(const int & number) {
        ++length;
        return new CodeEditorCacheCell(this, number, last -> prev);
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
