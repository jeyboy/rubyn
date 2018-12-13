#ifndef CODE_EDITOR_CACHE_H
#define CODE_EDITOR_CACHE_H

#include <qrect.h>
#include <qvector.h>
#include <qregularexpression.h>

#include "misc/defines.h"

typedef QPair<EDITOR_POS_TYPE, EDITOR_POS_TYPE> Pair;
typedef QList<Pair> PairList;

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

struct CacheScopeOffset {
    EDITOR_POS_TYPE level;
    EDITOR_POS_TYPE prev_offset;
    EDITOR_POS_TYPE start_block_number;

    CacheScopeOffset(const EDITOR_POS_TYPE & sc_level = NO_INFO, const EDITOR_POS_TYPE & offset = NO_INFO, const EDITOR_POS_TYPE & block_num = NO_INFO)
        : level(sc_level), prev_offset(offset), start_block_number(block_num) {}

    inline bool isNull() { return start_block_number == NO_INFO; }
};

struct CodeEditorCacheCell {
    CodeEditorCache * parent;

    CodeEditorCacheCell * prev;
    CodeEditorCacheCell * next;

    QVector<CacheScopeOffset> scope_offsets;

    EDITOR_POS_TYPE block_number;
    EDITOR_POS_TYPE block_pos;
    EDITOR_POS_TYPE block_length;

    BlockUserData * user_data;
    QTextLayout * layout;

    QRectF bounding_rect;
    QRectF folding_description_rect;
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
        scope_offsets.clear();

//        if (prev)
//            prev -> next = next;

//        if (next)
//            next -> prev = prev;
    }

    void setUserData(BlockUserData * udata);

    void initLevels(const QTextBlock & block);

    inline void popScopeOffset() {
        if (scope_offsets.length() > 1)
            scope_offsets.resize(scope_offsets.last().prev_offset + 1);
        else
            scope_offsets.clear();
    }

    void procSearch(const QTextBlock & blk);
};

class CodeEditorCache {
    bool in_search;
    QRegularExpression search_regex;
    QHash<EDITOR_POS_TYPE, PairList> search_mappings;

    CodeEditorCacheCell * root, * last;
    QVector<qint16> block_offsets;
//    QHash<EDITOR_POS_TYPE, > scope_offsets;

    qreal symbol_width;
    int tab_length;
    int length;

    OVERLAY_POS_TYPE show_overlays;

    friend struct CodeEditorCacheCell;
public:
    int debug_active_block_number;
    int top_block_number;
    int bottom_block_number;
    int fill_bottom;
    bool partialy_filled;

    CodeEditorCache();

    ~CodeEditorCache();

    bool inSearch() { return in_search; }
    void openSearch(const QRegularExpression & predicate) {
        search_mappings.clear();
        in_search = true;
        search_regex = predicate;
    }
    void closeSearch() {
        search_mappings.clear();
        in_search = false;
    }
    inline const PairList & searchResultsFor(const EDITOR_POS_TYPE & row) { return search_mappings[row]; }

    void mapOverlayState(const OVERLAY_POS_TYPE & overlay_pos, const bool & show) {
        if (show)
            show_overlays = show_overlays | overlay_pos;
        else
            show_overlays = show_overlays & ~overlay_pos;
    }
    void clearOverlaysState() { show_overlays = 0; }
    bool isShowOverlay() { return show_overlays; }

    void clear();
    void reset();

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

    inline bool isBlockOnScreen(const EDITOR_POS_TYPE & block_number) { return block_number >= top_block_number && block_number <= bottom_block_number; }

//    inline static CodeEditorCacheCell * insert(CodeEditorCacheCell * left) {
//        return new CodeEditorCacheCell(left);
//    }
};

#endif // CODE_EDITOR_CACHE_H
