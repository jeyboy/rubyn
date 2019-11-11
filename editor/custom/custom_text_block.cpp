#include "custom_text_block.h"

#include "custom_draw_context.h"
#include "custom_chars.h"

using namespace Custom;

TextBlock::TextBlock(const QString & txt, IBlock * prev_block) : IBlock(prev_block), content(txt) {
    colors.append(QColor(0, 0, 0));
    colors.append(QColor(255, 0, 0));
//    colors.append(QColor(0, 255, 0));
//    colors.append(QColor(0, 0, 255));
//    colors.append(QColor(255, 255, 0));
//    colors.append(QColor(0, 255, 255));
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


            //QChar::Tabulation	0x0009	Character tabulation.
            //QChar::LineFeed	0x000a
            //QChar::CarriageReturn	0x000d
            //QChar::Space	0x0020
            //QChar::Nbsp

            if (ch != ' ' && ch != '\t') {
                Custom::Chars::drawChar(
                    context -> _painter,
                    { offset, &Custom::Chars::glyph(ch, context -> _painter -> font()), colors[ra.bounded(colors.length() - 1)], Qt::white }
                );
            }

            offset.rx() += context -> __letter_with_pad_width;
        }
    }

    context -> _painter -> restore();
}
