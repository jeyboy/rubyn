#ifndef CUSTOM_IBLOCK_H
#define CUSTOM_IBLOCK_H

namespace Custom {
    class Document;
    class DrawContext;

    class IBlock {
        IBlock * _prev;
        IBlock * _next;
    public:
        enum BlockType {
            bt_none = 0,
            bt_text
        };

        IBlock(IBlock * prev_block = nullptr);
        virtual ~IBlock();
        virtual BlockType blockType() { return bt_none; }
        virtual void draw(DrawContext * context) = 0;

        IBlock * next() { return _next; }
        IBlock * prev() { return _prev; }

        friend class Document;
    };
}

#endif // CUSTOM_IBLOCK_H
