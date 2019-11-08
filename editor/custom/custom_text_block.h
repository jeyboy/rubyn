#ifndef CUSTOM_TEXT_BLOCK_H
#define CUSTOM_TEXT_BLOCK_H

#include "custom_iblock.h"
#include <qstring.h>


#include <qpen.h>
#include <qrandom.h>

namespace Custom {
    class Editor;

    class TextBlock : public IBlock {
        QString content;
        QList<QPen *> pens;
        QRandomGenerator ra;
    public:
        TextBlock(const QString & txt, IBlock * prev_block = nullptr);
//        virtual ~TextBlock() = default;

        BlockType blockType() { return bt_text; }
        void draw(DrawContext * context);

        friend class Editor;
    };
}

#endif // CUSTOM_TEXT_BLOCK_H
