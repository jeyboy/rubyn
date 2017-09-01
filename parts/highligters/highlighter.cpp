#include "highlighter.h"

#include "parts/lexer/lexer.h"

Highlighter::Highlighter(QTextDocument * parent, Lexer * lexer)
    : QSyntaxHighlighter(parent), lexer(lexer) {}

Highlighter::~Highlighter() { delete lexer; }

void Highlighter::highlightBlock(const QString & text) {
//    qDebug() << "*** " << currentBlock().firstLineNumber();

    if (text.trimmed().isEmpty()) // INFO: ignore empty str
        return;

    lexer -> handle(text, this);
}
