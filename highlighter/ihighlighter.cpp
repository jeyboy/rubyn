#include "ihighlighter.h"

IHighlighter::~IHighlighter() {}

void IHighlighter::setFormat(const int & start, const int & count, const QTextCharFormat & format) {
    if (!fill_styles || start < 0 || start >= format_changes.count())
        return;

    const int end = qMin(start + count, format_changes.count());
    for (int i = start; i < end; ++i)
        format_changes[i] = format;
}

void IHighlighter::setFormat(const int & start, const int & count, const QColor & color) {
    if (!fill_styles) return;

    QTextCharFormat format;
    format.setForeground(color);
    setFormat(start, count, format);
}

void IHighlighter::setFormat(const int & start, const int & count, const QFont & font) {
    if (!fill_styles) return;

    QTextCharFormat format;
    format.setFont(font);
    setFormat(start, count, format);
}

void IHighlighter::initBlockUserData(QTextBlock & block, BlockUserData * prev_udata, BlockUserData *& udata, const int & text_len) {
    if (!udata) {
        udata = new BlockUserData(
            _tokens, _paras,
            prev_udata ? prev_udata -> token_end : nullptr,
            prev_udata ? prev_udata -> para_end : nullptr
        );
        block.setUserData(udata);
    }
    else {
        udata -> para_begin -> prev = prev_udata ? prev_udata -> para_end : _paras -> rootToken();
        udata -> token_begin -> prev = prev_udata ? prev_udata -> token_end : _tokens -> rootToken();
    }

    udata -> level = prev_udata ? prev_udata -> levelForNextBlock() : DEFAULT_LEVEL;
    udata -> token_end -> start_pos = text_len;
}
