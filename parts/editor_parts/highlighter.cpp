#include "highlighter.h"

#include "misc/utils.h"
#include "parts/document_types/idocument.h"
#include "parts/lexer/lexer.h"

void Highlighter::setDocument(IDocument * new_doc) {
    if (doc) {
        disconnect(doc, &QTextDocument::contentsChange, this, &Highlighter::reformatBlocks);
        disconnect(doc, &QTextDocument::cursorPositionChanged, this, &Highlighter::cursorPositionChanged);

        QTextCursor cursor(doc);
        cursor.beginEditBlock();

        for (QTextBlock blk = doc -> begin(); blk.isValid(); blk = blk.next())
            blk.layout() -> clearFormats();

        cursor.endEditBlock();
    }

    doc = new_doc;
    if (doc) {
        connect(doc, &QTextDocument::contentsChange, this, &Highlighter::reformatBlocks);
        sconnect(doc, &QTextDocument::cursorPositionChanged, this, &Highlighter::cursorPositionChanged);
//            d->rehighlightPending = true;
//            QTimer::singleShot(0, this, &SyntaxHighlighter::delayedRehighlight);
//        }
//        d->foldValidator.setup(qobject_cast<TextDocumentLayout *>(doc->documentLayout()));
    }
}

Highlighter::Highlighter(IDocument * doc, Lexer * lexer)
    : QObject(doc), doc(0), lexer(lexer)
{
    setDocument(doc);
}

Highlighter::~Highlighter() {
    setDocument(0);
    delete lexer;
}

void Highlighter::highlightBlock(const QString & text) {
//    qDebug() << "*** " << currentBlock().firstLineNumber();

    if (text.trimmed().isEmpty()) // INFO: ignore empty str
        return;

    lexer -> handle(text, this);

//    QTextBlock blk = nextBlock();

//    if (blk.isValid())
//        forceBlockRehighlightion(blk);
}

void Highlighter::rehighlight() {
    if (!doc)
        return;

    QTextCursor cursor(doc);
    rehighlight(cursor, QTextCursor::End);
}

void Highlighter::rehighlightBlock(const QTextBlock & block) {
    if (!doc || !block.isValid() || block.document() != doc)
        return;

    QTextCursor cursor(block);
    rehighlight(cursor, QTextCursor::EndOfBlock);
}

//void Highlighter::cursorPositionChanged(const QTextCursor & cursor) {

//}



void Highlighter::setFormat(int start, int count, const QTextCharFormat & format) {
    if (start < 0 || start >= formatChanges.count())
        return;

    const int end = qMin(start + count, formatChanges.count());
    for (int i = start; i < end; ++i)
        formatChanges[i] = format;
}

void Highlighter::setFormat(int start, int count, const QColor & color) {
    QTextCharFormat format;
    format.setForeground(color);
    setFormat(start, count, format);
}

void Highlighter::setFormat(int start, int count, const QFont & font) {
    QTextCharFormat format;
    format.setFont(font);
    setFormat(start, count, format);
}

QTextCharFormat Highlighter::format(int pos) const {
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

void Highlighter::setCurrentBlockUserData(QTextBlockUserData * data) {
    if (!current_block.isValid())
        return;

    current_block.setUserData(data);
}

QTextBlockUserData *SyntaxHighlighter::currentBlockUserData() const {
    if (!current_block.isValid())
        return 0;

    return current_block.userData();
}

static bool byStartOfRange(const QTextLayout::FormatRange & range, const QTextLayout::FormatRange & other) {
    return range.start < other.start;
}

void Highlighter::setExtraFormats(const QTextBlock & block, QVector<QTextLayout::FormatRange> & formats) {
    const int blockLength = block.length();

    if (block.layout() == 0 || blockLength == 0)
        return;

    Utils::sort(formats, byStartOfRange);

    const QVector<QTextLayout::FormatRange> all = block.layout()->formats();
    QVector<QTextLayout::FormatRange> previousSemanticFormats;
    QVector<QTextLayout::FormatRange> formatsToApply;
    previousSemanticFormats.reserve(all.size());
    formatsToApply.reserve(all.size() + formats.size());

    for (int i = 0, ei = formats.size(); i < ei; ++i)
        formats[i].format.setProperty(QTextFormat::UserProperty, true);

    foreach (const QTextLayout::FormatRange &r, all) {
        if (r.format.hasProperty(QTextFormat::UserProperty))
            previousSemanticFormats.append(r);
        else
            formatsToApply.append(r);
    }

    if (formats.size() == previousSemanticFormats.size()) {
        Utils::sort(previousSemanticFormats, byStartOfRange);

        int index = 0;
        for (; index != formats.size(); ++index) {
            const QTextLayout::FormatRange &range = formats.at(index);
            const QTextLayout::FormatRange &previousRange = previousSemanticFormats.at(index);

            if (range.start != previousRange.start ||
                    range.length != previousRange.length ||
                    range.format != previousRange.format)
                break;
        }

        if (index == formats.size())
            return;
    }

    formatsToApply += formats;

//    bool wasInReformatBlocks = d->inReformatBlocks;
//    d->inReformatBlocks = true;
    block.layout() -> setFormats(formatsToApply);
    doc -> markContentsDirty(block.position(), blockLength - 1);
//    inReformatBlocks = wasInReformatBlocks;
}



void Highlighter::reformatBlocks(int from, int charsRemoved, int charsAdded) {
//    foldValidator.reset();

//    rehighlightPending = false;

    QTextBlock block = doc -> findBlock(from);
    if (!block.isValid())
        return;

    QTextBlock lastBlock = doc -> findBlock(from + charsAdded + (charsRemoved > 0 ? 1 : 0));
    int endPosition;

    if (lastBlock.isValid())
        endPosition = lastBlock.position() + lastBlock.length();
    else
        endPosition = doc -> lastBlock().position() + doc -> lastBlock().length();

    bool forceHighlightOfNextBlock = false;

    while (block.isValid() && (block.position() < endPosition || forceHighlightOfNextBlock)) {
        const int stateBeforeHighlight = block.userState();

        reformatBlock(block, from, charsRemoved, charsAdded);

        forceHighlightOfNextBlock = (block.userState() != stateBeforeHighlight);

        block = block.next();
    }

    formatChanges.clear();

//    foldValidator.finalize();
}

void Highlighter::reformatBlock(const QTextBlock & block, int from, int charsRemoved, int charsAdded) {
    current_block = block;

    formatChanges.fill(QTextCharFormat(), block.length() - 1);
    highlightBlock(block.text());
    applyFormatChanges(from, charsRemoved, charsAdded);

//    foldValidator.process(currentBlock);

    current_block = QTextBlock();
}

void Highlighter::applyFormatChanges(int from, int charsRemoved, int charsAdded) {
    QVector<QTextLayout::FormatRange> old_ranges;
    QTextLayout * layout = currentBlock.layout();
    QVector<QTextLayout::FormatRange> ranges = layout -> formats();

    bool formatsChanged = false;
    bool doAdjustRange = currentBlock.contains(from);

    if (!ranges.isEmpty()) {
        auto it = ranges.begin();
        while (it != ranges.end()) {
            if (it -> format.property(QTextFormat::UserProperty).toBool()) {
                if (doAdjustRange)
                    formatsChanged =
                        adjustRange(*it, from - currentBlock.position(), charsRemoved, charsAdded)
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
        doc -> markContentsDirty(currentBlock.position(), currentBlock.length());
    }
}
