#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

//#include <qobject.h>

#include <qtextdocument.h>
#include <qpointer.h>

#include "editor/block_user_data.h"

class TextDocument;

class Highlighter : public QObject {
    Q_OBJECT

    bool rehighlighting;

    TokenList * _tokens;
    ParaList * _paras;
//    Scope * _scope;
protected:
    void highlightBlock(const QString & text);

    TextDocument * _doc_wrapper;
    QPointer<QTextDocument> doc;

    QTextBlock current_block;

    QVector<QTextCharFormat> formats;
    QVector<QTextCharFormat> format_changes;
public:
    Highlighter(TextDocument * doc);
    ~Highlighter();

//    inline QPointer<TextDocument> document() { return doc; }
    void setDocument(TextDocument * new_doc);

    bool toggleFolding(const QTextBlock & blk);

    inline QTextBlock prevBlock() const { return current_block.previous(); }
    inline QTextBlock currentBlock() const { return current_block; }
    inline QTextBlock nextBlock() const { return current_block.next(); }

    QTextCharFormat format(const int & pos) const;

    void setFormat(const int & start, const int & count, const QTextCharFormat & format);
    void setFormat(const int & start, const int & count, const QColor & color);
    void setFormat(const int & start, const int & count, const QFont & font);

    int previousBlockState() const;
    int currentBlockState() const;
    void setCurrentBlockState(const int & new_state);

//    void setCurrentBlockUserData(QTextBlockUserData * data);
//    QTextBlockUserData * currentBlockUserData() const;

    void initBlockUserData(QTextBlock & block, BlockUserData * prev_udata, BlockUserData *& udata) {
        if (!udata) {
            udata = new BlockUserData(
                _tokens, _paras,
                prev_udata ? prev_udata -> token_end : nullptr,
                prev_udata ? prev_udata -> para_end : nullptr
            );
            block.setUserData(udata);
        }

        if (prev_udata) {
            udata -> level =
                prev_udata -> level + (
                    prev_udata -> para_control && !prev_udata -> para_control -> is_oneliner ? 1 : 0
                );
        }
    }

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
    void cursorPositionChanged(const QTextCursor & cursor);
    void enterPressed();
};


#endif // HIGHLIGHTER_H
