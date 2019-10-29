#include "custom_text_block.h"

#include "custom_draw_context.h"

using namespace Custom;

TextBlock::TextBlock(const QString & txt, IBlock * prev_block) : IBlock(prev_block), content(txt) {

}

void TextBlock::draw(DrawContext *& context) {
    if (content.length() > context -> maxStrLength()) {
        context -> _painter -> drawText(
          context -> _pos,
          content.mid(context -> leftStrPad(), context -> maxStrLength())
        );
    } else {
        context -> _painter -> drawText(
          context -> _pos,
          content.mid(context -> leftStrPad())
        );
    }
}
