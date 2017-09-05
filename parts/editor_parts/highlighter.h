#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

//#include <qobject.h>

#include "parts/editor_parts/block_user_data.h"

class Lexer;
class LexerState;
class IDocument;

class Highlighter : public QObject {
    Q_OBJECT
protected:
    void highlightBlock(const QString & text);

    Lexer * lexer;
    IDocument * doc;
    QTextBlock current_block;

    QVector<QTextCharFormat> formats;
    QVector<QTextCharFormat> formatChanges;
public:
    Highlighter(IDocument * doc, Lexer * lexer);
    ~Highlighter();

    void setDocument(IDocument * new_doc);

    QTextBlock prevBlock() const { return current_block.previous(); }
    QTextBlock currentBlock() const { return current_block; }
    QTextBlock nextBlock() const { return current_block.next(); }

//    inline void setFormat(const int & start, const int & count, const QTextCharFormat & format) {
//        QSyntaxHighlighter::setFormat(start, count, format);
//    }

protected:
    static bool adjustRange(QTextLayout::FormatRange & range, int from, int charsRemoved, int charsAdded) {
        if (range.start >= from) {
            range.start += charsAdded - charsRemoved;
            return true;
        } else if (range.start + range.length > from) {
            range.length += charsAdded - charsRemoved;
            return true;
        }
        return false;
    }

    void reformatBlocks(int from, int charsRemoved, int charsAdded);
    void reformatBlock(const QTextBlock & block, int from, int charsRemoved, int charsAdded);

    inline void rehighlight(QTextCursor & cursor, QTextCursor::MoveOperation operation) {
//        inReformatBlocks = true;
        int from = cursor.position();
        cursor.movePosition(operation);
        reformatBlocks(from, 0, cursor.position() - from);
//        inReformatBlocks = false;
    }

    void applyFormatChanges(int from, int charsRemoved, int charsAdded);
//    void updateFormats(const FontSettings &fontSettings);

    void reformatBlock(const QTextBlock & block, int from, int charsRemoved, int charsAdded);

public slots:
    void rehighlight();
    void rehighlightBlock(const QTextBlock & block);

protected slots:
//    void contentsChanged();
    void reformatBlocks(int from, int charsRemoved, int charsAdded);
    void cursorPositionChanged(const QTextCursor & cursor);
};


#endif // HIGHLIGHTER_H
