#ifndef CUSTOM_IBLOCK_H
#define CUSTOM_IBLOCK_H

#include <qstring.h>

namespace Custom {
    class Document;
    class DrawContext;

    class IBlock {
        IBlock * _prev;
        IBlock * _next;
        bool _is_visible;
    public:
        enum BlockType {
            bt_none = 0,
            bt_text
        };

        IBlock(IBlock * prev_block = nullptr);
        virtual ~IBlock();
        virtual BlockType blockType() { return bt_none; }
        virtual void draw(DrawContext * context) = 0;

        bool isVisible() { return _is_visible; }
        void hide() { _is_visible = false; }
        void show() { _is_visible = true; }

        IBlock * next() { return _next; }
        IBlock * prev() { return _prev; }
        virtual QString text() = 0;
        virtual void insertChar(const int & pos, const QChar & ch) = 0;
        virtual void appendText(const QString & text) = 0;
        virtual void insertText(const int & pos, const QString & text) = 0;
        virtual void removeText(const int & pos, const int & len) = 0;
        int blockNumber();

        void remove();

        friend class Document;
    };
}

#endif // CUSTOM_IBLOCK_H
