#ifndef CODE_EDITOR_SEARCHER_H
#define CODE_EDITOR_SEARCHER_H

#include "misc/defines.h"
#include "editor/text_document_layout.h"
#include "editor/search_result.h"

#include <qregularexpression.h>
#include <QTextBlock>

struct CodeEditorSearcher {
    uint revision;
    int search_results;
    bool is_opened;
    bool is_active;
    QRegularExpression search_regex;

    CodeEditorSearcher();

    void openSearch() { is_opened = true; }

    int searchResultsCount() { return search_results; }
    void beginSearch(const QRegularExpression & predicate) {
        search_results = 0;

        if (++revision > 100000)
            revision = 0;

        is_opened = true;
        search_regex = predicate;
    }
    int search(const QTextBlock & start_blk);
    void clearSearch() {
        search_results = 0;
        is_active = false;
    }
    void closeSearch() {
        is_opened = false;
        clearSearch();
    }
    inline SearchResult * searchResultsFor(const QTextBlock & blk) { return TextDocumentLayout::getUserDataForBlock(blk) -> search; }

    void procBlockSearch(const QTextBlock & blk);

    void procSearchReplace(QTextCursor & cursor, const QString & txt, const bool & back_move);

    void procSearchMod(PairList & res, int res_index, int mod_index, const QString & txt);
};

#endif // CODE_EDITOR_SEARCHER_H
