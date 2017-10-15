#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

//#include <qobject.h>

#include <qpointer.h>

#include "parts/editor_parts/block_user_data.h"

class Lexer;
class LexerState;
class TextDocument;

class Highlighter : public QObject {
    Q_OBJECT

    bool rehighlighting;
protected:
    void highlightBlock(const QString & text);

    QPointer<TextDocument> doc;
    QTextBlock current_block;

    QVector<QTextCharFormat> formats;
    QVector<QTextCharFormat> formatChanges;
public:
    Highlighter(TextDocument * doc);
    ~Highlighter();

//    inline QPointer<TextDocument> document() { return doc; }
    void setDocument(TextDocument * new_doc);

    QTextBlock prevBlock() const { return current_block.previous(); }
    QTextBlock currentBlock() const { return current_block; }
    QTextBlock nextBlock() const { return current_block.next(); }

    QTextCharFormat format(int pos) const;

    void setFormat(int start, int count, const QTextCharFormat & format);
    void setFormat(int start, int count, const QColor & color);
    void setFormat(int start, int count, const QFont & font);

    int previousBlockState() const;

    int currentBlockState() const;
    void setCurrentBlockState(const int & new_state);

    void setCurrentBlockUserData(QTextBlockUserData * data);
    QTextBlockUserData * currentBlockUserData() const;

    void setExtraFormats(const QTextBlock & block, QVector<QTextLayout::FormatRange> & formats);

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
    static bool byStartOfRange(const QTextLayout::FormatRange & range, const QTextLayout::FormatRange & other) {
        return range.start < other.start;
    }

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

public slots:
    void rehighlight();
    void rehighlightBlock(const QTextBlock & block);

protected slots:
//    void contentsChanged();
    void reformatBlocks(int from, int charsRemoved, int charsAdded);
    void cursorPositionChanged(const QTextCursor & cursor);
};


#endif // HIGHLIGHTER_H
