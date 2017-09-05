#include "highlighter.h"

#include "parts/lexer/lexer.h"
#include "parts/document_types/idocument.h"

Highlighter::Highlighter(IDocument * doc, Lexer * lexer)
    : QSyntaxHighlighter(doc), lexer(lexer)
{

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
