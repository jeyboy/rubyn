#ifndef CUSTOM_EDITOR_SEARCHER_H
#define CUSTOM_EDITOR_SEARCHER_H

#include "misc/defines.h"
#include <qregularexpression.h>

namespace Custom {
    class IBlock;

    struct EditorSearcherResult {
        IBlock * block;
        TextPart text_part;

        EditorSearcherResult(IBlock * block = nullptr, const TextPart & text_part = {NO_INFO, NO_INFO}) : block(block), text_part(text_part) {}

        bool isValid() { return !!block; }
    };

    class EditorSearcher {
        static TextParts default_mappings;

        bool is_opened;
        bool is_active;
        int search_results;
        QRegularExpression search_regex;

        QHash<IBlock *, TextParts> mappings;
    public:
        EditorSearcher();

        void openSearch() { is_opened = true; }

        inline bool isOpened() { return is_opened; }
        inline bool isActive() { return is_active; }
        inline int foundResultsAmount() { return search_results; }

        inline bool hasResults() { return search_results > 0; }
        inline int searchResultsCount() { return search_results; }
        void beginSearch(const QRegularExpression & predicate) {
            search_results = 0;
            is_opened = true;
            search_regex = predicate;
        }
        EditorSearcherResult search(IBlock * start_blk);
        void clearSearch() {
            search_results = 0;
            is_active = false;
        }
        void closeSearch() {
            is_opened = false;
            clearSearch();
        }

        inline TextParts & searchResultsFor(IBlock * blk) {
            if (!blk || !mappings.contains(blk)) {
                qDebug() << "NO UDATA";
                return default_mappings;
            }

            return mappings[blk];
        }


        TextParts * procBlockSearch(IBlock * blk);

//        void procSearchReplace(QTextCursor & cursor, const QString & txt, const bool & back_move);

//        void procSearchMod(TextParts & res, int res_index, int mod_index, const QString & txt);
    };
}

#endif // CUSTOM_EDITOR_SEARCHER_H
