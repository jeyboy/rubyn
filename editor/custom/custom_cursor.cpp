#include "custom_cursor.h"

#include "custom_document.h"

#include <qimage.h>
#include <qdebug.h>

using namespace Custom;

Cursor::Cursor(Document * doc, IBlock * block, const qint64 & pos_in_block) : _doc(doc), _block(block), _pos_in_block(pos_in_block),
    _rect(NO_INFO, NO_INFO, NO_INFO, NO_INFO), _move_state(mf_none) { }

void Cursor::drawInRect(const QRect & rect) {
    _rect = rect;
}

bool Cursor::isDrawn() { return _rect.left() != NO_INFO; }

bool Cursor::toOffset(const int & offset) {
    _move_state = mf_none;

    if (offset == 0) {
        return false;
    }

    int len = _block -> contentLength();

    if (offset > 0) {
        if (_pos_in_block + offset > len) {
            if (_pos_in_block != len) {
                _pos_in_block = len;
                _move_state = mf_pos_move;
            } else {
                return false;
            }
        } else {
            _pos_in_block += offset;
            _move_state = mf_pos_move;
        }
    } else {
        if (_pos_in_block - offset < 0) {
            if (_pos_in_block != 0) {
                _pos_in_block = 0;
                _move_state = mf_pos_move;
            } else {
                return false;
            }
        } else {
            _pos_in_block -= offset;
            _move_state = mf_pos_move;
        }
    }

    return true;
}

bool Cursor::toPrevChar() {
    if (_pos_in_block == 0) {
        if (!_block -> prev()) {
            _move_state = mf_none;
            return false;
        }

        _move_state = mf_line_move;
        _block = _block -> prev();
        _pos_in_block = _block -> contentLength();
    } else {
        _move_state = mf_pos_move;
        --_pos_in_block;
    }

    return true;
}
bool Cursor::toNextChar() {
    if (_pos_in_block == _block -> contentLength()) {
        if (!_block -> next()) {
            _move_state = mf_none;
            return false;
        }

        _move_state = mf_line_move;
        _block = _block -> next();
        _pos_in_block = 0;
    } else {
        _move_state = mf_pos_move;
        ++_pos_in_block;
    }

    return true;
}

bool Cursor::toLineStart() {
    if (_pos_in_block <= 0) {
        _move_state = mf_none;
        return false;
    }

    _pos_in_block = 0;
    _move_state = mf_pos_move;
    return true;
}

bool Cursor::toLineEnd() {
    qint64 txt_len = block() -> contentLength();

    if (_pos_in_block == txt_len) {
        _move_state = mf_none;
        return false;
    }

    _pos_in_block = txt_len;
    _move_state = mf_pos_move;
    return true;
}

bool Cursor::toPrevLine() {
    if (!_block -> prev() || !_block -> prev() -> prev()) {
        _move_state = mf_none;
        return false;
    }

    _move_state = mf_line_move;
    _block = _block -> prev();
    int len = _block -> contentLength();

    if (_pos_in_block >= len) {
        _move_state = MoveFlag(_move_state | mf_pos_move);
        _pos_in_block = len;
    }

    return true;
}
bool Cursor::toNextLine() {
    if (!_block -> next()) {
        _move_state = mf_none;
        return false;
    }

    _move_state = mf_line_move;
    _block = _block -> next();
    int len = _block -> contentLength();

    if (_pos_in_block >= len) {
        _move_state = MoveFlag(_move_state | mf_pos_move);
        _pos_in_block = len;
    }

    return true;
}

bool Cursor::atLineEnd() {
    return _block -> contentLength() == _pos_in_block;
}
