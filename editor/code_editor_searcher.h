#ifndef CODE_EDITOR_SEARCHER_H
#define CODE_EDITOR_SEARCHER_H

#include "misc/defines.h"
#include "editor/text_document_layout.h"

#include <qregularexpression.h>
#include <QTextBlock>

struct CodeEditorSearcher {
    static TextParts default_mappings;

    bool is_opened;
    bool is_active;
    int search_results;
    QRegularExpression search_regex;

    QHash<BlockUserData *, TextParts> mappings;

    CodeEditorSearcher();

    void openSearch() { is_opened = true; }

    inline bool hasResults() { return search_results > 0; }
    inline int searchResultsCount() { return search_results; }
    void beginSearch(const QRegularExpression & predicate) {
        search_results = 0;
        is_opened = true;
        search_regex = predicate;
    }
    TextPart search(const QTextBlock & start_blk);
    void clearSearch() {
        search_results = 0;
        is_active = false;
    }
    void closeSearch() {
        is_opened = false;
        clearSearch();
    }
    inline TextParts & searchResultsFor(const QTextBlock & blk) {
        BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);
        return searchResultsFor(udata);
    }
    inline TextParts & searchResultsFor(BlockUserData * udata) {
        if (!udata || !mappings.contains(udata)) {
            qDebug() << "NO UDATA";
            return default_mappings;
        }

        return mappings[udata];
    }


    TextParts * procBlockSearch(const QTextBlock & blk);

    void procSearchReplace(QTextCursor & cursor, const QString & txt, const bool & back_move);

    void procSearchMod(TextParts & res, int res_index, int mod_index, const QString & txt);
};

#endif // CODE_EDITOR_SEARCHER_H
