#include "custom_cursor.h"

#include "custom_document.h"

#include <qdebug.h>

using namespace Custom;

Cursor::Cursor(Document * doc, IBlock * block, const qint64 & pos_in_block) : _doc(doc), _block(block), _select_end_block(nullptr), _pos_in_block(pos_in_block), _select_end_pos_in_block(NO_INFO) {

}

void Cursor::toPrevChar() {
    qDebug() << "toPrevChar";

    if (_pos_in_block == 0) {
        if (!_block -> prev())
            return;

        _block = _block -> prev();
        _pos_in_block = _block -> text().length();
    } else {
        --_pos_in_block;
    }
}
void Cursor::toNextChar() {
    qDebug() << "toNextChar";

    if (_pos_in_block == _block -> text().length()) {
        if (!_block -> next())
            return;

        _block = _block -> next();
        _pos_in_block = 0;
    } else {
        ++_pos_in_block;
    }
}
void Cursor::toPrevLine() {
    qDebug() << "toPrevLine";

    if (!_block -> prev())
        return;

    _block = _block -> prev();
    int len = _block -> text().length();
    _pos_in_block = _pos_in_block <= len ? _pos_in_block : len;
}
void Cursor::toNextLine() {
    qDebug() << "toNextLine";

    if (!_block -> next())
        return;

    _block = _block -> next();
    int len = _block -> text().length();
    _pos_in_block = _pos_in_block <= len ? _pos_in_block : len;
}
