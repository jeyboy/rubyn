#include "code_editor_searcher.h"

PairList CodeEditorSearcher::default_mappings;

CodeEditorSearcher::CodeEditorSearcher() : is_opened(false), is_active(false), search_results(0) {

}

int CodeEditorSearcher::search(const QTextBlock & start_blk) {
    is_opened = is_active = true;
    mappings.clear();

    QTextBlock blk(start_blk);
    EDITOR_POS_TYPE blk_num = blk.blockNumber();

    while(blk.isValid()) {
        procBlockSearch(blk);
        ++blk_num; blk = blk.next();
    }

    return search_results;
}

void CodeEditorSearcher::procBlockSearch(const QTextBlock & blk) {
    if (is_active) {
        BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);

        if (udata && !mappings.contains(udata)) {
            PairList row_mappings;

            QString txt = blk.text();
            QRegularExpressionMatchIterator i = search_regex.globalMatch(txt);

            while (i.hasNext()) {
                QRegularExpressionMatch match = i.next();

                row_mappings.append(Pair(match.capturedStart(), match.capturedLength()));
                search_results++;
            }

            if (!row_mappings.isEmpty())
                mappings[udata] = row_mappings;
        }
    }
}

void CodeEditorSearcher::procSearchReplace(QTextCursor & cursor, const QString & txt, const bool & back_move) {
    //TODO: calc count of removed lines after replace and correct search hash
    QTextBlock block = cursor.block();

    PairList & mappings = searchResultsFor(block);

    int diff = 0;
    int res_index = 0;
    int mod_index = cursor.selectionStart();

    QMutableListIterator<Pair> it(mappings);
    while (it.hasNext()) {
        Pair & pair = it.next();

        if ((cursor.selectionStart() - block.position()) == pair.first) {
            diff = txt.length() - (cursor.selectionEnd() - mod_index);

            it.remove();
        }
        else if (diff != 0) {
            pair.first += diff;
        }
        else ++res_index;
    }

    cursor.insertText(txt);

    if (back_move)
        cursor.setPosition(mod_index);

    procSearchMod(mappings, res_index, mod_index - block.position(), txt);
}

void CodeEditorSearcher::procSearchMod(PairList & res, int res_index, int mod_index, const QString & txt) {
    QRegularExpressionMatchIterator i = search_regex.globalMatch(txt);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();

        res.insert(res_index, Pair(mod_index + match.capturedStart(), match.capturedLength()));
    }
}
