#ifndef CUSTOM_IBLOCK_H
#define CUSTOM_IBLOCK_H

#include <qstring.h>

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
        virtual QString text() = 0;
        virtual void insertChar(const int & pos, const QChar & ch) = 0;
        virtual void insertText(const int & pos, const QByteArray & text) = 0;
        virtual void removeText(const int & pos, const int & len) = 0;
        int blockNumber();

        friend class Document;
    };
}

#endif // CUSTOM_IBLOCK_H
