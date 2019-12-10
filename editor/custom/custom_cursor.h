#ifndef CUSTOM_CURSOR_H
#define CUSTOM_CURSOR_H

#include <qrect.h>
#include <qdebug.h>

#include "misc/defines.h"

namespace Custom {
    class Document;
    class IBlock;

    class Cursor {
        enum MoveFlag {
            mf_none = 0,
            mf_char_move,
            mf_line_move
        };

        Document * _doc;
        IBlock * _block;
        IBlock * _select_end_block;

//        qint64 _move_pos_in_block;
        qint64 _pos_in_block;
        qint64 _select_end_pos_in_block;

        QRectF _rect;
        MoveFlag _move_state;
    public:       
        Cursor(Document * doc, IBlock * block = nullptr, const qint64 & pos_in_block = 0);

        inline bool isValid() { return _doc && _block; }

        IBlock * block() { return _block; }
        qint64 posInBlock() { return _pos_in_block; }
        QRectF rect() { return _rect; }
        void drawInRect(const QRectF & rect) {
            qDebug() << "*** drawInRect" << rect;
            _rect = rect;
        }
        bool isDrawn();

        bool toPrevChar();
        bool toNextChar();
        bool toPrevLine();
        bool toNextLine();

//        void select();
    };
};

#endif // CUSTOM_CURSOR_H
