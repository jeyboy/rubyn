#include "text_document_layout.h"

#include <qdebug.h>

TextDocumentLayout::TextDocumentLayout(QTextDocument * document) : QPlainTextDocumentLayout(document) {

}

bool TextDocumentLayout::toggleFolding(QTextBlock & blk) { //TODO: need to use line indent like mark of folding - right now unfold called from highlighter is not worked
    BlockUserData * user_data = getUserDataForBlock(blk);
    DATA_FLAGS_TYPE folding_flags = user_data && user_data -> para_control ? user_data -> foldingState() : 0;

    if (folding_flags) {
        user_data -> invertFoldingState();

        //TODO: need to check performance for bottom to top proc of blocks: possible what performance is broken by layout proceses
        //TODO: refactor needed

        bool status = (folding_flags & BlockUserData::udf_folding_opened) != BlockUserData::udf_folding_opened;
        EDITOR_POS_TYPE lines_coverage = user_data -> para_control -> linesCoverage();
        EDITOR_POS_TYPE sublines_coverage = 0;

        while(--lines_coverage >= 0) {
            blk = blk.next();

//                                    if (!blk.isValid())
//                                        break;

            if (sublines_coverage == 0) {
                blk.setVisible(status);
                blk.setLineCount(status ? qMax(1, blk.layout() -> lineCount()) : 0);

                if (status) {
                    user_data = getUserDataForBlock(blk);
                    folding_flags = user_data && user_data -> para_control ? user_data -> foldingState() : 0;

                    if (folding_flags) {
                        bool substatus = (folding_flags & BlockUserData::udf_folding_opened) == BlockUserData::udf_folding_opened;

                        if (substatus != status) {
                            sublines_coverage = user_data -> para_control -> linesCoverage();
                        }
                    }
                }
            }
            else --sublines_coverage;
        }

        ///// TODO: this implementation is a bit slow for huge blocks - need to rewrite _q_adjustScrollbars in CodeEditor and use it
        emitDocumentSizeChanged();
        ////////////////////////////////////////////////////////////
        requestUpdate();

       return true;
    }

    return false;
}
