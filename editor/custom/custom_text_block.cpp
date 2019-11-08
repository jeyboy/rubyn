#include "custom_text_block.h"

#include "custom_draw_context.h"

using namespace Custom;

TextBlock::TextBlock(const QString & txt, IBlock * prev_block) : IBlock(prev_block), content(txt) {
    pens.append(new QPen(QColor(255, 0, 0), 1));
    pens.append(new QPen(QColor(255, 0, 0), 2));
    pens.append(new QPen(QColor(255, 0, 0), 3));

    pens.append(new QPen(QColor(0, 255, 0), 1));
    pens.append(new QPen(QColor(0, 255, 0), 2));
    pens.append(new QPen(QColor(0, 255, 0), 3));

    pens.append(new QPen(QColor(0, 0, 255), 1));
    pens.append(new QPen(QColor(0, 0, 255), 2));
    pens.append(new QPen(QColor(0, 0, 255), 3));
}

void TextBlock::draw(DrawContext * context) {
    QString str;

    if (content.length() > context -> maxStrLength()) {
        str = content.mid(context -> leftStrPad(), context -> maxStrLength());
    } else {
        str = content.mid(context -> leftStrPad());
    }

//    context -> _painter -> drawText(context -> _pos, str);

    QPointF offset = context -> _pos;

//    It can be constructed by passing a QFont object to QRawFont::fromFont(). The function will return a QRawFont object representing the font that will be selected as response to the QFont query and the selected writing system.


    for(int i = 0; i < str.length(); i++) {
        context -> _painter -> setPen(*pens[ra.bounded(pens.length() - 1)]);
        context -> _painter -> drawText(offset, QString(str[i]));
        offset.rx() += context -> __letter_with_pad_width;
    }
}
