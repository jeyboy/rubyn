#include "highlighter.h"

#include "parts/lexer/lexer.h"
#include "highlight_format_factory.h"
#include "parts/editor_parts/block_user_data.h"

Highlighter::Highlighter(QTextDocument * parent, Lexer * lexer)
    : QSyntaxHighlighter(parent), lexer(lexer) {}

Highlighter::~Highlighter() { delete lexer; }

void Highlighter::highlightBlock(const QString & text) {
//    qDebug() << "*** " << currentBlock().firstLineNumber();

    if (text.trimmed().isEmpty()) // INFO: ignore empty str
        return;

    QTextBlock block = currentBlock();
    QTextBlock prev_block = block.previous();

    BlockUserData * udata = reinterpret_cast<BlockUserData *>(prev_block.userData());
    LexerState * state = 0;

    if (!udata)
        state = new LexerState();
    else
        state = new LexerState(*udata -> state);

    LexToken * lexems = lexer -> analize(text, state);

    BlockUserData * cdata = reinterpret_cast<BlockUserData *>(block.userData());

    state -> index = 0;
    if (!cdata)
        cdata = new BlockUserData(false, false, state);
    else
        cdata -> state = state;

    block.setUserData(cdata);

    while(lexems) {
        LexToken * curr = lexems;
        lexems = lexems -> next;

        setFormat(curr -> left, curr -> length, HighlightFormatFactory::obj().getFormatFor(curr -> lexem));

        delete curr;
    }
}
