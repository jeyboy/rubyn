#ifndef PSEUDO_HIGHLIGHTER_H
#define PSEUDO_HIGHLIGHTER_H

#include "highlighter/ihighlighter.h"

class ILexer;

struct PseudoHighlighterBlock {
    int state;
    QTextLayout * layout;
    BlockUserData * user_data;

    PseudoHighlighterBlock() : state(-1), layout(nullptr), user_data(nullptr) {

    }

    void setText(const QFont & f, const QString & str) {
        if (!layout)
            layout = new QTextLayout(str, f);
        else {
            layout -> setFont(f);
            layout -> setText(str);
        }
    }

    ~PseudoHighlighterBlock() {
        delete layout;
        delete user_data;
    }

    inline void setUserState(const int & new_state) { state = new_state; }
    inline void setUserData(BlockUserData * new_user_data) { user_data = new_user_data; }
};

class PseudoHighlighter : public IHighlighter {
    QVector<PseudoHighlighterBlock *> blocks;

    int current_block_num;
    QFont font;
public:
    PseudoHighlighter(const QFont & f);
    PseudoHighlighter(const QFont & f, ILexer * lexer, const QString & text);
    PseudoHighlighter(const QFont & f, ILexer * lexer, QIODevice * file);

    ~PseudoHighlighter();

    inline int linesCount() { return blocks.length(); }
    inline QTextLayout * block(const int & num) {
        if (num < 0 || num >= blocks.length())
            return nullptr;

        return blocks[num] -> layout;
    }

    bool analyze(ILexer * lexer, const QString & text);
    bool analyze(ILexer * lexer, QIODevice * file);

    void setFillStyles(const bool & fill) { fill_styles = fill; }

    BlockUserData * prevUserData();
    BlockUserData * userData();
    void setCurrentUserData(BlockUserData * new_data);

    int prevUserState();
    int userState();
    void setUserState(const int & new_state);

protected:
    PseudoHighlighterBlock * prevBlock();
    PseudoHighlighterBlock * currentBlock();

    void clear() {
        qDeleteAll(blocks);
        blocks.clear();
    }
    void applyFormatChanges(PseudoHighlighterBlock * blk);
};

#endif // PSEUDO_HIGHLIGHTER_H
