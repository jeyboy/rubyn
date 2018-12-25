#ifndef CODE_EDITOR_SEARCHER_H
#define CODE_EDITOR_SEARCHER_H

#include "misc/defines.h"
#include <qregularexpression.h>
#include <QTextBlock>

typedef QPair<EDITOR_POS_TYPE, EDITOR_POS_TYPE> Pair;
typedef QList<Pair> PairList;

struct CodeEditorSearcher {
    int search_results;
    bool is_opened;
    bool in_search;
    QRegularExpression search_regex;
    QHash<EDITOR_POS_TYPE, PairList> search_mappings;

    CodeEditorSearcher();

    bool isOpened() { return is_opened; }
    void openSearch() { is_opened = true; }

    int searchResultsCount() { return search_results; }
    bool inSearch() { return in_search; }
    void beginSearch(const QRegularExpression & predicate) {
        search_results = 0;
        search_mappings.clear();
        in_search = true;
        search_regex = predicate;
    }
    int search(const QTextBlock & start_blk) {
        QTextBlock blk(start_blk);
        EDITOR_POS_TYPE blk_num = blk.blockNumber();

        while(blk.isValid()) {
            procBlockSearch(blk_num, blk);
            ++blk_num; blk = blk.next();
        }

        return search_results;
    }
    void clearSearch() {
        search_results = 0;
        search_mappings.clear();
        in_search = false;
    }
    void closeSearch() {
        is_opened = false;
        clearSearch();
    }
    inline PairList & searchResultsFor(const EDITOR_POS_TYPE & row) { return search_mappings[row]; }

    void procBlockSearch(const EDITOR_POS_TYPE & block_number, const QTextBlock & blk);

    void procSearchReplace(QTextCursor & cursor, const QString & txt, const bool & back_move);

    void procSearchMod(PairList & res, int res_index, int mod_index, const QString & txt);
};

#endif // CODE_EDITOR_SEARCHER_H
