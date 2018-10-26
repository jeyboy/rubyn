#include "text_document_layout.h"

#include "controls/logger.h"

TextDocumentLayout::TextDocumentLayout(QTextDocument * document) : QPlainTextDocumentLayout(document) {}

bool TextDocumentLayout::toggleFolding(const QTextBlock & blk) {
    QTextBlock block = blk;
    BlockUserData * user_data = getUserDataForBlock(block);
    bool has_folding = user_data && user_data -> hasFolding();

    if (has_folding) {
        user_data -> invertFoldingState();

        bool unfolding = !user_data -> folded();
        int level = user_data -> level;
        bool level_blockator = user_data -> para_control -> is_blockator;
        bool sublevel_blockator = false;
        int sub_level = INT32_MAX;

        while(true) {
            block = block.next();

            user_data = getUserDataForBlock(block);

            if (!user_data || user_data -> level < level || (user_data -> level == level && !level_blockator))
                break;

            if (user_data -> level == sub_level) {
                if (sublevel_blockator)
                    sublevel_blockator = false;
                else
                    sub_level = INT32_MAX;
            }

            if (!unfolding || user_data -> level < sub_level) {
                block.setVisible(unfolding);
                block.setLineCount(unfolding ? qMax(1, block.layout() -> lineCount()) : 0);

                if (unfolding && user_data -> folded()) {
                    sublevel_blockator = user_data -> para_control -> is_blockator;
                    sub_level = user_data -> level;
                }
            }

            if (user_data -> level == level)
                break;
        }

        ///// TODO: this implementation is a bit slow for huge blocks - need to rewrite _q_adjustScrollbars in CodeEditor and use it
        emitDocumentSizeChanged();
        ////////////////////////////////////////////////////////////
        requestUpdate();

        return true;
    }

    return false;
}

//bool TextDocumentLayout::reverseToggleFolding(const QTextBlock & blocker_blk, const bool & emit_update) {
//    int blocker_level = getBlockLevel(blocker_blk);
//    QTextBlock block = blocker_blk.previous();

//    int max_level = getBlockLevel(blocker_blk);
//    bool can_groun = max_level - blocker_level == 0;
//    max_level += (can_groun ? 1 : 0);

//    bool unfolding = !block.isVisible();

//    while(block.isValid()) {
//        int blk_level = getBlockLevel(block);

//        if (blk_level <= blocker_level) {
//            BlockUserData * user_data = getUserDataForBlock(block);

//            if (user_data -> folded()) {
//                user_data -> invertFoldingState();
//                break;
//            }
//        }

//        if (blk_level <= max_level) {
//            block.setVisible(unfolding);
//            block.setLineCount(unfolding ? qMax(1, block.layout() -> lineCount()) : 0);

//            if (blk_level == max_level) {
//                BlockUserData * user_data = getUserDataForBlock(block);

//                if (user_data -> hasFolding())
//                    ++max_level;
//            }
//        }

//        block = block.previous();
//    }

//    if (emit_update) {
//        ///// TODO: this implementation is a bit slow for huge blocks - need to rewrite _q_adjustScrollbars in CodeEditor and use it
//        emitDocumentSizeChanged();
//        ////////////////////////////////////////////////////////////
//        requestUpdate();
//    }

//     return true;
//}

//bool TextDocumentLayout::toggleFolding2(const QTextBlock & blk) { //TODO: need to use line indent like mark of folding - right now unfold called from highlighter is not worked
//    BlockUserData * user_data = getUserDataForBlock(blk);
//    DATA_FLAGS_TYPE folding_flags = user_data && user_data -> para_control ? user_data -> foldingState() : 0;

//    if (folding_flags) {
//        Logger::obj().startMark();

//        user_data -> invertFoldingState();

//        //TODO: need to check performance for bottom to top proc of blocks: possible what performance is broken by layout proceses
//        //TODO: refactor needed

//        bool status = (folding_flags & BlockUserData::udf_folding_opened) != BlockUserData::udf_folding_opened;
//        EDITOR_POS_TYPE lines_coverage = user_data -> para_control -> linesCoverage();
//        EDITOR_POS_TYPE sublines_coverage = 0;

//        while(--lines_coverage >= 0) {
//            blk = blk.next();

////                                    if (!blk.isValid())
////                                        break;

//            if (sublines_coverage == 0) {
//                blk.setVisible(status);
//                blk.setLineCount(status ? qMax(1, blk.layout() -> lineCount()) : 0);

//                if (status) {
//                    user_data = getUserDataForBlock(blk);
//                    folding_flags = user_data && user_data -> para_control ? user_data -> foldingState() : 0;

//                    if (folding_flags) {
//                        bool substatus = (folding_flags & BlockUserData::udf_folding_opened) == BlockUserData::udf_folding_opened;

//                        if (substatus != status) {
//                            sublines_coverage = user_data -> para_control -> linesCoverage();
//                        }
//                    }
//                }
//            }
//            else --sublines_coverage;
//        }
//        Logger::obj().endMark("toggleFolding");

//        ///// TODO: this implementation is a bit slow for huge blocks - need to rewrite _q_adjustScrollbars in CodeEditor and use it
//        emitDocumentSizeChanged();
//        ////////////////////////////////////////////////////////////
//        requestUpdate();

//        return true;
//    }

//    return false;
//}
