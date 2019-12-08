#include "custom_cursor.h"

#include "custom_document.h"

using namespace Custom;

Cursor::Cursor(Document * doc, IBlock * block, const qint64 & pos_in_block) : _doc(doc), _block(block), _select_end_block(nullptr), _pos_in_block(pos_in_block), _select_end_pos_in_block(NO_INFO) {

}
