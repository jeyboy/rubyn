#ifndef CUSTOM_IBLOCK_H
#define CUSTOM_IBLOCK_H

namespace Custom {
    class Document;

    class IBlock {
        IBlock * prev;
        IBlock * next;
    public:
        IBlock(IBlock * prev_block = nullptr);
        virtual ~IBlock();

        friend class Document;
    };
}

#endif // CUSTOM_IBLOCK_H
