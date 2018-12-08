#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "highlighter/ihighlighter.h"
#include "editor/document_types/text_document.h"

#include <qpointer.h>

class TextDocument;

class Highlighter : public QObject, public IHighlighter {
    Q_OBJECT

    bool rehighlighting;
protected:
    inline void highlightBlock(const QString & text) { doc -> lexicate(text, this); }
    void procFlagsForLastHighlightedBlock(const QTextBlock & block);

    QPointer<TextDocument> doc;

    QTextBlock current_block;
public:
    Highlighter(TextDocument * doc);
    ~Highlighter();

//    inline QPointer<TextDocument> document() { return doc; }
    void setDocument(TextDocument * new_doc);

    inline bool toggleFolding() { return doc -> layout -> toggleFolding(current_block); }

    inline QTextBlock prevBlock() const { return current_block.previous(); }
//    inline QTextBlock currentBlock() const { return current_block; }
//    inline QTextBlock nextBlock() const { return current_block.next(); }

    QTextCharFormat format(const int & pos) const;

    inline BlockUserData * prevUserData() { return reinterpret_cast<BlockUserData *>(prevBlock().userData()); }
    inline BlockUserData * userData() { return reinterpret_cast<BlockUserData *>(current_block.userData()); }
    inline void setCurrentUserData(BlockUserData * new_data) { current_block.setUserData(new_data); }

    int prevUserState();
    int userState();
    void setUserState(const int & new_state);

//    void setCurrentBlockUserData(QTextBlockUserData * data);
//    QTextBlockUserData * currentBlockUserData() const;

//    inline void clearExtraFormatForCurrBlock() {
//        if (current_block.isValid())
//            current_block.layout() -> clearFormats();
//    }
//    inline void setExtraFormatToCurrBlock(const int & start, const int & count, const QTextCharFormat & format) {
//        if (current_block.isValid())
//            setExtraFormats(current_block, QVector<QTextLayout::FormatRange>() << QTextLayout::FormatRange{start, count, format});
//    }
//    inline void setExtraFormat(const int & start, const int & count, const QTextCharFormat & format) {
//        setExtraFormats(doc -> findBlock(start), QVector<QTextLayout::FormatRange>() << QTextLayout::FormatRange{start, count, format});
//    }
//    void setExtraFormats(const QTextBlock & block, QVector<QTextLayout::FormatRange> & formats);

protected:
//    static bool byStartOfRange(const QTextLayout::FormatRange & range, const QTextLayout::FormatRange & other) {
//        return range.start < other.start;
//    }

    void reformatBlock(const QTextBlock & block, int from, int charsRemoved, int charsAdded);

    inline void rehighlight(QTextCursor & cursor, QTextCursor::MoveOperation operation) {
//        inReformatBlocks = true;
        int from = cursor.position();
        cursor.movePosition(operation);
        reformatBlocks(from, 0, cursor.position() - from); // wtf?
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
//    void blockCountChanged(int count);
//    void cursorPositionChanged(const QTextCursor & cursor);
//    void enterPressed();
};


#endif // HIGHLIGHTER_H
