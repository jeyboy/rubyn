#include "custom_text_block.h"

#include "custom_draw_context.h"

using namespace Custom;

TextBlock::TextBlock(const QString & txt, IBlock * prev_block) : IBlock(prev_block), content(txt) {

}

void TextBlock::draw(DrawContext *& context) {
//    int symb_count = qAbs(qFloor(context -> _pos.x() / context -> __symbol_width));
//    qDebug() << "draw" << context -> _pos.x() << symb_count;

    qDebug() << "DRAW" << context -> leftStrPad() << context -> maxStrLength();

//    context -> _painter -> drawRect(
//        context -> _pos.x(), context -> _pos.y(),
//        symb_count * context -> __symbol_width, context -> __line_height
//    );



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
