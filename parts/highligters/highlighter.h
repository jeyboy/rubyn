#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <qsyntaxhighlighter.h>
#include "parts/editor_parts/block_user_data.h"

class Lexer;
class LexerState;

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT
protected:
    void highlightBlock(const QString & text) Q_DECL_OVERRIDE;

    Lexer * lexer;

    friend class Lexer;
public:
    Highlighter(QTextDocument * parent, Lexer * lexer);
    ~Highlighter();
};

#endif // IHIGHLIGHTER_H
