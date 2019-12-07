#ifndef CUSTOM_CURSOR_H
#define CUSTOM_CURSOR_H

#include "misc/defines.h"

namespace Custom {
    class Document;
    class IBlock;

    class Cursor {
        Document * _doc;
        IBlock * _block;

        qint64 _pos_in_block;
    public:
        Cursor(Document * doc, IBlock * block = nullptr, const qint64 & pos_in_block = 0);

//        void select();
    };
};

#endif // CUSTOM_CURSOR_H
