#include <qdebug.h>

#include "custom_text_block.h"

#include "custom_draw_context.h"
#include "custom_chars.h"

using namespace Custom;

TextBlock::TextBlock(const QByteArray/*QString*/ & txt, IBlock * prev_block) : IBlock(prev_block), _content(txt) {
    _content.squeeze();
}

void TextBlock::insertChar(const int & pos, const QChar & ch) {
    if (pos > _content.length()) {
        _content += QString(pos - _content.length(), QChar(' '));
        _content.append(ch);
    }
    else _content.insert(pos, ch);
}

void TextBlock::insertText(const int & pos, const QByteArray & text) {
    if (pos > _content.length()) {
        _content += QString(pos - _content.length(), QChar(' '));
        _content.append(text);
    }
    else _content.insert(pos, text);
}

void TextBlock::removeText(const int & pos, const int & len) {
    if (pos >= _content.length())
        return;

    _content.remove(pos, len);
}

void TextBlock::draw(DrawContext * context) {
    bool simple = false;

    context -> _painter -> save();

    QString str;

    qint32 left_offset = context -> leftStrPad();
    qint32 str_len = context -> maxStrLength();

    if (_content.length() > context -> maxStrLength()) {
        str = _content.mid(left_offset, str_len);
    } else {
        str = _content.mid(left_offset);
    }

    context -> _on_screen.insert(
        this, { QRectF(context -> _pos, QSizeF(context -> __content_width, context -> __line_height)), left_offset, str_len, context -> __letter_with_pad_width, context -> _letter_spacing }
    );

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
