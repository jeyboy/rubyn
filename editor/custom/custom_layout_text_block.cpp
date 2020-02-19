#include <qdebug.h>

#include "custom_layout_text_block.h"

#include "custom_draw_context.h"
#include "custom_chars.h"

using namespace Custom;

LayoutTextBlock::LayoutTextBlock(const QByteArray/*QString*/ & txt, IBlock * prev_block) : IBlock(prev_block), _content(nullptr) {
    _content = new QTextLayout(txt);
}

void LayoutTextBlock::insertChar(const int & pos, const QChar & ch) {
//    if (pos > _content.length()) {
//        _content += QString(pos - _content.length(), QChar(' '));
//        _content.append(ch);
//    }
//    else _content.insert(pos, ch);
}

void LayoutTextBlock::appendText(const QString & text) {
//    _content.append(text);
}

void LayoutTextBlock::insertText(const int & pos, const QString & text) {
//    if (pos > _content.length()) {
//        _content += QString(pos - _content.length(), QChar(' '));
//        _content.append(text);
//    }
//    else _content.insert(pos, text);
}

void LayoutTextBlock::removeText(const int & pos, const int & len) {
//    if (pos >= _content.length())
//        return;

//    _content.remove(pos, len);
}

void LayoutTextBlock::draw(DrawContext * context) {
    context -> _painter -> save();

    QList<QGlyphRun> str;

    qint32 left_offset = context -> leftStrPad();
    qint32 str_len = context -> maxStrLength();

    _content -> setFont(context -> _painter -> font());

    if (text().length() > str_len) {
        str = _content -> glyphRuns(left_offset, str_len);
    } else {
        str = _content -> glyphRuns(left_offset);
    }

    context -> _on_screen.insert(
        this, { QRectF(context -> _pos, QSizeF(context -> __content_width, context -> __line_height)), left_offset, str_len, context -> __letter_with_pad_width, context -> _letter_spacing }
    );

    QList<QGlyphRun>::ConstIterator it = str.constBegin();
    QPointF offset = context -> _pos;

    for(; it != str.constEnd(); it++) {
        context -> _painter -> drawGlyphRun(context -> _pos, *it);
        offset.rx() += (*it).boundingRect().width();
    }

    context -> _painter -> restore();
}
