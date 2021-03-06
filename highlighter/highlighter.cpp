#include "highlighter.h"

#include "misc/utils.h"

#include "controls/logger.h"

#include <qtimer.h>

void Highlighter::setDocument(TextDocument * new_doc) {
    if (doc) {
        disconnect(doc, &QTextDocument::contentsChange, this, &Highlighter::reformatBlocks);
//        disconnect(doc, &QTextDocument::cursorPositionChanged, this, &Highlighter::cursorPositionChanged);
//        disconnect(doc, &QTextDocument::blockCountChanged, this, &Highlighter::blockCountChanged);
//        disconnect(_doc_wrapper, SIGNAL(enterPressed()), this, SLOT(enterPressed()));

        QTextCursor cursor(doc);

        cursor.beginEditBlock();

        for (QTextBlock blk = doc -> begin(); blk.isValid(); blk = blk.next())
            blk.layout() -> clearFormats();

        cursor.endEditBlock();
    }

    if (new_doc) {
        Logger::obj().info("Parsing", new_doc -> docName());
        qDebug() << new_doc -> docName();
        doc = new_doc;

        connect(doc, &QTextDocument::contentsChange, this, &Highlighter::reformatBlocks);
//        connect(doc, &QTextDocument::cursorPositionChanged, this, &Highlighter::cursorPositionChanged);
//        connect(doc, &QTextDocument::blockCountChanged, this, &Highlighter::blockCountChanged);
//        connect(_doc_wrapper, SIGNAL(enterPressed()), this, SLOT(enterPressed()));
//            d->rehighlightPending = true;
//        QTimer::singleShot(0, this, SLOT(rehighlight()));
        rehighlight();
//        }
    }
}

Highlighter::Highlighter(TextDocument * doc) : QObject(), IHighlighter(), rehighlighting(false), old_amount(0), doc(nullptr) {
    setDocument(doc);
}

Highlighter::~Highlighter() {
    setDocument(nullptr);
}

void Highlighter::procFlagsForLastHighlightedBlock(const QTextBlock & block) {
    BlockUserData * prev_udata = TextDocumentLayout::getUserDataForBlock(block.previous());

    if (prev_udata && prev_udata -> hasFolding()) {
        if (block.isValid()) {
            BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(block);

            prev_udata -> para_control -> is_oneliner = !udata || (udata && udata -> level <= prev_udata -> level);
        }
        else prev_udata -> para_control -> is_oneliner = true;
    }
}

void Highlighter::rehighlight() {
    if (!doc)
        return;

    rehighlighting = true;
    old_amount = doc -> blockCount();

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

QTextCharFormat Highlighter::format(const int & pos) const {
    if (pos < 0 || pos >= format_changes.count())
        return QTextCharFormat();

    return format_changes.at(pos);
}

int Highlighter::prevUserState() {
    if (!current_block.isValid())
        return -1;

    const QTextBlock previous = prevBlock();
    if (!previous.isValid())
        return -1;

    return previous.userState();
}

int Highlighter::userState() {
    if (!current_block.isValid())
        return -1;

    return current_block.userState();
}

void Highlighter::setUserState(const int & new_state) {
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

void Highlighter::reformatBlocks(int from, int chars_removed, int chars_added) {
//    rehighlightPending = false;

    QTextBlock block = doc -> findBlock(from);
    if (!block.isValid())
        return;

    int diff_count = doc -> blockCount() - old_amount;

    if (diff_count != 0)
        doc -> blocksLayoutChange(block.blockNumber(), diff_count);

    QTextBlock last_block = doc -> findBlock(from + chars_added + (chars_removed > 0 ? 1 : 0));
    int end_position;

//    qDebug() << "reformatBlocks" << '(' << from << chars_added << chars_removed << ')' << block.blockNumber() << last_block.blockNumber();

    if (last_block.isValid())
        end_position = last_block.position() + last_block.length();
    else
        end_position = doc -> lastBlock().position() + doc -> lastBlock().length();

    bool force_next_block_highlight = false;

    while (block.isValid() && (force_next_block_highlight || block.position() < end_position)) {
        const int state_before_highlight = block.userState();

        reformatBlock(block, from, chars_removed, chars_added);

        force_next_block_highlight = !rehighlighting && (block.userState() != state_before_highlight);

        block = block.next();
    }

    procFlagsForLastHighlightedBlock(block);

    format_changes.clear();

    emit doc -> highlightingComplete();
    old_amount = doc -> blockCount();
}

void Highlighter::reformatBlock(const QTextBlock & block, int from, int chars_removed, int chars_added) {
    current_block = block;

    initFormats(block.length());
    highlightBlock(block.text());
    applyFormatChanges(from, chars_removed, chars_added);

    current_block = QTextBlock();
}

void Highlighter::applyFormatChanges(int from, int chars_removed, int chars_added) {
    QVector<QTextLayout::FormatRange> old_ranges;
    QTextLayout * layout = current_block.layout();
    QVector<QTextLayout::FormatRange> ranges = layout -> formats();

    bool formats_changed = false;
    bool do_adjust_range = current_block.contains(from);

    if (!ranges.isEmpty()) {
        auto it = ranges.begin();
        while (it != ranges.end()) {
            if (it -> format.property(QTextFormat::UserProperty).toBool()) {
                if (do_adjust_range)
                    formats_changed =
                        adjustRange(*it, from - current_block.position(), chars_removed, chars_added)
                            || formats_changed;
                ++it;
            } else {
                old_ranges.append(*it);
                it = ranges.erase(it);
            }
        }
    }

    QTextLayout::FormatRange r;
    QVector<QTextLayout::FormatRange> new_ranges;

    int i = 0;

    while (i < format_changes.count()) {
        while(i < format_changes.count() && format_changes.at(i) == default_format)
            ++i;

        if (i >= format_changes.count())
            break;

        r.start = i;
        r.format = format_changes.at(i);

        while(i < format_changes.count() && format_changes.at(i) == r.format)
            ++i;

        r.length = i - r.start;

        new_ranges << r;
    }

    formats_changed = formats_changed || (new_ranges.size() != old_ranges.size());

    for (int i = 0; !formats_changed && i < new_ranges.size(); ++i) {
        const QTextLayout::FormatRange &o = old_ranges.at(i);
        const QTextLayout::FormatRange &n = new_ranges.at(i);
        formats_changed = (o.start != n.start || o.length != n.length || o.format != n.format);
    }

    if (formats_changed) {
        ranges.append(new_ranges);
        layout -> setFormats(ranges);
        doc -> markContentsDirty(current_block.position(), current_block.length());
    }
}
