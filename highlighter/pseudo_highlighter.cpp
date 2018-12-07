#include "pseudo_highlighter.h"

#include "project/file.h"
#include "lexer/ilexer.h"

PseudoHighlighter::PseudoHighlighter() : current_block_num(-1) {

}

PseudoHighlighter::~PseudoHighlighter() {
    blocks.clear();
}

void PseudoHighlighter::analyze(ILexer * lexer, const QString & text) {
    blocks.clear();
    current_block_num = 0;

    QTextBlock blk;
    blk.layout() -> setText(text);
    blocks.append(blk);

    lexer -> handle(text, this);
}
void PseudoHighlighter::analyze(ILexer * lexer, QIODevice * file) {
    blocks.clear();
    current_block_num = 0;

    while(!file -> atEnd()) {
        QByteArray ar = file -> readLine();

        QTextBlock blk;
        blk.layout() -> setText(ar);
        blocks.append(blk);

        lexer -> handle(blk.text(), this);
        ++current_block_num;
    }
}

QTextBlock PseudoHighlighter::prevBlock() const {
    if (current_block_num - 1 > -1 && blocks.length() > current_block_num - 1)
        return blocks.at(current_block_num - 1);

    return QTextBlock();
}
QTextBlock PseudoHighlighter::currentBlock() const {
    if (current_block_num > -1 && blocks.length() > current_block_num)
        return blocks.at(current_block_num);

    return QTextBlock();
}
QTextBlock PseudoHighlighter::nextBlock() const {
    if (current_block_num > -1 && blocks.length() > current_block_num + 1)
        return blocks.at(current_block_num + 1);

    return QTextBlock();
}

int PseudoHighlighter::previousBlockState() const {
    return prevBlock().userState();
}
int PseudoHighlighter::currentBlockState() const {
    return currentBlock().userState();
}
void PseudoHighlighter::setCurrentBlockState(const int & new_state) {
    QTextBlock current_block = currentBlock();

    if (!current_block.isValid())
        return;

    current_block.setUserState(new_state);
}
