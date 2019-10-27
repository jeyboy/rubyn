#include "custom_text_block.h"

#include "custom_draw_context.h"

using namespace Custom;

TextBlock::TextBlock(const QString & txt, IBlock * prev_block) : IBlock(prev_block), content(txt) {

}

void TextBlock::draw(DrawContext *& context) {
    context -> _painter -> drawText(
      context -> _pos,
      content
    );
}
