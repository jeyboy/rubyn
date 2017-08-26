#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <qsyntaxhighlighter.h>

class Lexer;

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT
protected:
    void highlightBlock(const QString & text) Q_DECL_OVERRIDE;

    Lexer * lexer;
public:
    Highlighter(QTextDocument * parent, Lexer * lexer);
    ~Highlighter() { delete lexer; }
};

#endif // IHIGHLIGHTER_H
