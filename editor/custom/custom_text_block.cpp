#include "custom_text_block.h"

using namespace Custom;

TextBlock::TextBlock(const QString & txt, IBlock * prev_block) : IBlock(prev_block), content(txt) {

}
