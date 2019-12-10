#include "custom_cursor.h"

#include "custom_document.h"

using namespace Custom;

Cursor::Cursor(Document * doc, IBlock * block, const qint64 & pos_in_block) : _doc(doc), _block(block), _select_end_block(nullptr), _pos_in_block(pos_in_block), _select_end_pos_in_block(NO_INFO), _rect(NO_INFO, NO_INFO, NO_INFO, NO_INFO) {

}

bool Cursor::isDrawn() { return _rect.left() != NO_INFO; }

bool Cursor::toPrevChar() {
    if (_pos_in_block == 0) {
        if (!_block -> prev())
            return false;

        _block = _block -> prev();
        _pos_in_block = _block -> text().length();
    } else {
        --_pos_in_block;
    }

    return true;
}
bool Cursor::toNextChar() {
    if (_pos_in_block == _block -> text().length()) {
        if (!_block -> next())
            return false;

        _block = _block -> next();
        _pos_in_block = 0;
    } else {
        ++_pos_in_block;
    }

    return true;
}
bool Cursor::toPrevLine() {
    if (!_block -> prev())
        return false;

    _block = _block -> prev();
    int len = _block -> text().length();
    _pos_in_block = _pos_in_block <= len ? _pos_in_block : len;

    return true;
}
bool Cursor::toNextLine() {
    if (!_block -> next())
        return false;

    _block = _block -> next();
    int len = _block -> text().length();
    _pos_in_block = _pos_in_block <= len ? _pos_in_block : len;

    return true;
}
