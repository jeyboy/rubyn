#ifndef CUSTOM_EDITOR_SEARCHER_H
#define CUSTOM_EDITOR_SEARCHER_H

#include "misc/defines.h"
#include <qregularexpression.h>

namespace Custom {
    class EditorSearcher {
        bool is_opened;
        bool is_active;
        int search_results;
        QRegularExpression search_regex;

    public:

        EditorSearcher();

        void openSearch() { is_opened = true; }

        inline bool hasResults() { return search_results > 0; }
        inline int searchResultsCount() { return search_results; }
        void beginSearch(const QRegularExpression & predicate) {
            search_results = 0;
            is_opened = true;
            search_regex = predicate;
        }
        Pair search(const QTextBlock & start_blk);
        void clearSearch() {
            search_results = 0;
            is_active = false;
        }
        void closeSearch() {
            is_opened = false;
            clearSearch();
        }

        inline PairList & searchResultsFor(const QTextBlock & blk) {
            BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);
            return searchResultsFor(udata);
        }
        inline PairList & searchResultsFor(BlockUserData * udata) {
            if (!udata || !mappings.contains(udata)) {
                qDebug() << "NO UDATA";
                return default_mappings;
            }

            return mappings[udata];
        }


        PairList * procBlockSearch(const QTextBlock & blk);

        void procSearchReplace(QTextCursor & cursor, const QString & txt, const bool & back_move);

        void procSearchMod(PairList & res, int res_index, int mod_index, const QString & txt);
    };
}

#endif // CUSTOM_EDITOR_SEARCHER_H
