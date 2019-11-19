#include "custom_editor_searcher.h"

using namespace Custom;

EditorSearcher::EditorSearcher() : is_opened(false), is_active(false), search_results(0) {

}


//TextPart EditorSearcher::search(const QTextBlock & start_blk) {
//    TextPart first_match(NO_INFO, NO_INFO);
//    is_opened = is_active = true;
//    bool has_mapping = false;

//    mappings.clear();

//    QTextBlock blk(start_blk);
//    EDITOR_POS_TYPE blk_num = blk.blockNumber();

//    while(blk.isValid()) {
//        PairList * mappings = procBlockSearch(blk);

//        if (!has_mapping && mappings) {
//            first_match = Pair(mappings -> first());
//            first_match.first += blk.position();
//            has_mapping = true;
//        }

//        ++blk_num; blk = blk.next();
//    }

//    return first_match;
//}

//TextParts * EditorSearcher::procBlockSearch(const QTextBlock & blk) {
//    if (is_active) {
//        BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);

//        if (udata && !mappings.contains(udata)) {
//            TextParts row_mappings;

//            QString txt = blk.text();
//            QRegularExpressionMatchIterator i = search_regex.globalMatch(txt);

//            while (i.hasNext()) {
//                QRegularExpressionMatch match = i.next();

//                row_mappings.append(Pair(match.capturedStart(), match.capturedLength()));
//                search_results++;
//            }

//            if (!row_mappings.isEmpty()) {
//                mappings[udata] = row_mappings;
//                return &mappings[udata];
//            }
//        }
//    }

//    return nullptr;
//}

//void EditorSearcher::procSearchReplace(QTextCursor & cursor, const QString & txt, const bool & back_move) {
//    QTextBlock block = cursor.block();

//    TextParts & mappings = searchResultsFor(block);

//    int diff = 0;
//    int res_index = 0;
//    int mod_index = cursor.selectionStart();
//    EDITOR_POS_TYPE block_pos = block.position();


//    QMutableListIterator<TextPart> it(mappings);
//    while (it.hasNext()) {
//        TextPart & pair = it.next();

//        if ((mod_index - block_pos) == pair.first) {
//            diff = txt.length() - (cursor.selectionEnd() - mod_index);

//            --search_results;
//            it.remove();
//        }
//        else if (diff != 0) {
//            pair.first += diff;
//        }
//        else ++res_index;
//    }

//    cursor.insertText(txt);

//    if (back_move)
//        cursor.setPosition(mod_index);

//    procSearchMod(mappings, res_index, mod_index - block_pos, txt);
//}

//void EditorSearcher::procSearchMod(TextParts & res, int res_index, int mod_index, const QString & txt) {
//    QRegularExpressionMatchIterator i = search_regex.globalMatch(txt);

//    while (i.hasNext()) {
//        QRegularExpressionMatch match = i.next();

//        ++search_results;
//        res.insert(res_index, Pair(mod_index + match.capturedStart(), match.capturedLength()));
//    }
//}

