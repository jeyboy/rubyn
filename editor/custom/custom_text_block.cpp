#include <qdebug.h>

#include "custom_text_block.h"

#include "custom_draw_context.h"
#include "custom_chars.h"

using namespace Custom;

TextBlock::TextBlock(const QByteArray/*QString*/ & txt, IBlock * prev_block) : IBlock(prev_block), content(txt) {
    content.squeeze();
}

void TextBlock::draw(DrawContext * context) {
    bool simple = false;

    context -> _painter -> save();

    QString str;

    if (content.length() > context -> maxStrLength()) {
        str = content.mid(context -> leftStrPad(), context -> maxStrLength());
    } else {
        str = content.mid(context -> leftStrPad());
    }

    if (simple) {
      context -> _painter -> drawText(context -> _pos, str);
    } else {
        QPointF offset = context -> _pos;

    //    It can be constructed by passing a QFont object to QRawFont::fromFont(). The function will return a QRawFont object representing the font that will be selected as response to the QFont query and the selected writing system.

        for(int i = 0; i < str.length(); i++) {
            const QChar & ch = str[i];

            Custom::Chars::drawChar(
                context -> _painter,
                { offset, &Custom::Chars::glyph(ch, context -> _painter -> font(), context -> _visualization), Qt::black/*Chars::randomColor()*/, Qt::white/*Chars::randomColor()*/ /*Qt::blue*/ }
            );


//            if (ch != ' ' && ch != '\t') {
//                Custom::Chars::drawChar(
//                    context -> _painter,
//                    { offset, &Custom::Chars::glyph(ch, context -> _painter -> font()), /*Qt::black*/Chars::randomColor(), /*Qt::white*//*Chars::randomColor()*/ Qt::blue }
//                );
//            }

            offset.rx() += context -> __letter_with_pad_width;
        }
    }

    context -> _painter -> restore();
}
