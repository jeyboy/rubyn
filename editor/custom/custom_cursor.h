#ifndef CUSTOM_CURSOR_H
#define CUSTOM_CURSOR_H

#include "misc/defines.h"

namespace Custom {
    class Document;
    class IBlock;

    class Cursor {
        Document * _doc;
        IBlock * _block;
        IBlock * _select_end_block;

        qint64 _pos_in_block;
        qint64 _select_end_pos_in_block;
    public:
        Cursor(Document * doc, IBlock * block = nullptr, const qint64 & pos_in_block = 0);

        inline bool isValid() { return _doc && _block; }

        IBlock * block() { return _block; }
        qint64 posInBlock() { return _pos_in_block; }

//        void select();
    };
};

#endif // CUSTOM_CURSOR_H
