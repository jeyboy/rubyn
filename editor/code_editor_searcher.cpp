#include "code_editor_searcher.h"

CodeEditorSearcher::CodeEditorSearcher() : in_search(false), is_opened(false) {

}


void CodeEditorSearcher::procBlockSearch(const EDITOR_POS_TYPE & block_number, const QTextBlock & blk) {
    if (in_search) {
        if (!search_mappings.contains(block_number)) {
            PairList res;

            QString txt = blk.text();
            QRegularExpressionMatchIterator i = search_regex.globalMatch(txt);

            while (i.hasNext()) {
                QRegularExpressionMatch match = i.next();

                res << Pair(match.capturedStart(), match.capturedLength());
                search_results++;
            }

            search_mappings.insert(block_number, res);
        }
    }
}

void CodeEditorSearcher::procSearchReplace(QTextCursor & cursor, const QString & txt, const bool & back_move) {
    //TODO: calc count of removed lines after replace and correct search hash
    QTextBlock block = cursor.block();

    PairList & indexes = searchResultsFor(cursor.blockNumber());

    int diff = 0;
    int res_index = 0;
    int mod_index = cursor.selectionStart();

    QMutableListIterator<Pair> it(indexes);
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

    procSearchMod(indexes, res_index, mod_index - block.position(), txt);
}

void CodeEditorSearcher::procSearchMod(PairList & res, int res_index, int mod_index, const QString & txt) {
    QRegularExpressionMatchIterator i = search_regex.globalMatch(txt);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();

        res.insert(res_index, Pair(mod_index + match.capturedStart(), match.capturedLength()));
    }
}
