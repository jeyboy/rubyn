#include "pseudo_highlighter.h"

PseudoHighlighter::PseudoHighlighter() {

}

PseudoHighlighter::~PseudoHighlighter() {

}

QTextBlock PseudoHighlighter::prevBlock() const {

}
QTextBlock PseudoHighlighter::currentBlock() const {

}
QTextBlock PseudoHighlighter::nextBlock() const {

}

bool PseudoHighlighter::toggleFolding(const QTextBlock & blk) {

}

void PseudoHighlighter::setFormat(const int & start, const int & count, const QTextCharFormat & format) {

}
void PseudoHighlighter::setFormat(const int & start, const int & count, const QColor & color) {

}
void PseudoHighlighter::setFormat(const int & start, const int & count, const QFont & font) {

}

int PseudoHighlighter::previousBlockState() const {

}
int PseudoHighlighter::currentBlockState() const {

}
void PseudoHighlighter::setCurrentBlockState(const int & new_state) {

}
void PseudoHighlighter::initBlockUserData(QTextBlock & block, BlockUserData * prev_udata, BlockUserData *& udata, const int & text_len) {

}
