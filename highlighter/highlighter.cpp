#include "highlighter.h"

#include "misc/utils.h"

#include "editor/document_types/text_document.h"

#include <qtimer.h>

void Highlighter::setDocument(TextDocument * new_doc) {
    if (doc) {
        disconnect(doc, &QTextDocument::contentsChange, this, &Highlighter::reformatBlocks);
        disconnect(doc, &QTextDocument::cursorPositionChanged, this, &Highlighter::cursorPositionChanged);
//        disconnect(doc, &QTextDocument::blockCountChanged, this, &Highlighter::blockCountChanged);
        disconnect(_doc_wrapper, SIGNAL(enterPressed()), this, SLOT(enterPressed()));

        QTextCursor cursor(doc);

        cursor.beginEditBlock();

        for (QTextBlock blk = doc -> begin(); blk.isValid(); blk = blk.next())
            blk.layout() -> clearFormats();

        cursor.endEditBlock();
    }

    if (new_doc) {
        _doc_wrapper = new_doc;
        doc = _doc_wrapper -> toQDoc();

        connect(doc, &QTextDocument::contentsChange, this, &Highlighter::reformatBlocks);
        connect(doc, &QTextDocument::cursorPositionChanged, this, &Highlighter::cursorPositionChanged);
//        connect(doc, &QTextDocument::blockCountChanged, this, &Highlighter::blockCountChanged);
        connect(_doc_wrapper, SIGNAL(enterPressed()), this, SLOT(enterPressed()));
//            d->rehighlightPending = true;
//        QTimer::singleShot(0, this, SLOT(rehighlight()));
        rehighlight();
//        }
    }
}

void Highlighter::toggleFolding(QTextBlock & blk) {
    _doc_wrapper -> layout -> toggleFolding(blk);
}

Highlighter::Highlighter(TextDocument * doc) : QObject(), rehighlighting(false),
    _tokens(new TokenList()), _paras(new ParaList()), _doc_wrapper(nullptr), doc(nullptr)
{
    setDocument(doc);
}

Highlighter::~Highlighter() {
    setDocument(nullptr);
    delete _tokens;
    delete _paras;
}

void Highlighter::highlightBlock(const QString & text) {
//    qDebug() << "*** " << currentBlock().firstLineNumber() + 1;

    _doc_wrapper -> lexicate(text, this);
}

void Highlighter::rehighlight() {
    if (!doc)
        return;

    rehighlighting = true;

    QTextCursor cursor(doc);
    rehighlight(cursor, QTextCursor::End);

    rehighlighting = false;
}

void Highlighter::rehighlightBlock(const QTextBlock & block) {
    if (!doc || !block.isValid() || block.document() != doc)
        return;

    QTextCursor cursor(block);
    rehighlight(cursor, QTextCursor::EndOfBlock);
}

void Highlighter::setFormat(const int & start, const int & count, const QTextCharFormat & format) {
    if (start < 0 || start >= formatChanges.count())
        return;

    const int end = qMin(start + count, formatChanges.count());
    for (int i = start; i < end; ++i)
        formatChanges[i] = format;
}

void Highlighter::setFormat(const int & start, const int & count, const QColor & color) {
    QTextCharFormat format;
    format.setForeground(color);
    setFormat(start, count, format);
}

void Highlighter::setFormat(const int & start, const int & count, const QFont & font) {
    QTextCharFormat format;
    format.setFont(font);
    setFormat(start, count, format);
}

QTextCharFormat Highlighter::format(const int & pos) const {
    if (pos < 0 || pos >= formatChanges.count())
        return QTextCharFormat();

    return formatChanges.at(pos);
}

int Highlighter::previousBlockState() const {
    if (!current_block.isValid())
        return -1;

    const QTextBlock previous = prevBlock();
    if (!previous.isValid())
        return -1;

    return previous.userState();
}

int Highlighter::currentBlockState() const {
    if (!current_block.isValid())
        return -1;

    return current_block.userState();
}

void Highlighter::setCurrentBlockState(const int & new_state) {
    if (!current_block.isValid())
        return;

    current_block.setUserState(new_state);
}

//void Highlighter::setCurrentBlockUserData(QTextBlockUserData * data) {
//    if (!current_block.isValid())
//        return;

//    current_block.setUserData(data);
//}

//QTextBlockUserData * Highlighter::currentBlockUserData() const {
//    if (!current_block.isValid())
//        return 0;

//    return current_block.userData();
//}

//void Highlighter::setExtraFormats(const QTextBlock & block, QVector<QTextLayout::FormatRange> & formats) {
//    const int blockLength = block.length();

//    if (block.layout() == nullptr || blockLength == 0)
//        return;

//    Utils::sort(formats, byStartOfRange);

//    const QVector<QTextLayout::FormatRange> all = block.layout() -> formats();
//    QVector<QTextLayout::FormatRange> previous_semantic_formats;
//    QVector<QTextLayout::FormatRange> formats_to_apply;
//    previous_semantic_formats.reserve(all.size());
//    formats_to_apply.reserve(all.size() + formats.size());

