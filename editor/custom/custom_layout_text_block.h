#ifndef CUSTOM_LAYOUT_TEXT_BLOCK_H
#define CUSTOM_LAYOUT_TEXT_BLOCK_H

#include "custom_iblock.h"
#include <qtextlayout.h>

namespace Custom {
    class Editor;

    class LayoutTextBlock : public IBlock {
        QTextLayout * _content;
    public:
        LayoutTextBlock(const QByteArray/*QString*/ & txt, IBlock * prev_block = nullptr);
        ~LayoutTextBlock() { delete _content; }
        QString text() { return _content -> text(); }

        void insertChar(const int & pos, const QChar & ch);
        void appendText(const QString & text);
        void insertText(const int & pos, const QString & text);
        void removeText(const int & pos, const int & len);

        BlockType blockType() { return bt_text; }
        void draw(DrawContext * context);

        friend class Editor;
    };
}

#endif // CUSTOM_LAYOUT_TEXT_BLOCK_H
