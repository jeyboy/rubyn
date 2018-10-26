#ifndef TEXT_DOCUMENT_LAYOUT_H
#define TEXT_DOCUMENT_LAYOUT_H

#include <QPlainTextDocumentLayout>

#include "block_user_data.h"

class TextDocumentLayout : public QPlainTextDocumentLayout {
public:
    inline static BlockUserData * getUserDataForBlock(const QTextBlock & blk) {
        return static_cast<BlockUserData *>(blk.userData());
    }

    inline static int getBlockLevel(const QTextBlock & blk) {
        BlockUserData * data = getUserDataForBlock(blk);
        return data ? data -> level : DEFAULT_LEVEL;
    }

    TextDocumentLayout(QTextDocument * document);

    bool toggleFolding(const QTextBlock & blk);

//    bool reverseToggleFolding(const QTextBlock & blocker_blk, const bool & emit_update = false);

    inline void emitDocumentSizeChanged() { emit documentSizeChanged(documentSize()); }
};

#endif // TEXT_DOCUMENT_LAYOUT_H
