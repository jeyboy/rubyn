#include "highlighter.h"

#include "parts/lexer/lexer.h"

Highlighter::Highlighter(QTextDocument * parent, Lexer * lexer)
    : QSyntaxHighlighter(parent), lexer(lexer)
{
    connect(this, SIGNAL(forceBlockRehighlightion(QTextBlock)), this, SLOT(rehighlightBlock(QTextBlock)));
}

Highlighter::~Highlighter() { delete lexer; }

void Highlighter::highlightBlock(const QString & text) {
//    qDebug() << "*** " << currentBlock().firstLineNumber();

    if (text.trimmed().isEmpty()) // INFO: ignore empty str
        return;

    lexer -> handle(text, this);

//    QTextBlock blk = nextBlock();

//    if (blk.isValid())
//        forceBlockRehighlightion(blk);
}