//    for (int i = 0, ei = formats.size(); i < ei; ++i)
//        formats[i].format.setProperty(QTextFormat::UserProperty, true);

//    foreach (const QTextLayout::FormatRange &r, all) {
//        if (r.format.hasProperty(QTextFormat::UserProperty))
//            previous_semantic_formats.append(r);
//        else
//            formats_to_apply.append(r);
//    }

//    if (formats.size() == previous_semantic_formats.size()) {
//        Utils::sort(previous_semantic_formats, byStartOfRange);

//        int index = 0;
//        for (; index != formats.size(); ++index) {
//            const QTextLayout::FormatRange &range = formats.at(index);
//            const QTextLayout::FormatRange &previousRange = previous_semantic_formats.at(index);

//            if (range.start != previousRange.start ||
//                    range.length != previousRange.length ||
//                    range.format != previousRange.format)
//                break;
//        }

//        if (index == formats.size())
//            return;
//    }

//    formats_to_apply += formats;

////    bool wasInReformatBlocks = d->inReformatBlocks;
////    d->inReformatBlocks = true;
//    block.layout() -> setFormats(formats_to_apply);
//    doc -> markContentsDirty(block.position(), blockLength - 1);
////    inReformatBlocks = wasInReformatBlocks;
//}

void Highlighter::reformatBlocks(int from, int charsRemoved, int charsAdded) {
//    rehighlightPending = false;


//    if (!rehighlighting && charsRemoved) {
//        // recalc folding queues
//    }

    QTextBlock block = doc -> findBlock(from);
    if (!block.isValid())
        return;

    QTextBlock last_block = doc -> findBlock(from + charsAdded + (charsRemoved > 0 ? 1 : 0));
    int end_position;

    if (last_block.isValid())
        end_position = last_block.position() + last_block.length();
    else
        end_position = doc -> lastBlock().position() + doc -> lastBlock().length();

    bool force_next_block_highlight = false;

    while (block.isValid() && (block.position() < end_position || force_next_block_highlight)) {
        const int state_before_highlight = block.userState();

        reformatBlock(block, from, charsRemoved, charsAdded);

        force_next_block_highlight = !rehighlighting && (block.userState() != state_before_highlight);

        block = block.next();
    }

    formatChanges.clear();
}

void Highlighter::reformatBlock(const QTextBlock & block, int from, int charsRemoved, int charsAdded) {
//    qDebug() << "reformatBlock" << block.text();

    current_block = block;

    formatChanges.fill(QTextCharFormat(), block.length() - 1);
    highlightBlock(block.text());
    applyFormatChanges(from, charsRemoved, charsAdded);

    current_block = QTextBlock();
}

void Highlighter::applyFormatChanges(int from, int charsRemoved, int charsAdded) {
    QVector<QTextLayout::FormatRange> old_ranges;
    QTextLayout * layout = current_block.layout();
    QVector<QTextLayout::FormatRange> ranges = layout -> formats();

    bool formatsChanged = false;
    bool doAdjustRange = current_block.contains(from);

    if (!ranges.isEmpty()) {
        auto it = ranges.begin();
        while (it != ranges.end()) {
            if (it -> format.property(QTextFormat::UserProperty).toBool()) {
                if (doAdjustRange)
                    formatsChanged =
                        adjustRange(*it, from - current_block.position(), charsRemoved, charsAdded)
                            || formatsChanged;
                ++it;
            } else {
                old_ranges.append(*it);
                it = ranges.erase(it);
            }
        }
    }

    QTextCharFormat emptyFormat;
    QTextLayout::FormatRange r;
    QVector<QTextLayout::FormatRange> new_ranges;

    int i = 0;

    while (i < formatChanges.count()) {
        while(i < formatChanges.count() && formatChanges.at(i) == emptyFormat)
            ++i;

        if (i >= formatChanges.count())
            break;

        r.start = i;
        r.format = formatChanges.at(i);

        while(i < formatChanges.count() && formatChanges.at(i) == r.format)
            ++i;

        r.length = i - r.start;

        new_ranges << r;
    }

    formatsChanged = formatsChanged || (new_ranges.size() != old_ranges.size());

    for (int i = 0; !formatsChanged && i < new_ranges.size(); ++i) {
        const QTextLayout::FormatRange &o = old_ranges.at(i);
        const QTextLayout::FormatRange &n = new_ranges.at(i);
        formatsChanged = (o.start != n.start || o.length != n.length || o.format != n.format);
    }

    if (formatsChanged) {
        ranges.append(new_ranges);
        layout -> setFormats(ranges);
        doc -> markContentsDirty(current_block.position(), current_block.length());
    }
}

//void Highlighter::blockCountChanged(int count) {
//    qDebug() << "blockCountChanged" << count << doc -> blockCount();
//}

void Highlighter::cursorPositionChanged(const QTextCursor & /*cursor*/) {

}

void Highlighter::enterPressed() {
    qDebug() << "NEW LINE";
}
