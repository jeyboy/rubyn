#ifndef CUSTOM_TEXT_BLOCK_H
#define CUSTOM_TEXT_BLOCK_H

#include "custom_iblock.h"
//#include <qstring.h>
#include <qbytearray.h>

namespace Custom {
    class Editor;

    class TextBlock : public IBlock {
//        QString _content;
        QByteArray _content;
    public:
        TextBlock(const QByteArray/*QString*/ & txt, IBlock * prev_block = nullptr);
//        virtual ~TextBlock() = default;
        QString text() { return _content; }

        void insertChar(const int & pos, const QChar & ch);
        void insertText(const int & pos, const QByteArray & text);
        void removeText(const int & pos, const int & len);

        BlockType blockType() { return bt_text; }
        void draw(DrawContext * context);

        friend class Editor;
    };
}

#endif // CUSTOM_TEXT_BLOCK_H
