#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <qsyntaxhighlighter.h>

class Lexer;
class LexerState;

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT
protected:
    void highlightBlock(const QString & text) Q_DECL_OVERRIDE;

    Lexer * lexer;
    LexerState * lexer_state;
public:
    Highlighter(QTextDocument * parent, Lexer * lexer);
    ~Highlighter();
};

#endif // IHIGHLIGHTER_H
