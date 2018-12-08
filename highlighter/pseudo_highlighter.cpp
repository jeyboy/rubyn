#include "pseudo_highlighter.h"

#include "project/file.h"
#include "lexer/ilexer.h"

PseudoHighlighter::PseudoHighlighter(const QFont & f) : current_block_num(-1), font(f) {

}

PseudoHighlighter::PseudoHighlighter(const QFont & f, ILexer * lexer, const QString & text) : current_block_num(-1), font(f) {
    analyze(lexer, text);
}

PseudoHighlighter::PseudoHighlighter(const QFont & f, ILexer * lexer, QIODevice * file) : current_block_num(-1), font(f) {
    analyze(lexer, file);
}

PseudoHighlighter::~PseudoHighlighter() {
    clear();
}

bool PseudoHighlighter::analyze(ILexer * lexer, const QString & text) {
    clear();

    if (!lexer) return false;

    current_block_num = 0;

    PseudoHighlighterBlock * blk = new PseudoHighlighterBlock();
    blk -> setText(font, text);

    blocks.append(blk);

    initFormats(text.length());

    lexer -> handle(text, this);

    applyFormatChanges(blk);
    format_changes.clear();

    return true;
}
bool PseudoHighlighter::analyze(ILexer * lexer, QIODevice * file) {
    clear();

    if (!lexer) return false;

    current_block_num = 0;

    while(!file -> atEnd()) {
        QByteArray ar = file -> readLine();

        QString str(ar);
        PseudoHighlighterBlock * blk = new PseudoHighlighterBlock();
        blk -> setText(font, str);
        blocks.append(blk);

        initFormats(ar.length());

        lexer -> handle(str, this);

        applyFormatChanges(blk);

        ++current_block_num;
    }

    format_changes.clear();

    return true;
}

BlockUserData * PseudoHighlighter::prevUserData() {
    PseudoHighlighterBlock * prev_block = prevBlock();

    if (!prev_block) return nullptr;

    return prev_block -> user_data;
}
BlockUserData * PseudoHighlighter::userData() {
    PseudoHighlighterBlock * current_block = currentBlock();

    if (!current_block) return nullptr;

    return current_block -> user_data;
}
void PseudoHighlighter::setCurrentUserData(BlockUserData * new_data) {
    PseudoHighlighterBlock * current_block = currentBlock();

    if (!current_block) return;

    current_block -> setUserData(new_data);
}

int PseudoHighlighter::prevUserState() {
    PseudoHighlighterBlock * blk = prevBlock();

    return blk ? blk -> state : -1;
}
int PseudoHighlighter::userState() {
    PseudoHighlighterBlock * blk = currentBlock();

    return blk ? blk -> state : -1;
}
void PseudoHighlighter::setUserState(const int & new_state) {
    PseudoHighlighterBlock * current_block = currentBlock();

    if (!current_block) return;

    current_block -> setUserState(new_state);
}

PseudoHighlighterBlock * PseudoHighlighter::prevBlock() {
    if (current_block_num - 1 > -1 && blocks.length() > current_block_num - 1)
        return blocks[current_block_num - 1];

    return nullptr;
}

PseudoHighlighterBlock * PseudoHighlighter::currentBlock() {
    if (current_block_num > -1 && blocks.length() > current_block_num)
        return blocks[current_block_num];

    return nullptr;
}

void PseudoHighlighter::applyFormatChanges(PseudoHighlighterBlock * blk) {
    QTextLayout * layout = blk -> layout;

    QTextLayout::FormatRange r;
    QVector<QTextLayout::FormatRange> new_ranges;

    int i = 0;
    int limit = format_changes.count();

    while (i < limit) {
        while(i < limit && format_changes.at(i) == default_format)
            ++i;

        if (i >= limit)
            break;

        r.start = i;
        r.format = format_changes.at(i);

        while(i < limit && format_changes.at(i) == r.format)
            ++i;

        r.length = i - r.start;

        new_ranges << r;
    }

    if (new_ranges.isEmpty())
        layout -> clearFormats();
    else
        layout -> setFormats(new_ranges);

    layout -> beginLayout();

    /*QTextLine line = */layout -> createLine();
//    if (line.isValid())
//        line.setLineWidth(200);

    layout -> endLayout();
}
