#include "code_editor.h"

#include <qstringbuilder.h>
#include <qwidget.h>
#include <qtextobject.h>
#include <qpainter.h>
#include <qfile.h>
#include <qscrollbar.h>
#include <qtooltip.h>
#include <qcompleter.h>
#include <qabstractitemview.h> // completer dependency

#include "editor_parts/overlay_info.h"
#include "editor_parts/file.h"
#include "editor_parts/extra_area.h"

#include "parts/document_types/text_document.h"

QString CodeEditor::word_boundary("~#%^&*()+{}|\"<>,./;'[]\\-= "); // end of word // "~!@#$%^&*()+{}|:\"<>?,./;'[]\\-= "

CodeEditor::CodeEditor(QWidget * parent) : QPlainTextEdit(parent), completer(0), wrapper(0), overlay(new OverlayInfo()),
    tooplip_block_num(-1), tooplip_block_pos(-1), extra_overlay_block_num(-1), folding_y(NO_FOLDING), folding_overlay_y(NO_FOLDING), curr_block_number(-1)
{
    extra_area = new ExtraArea(this);  

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateExtraAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateExtraArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

//    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateExtraAreaWidth(int)));
//    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateExtraArea(QRect,int)));
//    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateExtraAreaWidth(0);
//    highlightCurrentLine();

    setLineWrapMode(NoWrap);

    verticalScrollBar() -> setSingleStep(2);
//    scrollBarWidgets()

    //    QTextCursor cursor = ui->textEdit->textCursor();
    //    ui->textEdit->selectAll();
    //    ui->textEdit->setFontPointSize(32);
    //    ui->textEdit->setTextCursor( cursor );

    setMouseTracking(true);

    prepareIcons();
}

CodeEditor::~CodeEditor() {
    delete overlay;
    icons.clear();
}

void CodeEditor::setCompleter(QCompleter * new_completer) {
    if (completer)
        QObject::disconnect(completer, 0, this, 0);

    completer = new_completer;

    if (!completer)
        return;

    completer -> setWidget(this);
    completer -> setCompletionMode(QCompleter::PopupCompletion);
    completer -> setCaseSensitivity(Qt::CaseInsensitive);
    completer -> setFilterMode(Qt::MatchStartsWith); // Qt::MatchStartsWith // Qt::MatchContains // Qt::MatchEndsWith

    connect(completer, SIGNAL(activated(QString)), this, SLOT(applyCompletion(QString)));
}

void CodeEditor::openDocument(File * file) {
    if (file && file -> isText()) {
        QFont new_font(font().family(), 11);
//        new_font.setStretch(90);

        wrapper = file -> asText();
        QTextDocument * text_doc = wrapper -> toQDoc();

        text_doc -> setDefaultFont(new_font);
        setFont(new_font);

        setDocumentTitle(file -> name());
        setDocument(text_doc);

        updateExtraAreaWidth(0);

        if (!file -> isFullyReaded()) {
            //    verticalScrollBar()
        }
    }
    // else inform user about fail
}

int CodeEditor::foldingOffset() {
    int digits = qMax(1, QString::number(blockCount()).length());
    return HPADDING * 2 + symbol_width * digits;
}

int CodeEditor::extraAreaWidth() {
    return foldingOffset() + HPADDING + FOLDING_WIDTH;
}

void CodeEditor::updateExtraAreaWidth(int /* newBlockCount */) {
    extra_zone_width = extraAreaWidth();
    setViewportMargins(extra_zone_width, 0, 0, 0);
    line_number_width = extra_zone_width - HPADDING * 2 - FOLDING_WIDTH;
    folding_offset_x = foldingOffset();
    folding_width = extra_zone_width - folding_offset_x;
}

void CodeEditor::updateExtraArea(const QRect & rect, int dy) {
    if (dy)
        extra_area -> scroll(0, dy);
    else
        extra_area -> update(0, rect.y(), extra_area -> width(), rect.height());

    if (rect.contains(viewport() -> rect()))
        updateExtraAreaWidth(0);
}

bool CodeEditor::event(QEvent * event) {
    if (event -> type() == QEvent::ToolTip) {
        QHelpEvent * helpEvent = static_cast<QHelpEvent*>(event);

        QTextCursor cursor = cursorForPosition(helpEvent -> pos() - QPoint(extraAreaWidth(), 0));
        QTextBlock blk = cursor.block();

        //showOverlay(firstVisibleBlock());
//        showOverlay(document() -> findBlockByNumber(60));

        if (blk.isValid()) {
            EDITOR_POS_TYPE pos = cursor.positionInBlock();
            bool tip_is_visible = QToolTip::isVisible();

            BlockUserData * udata = reinterpret_cast<BlockUserData *>(blk.userData());
            if (udata && !udata -> msgs.isEmpty()) {
                int block_num = blk.firstLineNumber();
                QList<MsgInfo> msgs = udata -> msgs;

                for(QList<MsgInfo>::Iterator msg = msgs.begin(); msg != msgs.end(); msg++) {
                    if ((*msg).pos <= pos && ((*msg).pos + (EDITOR_POS_TYPE)(*msg).length) > pos) {
                        // ignore showing of tooltips if its exactly shown for this msg
                        if (tooplip_block_num == block_num && tooplip_block_pos == (*msg).pos)
                            return true;

                        if (tip_is_visible) { // the tooltip is not moving if the text is not changing
                            if (QToolTip::text() == (*msg).msg)
                                QToolTip::showText(helpEvent -> globalPos(), QString("+"));
                        }

                        QToolTip::showText(helpEvent -> globalPos(), (*msg).msg);
                        tooplip_block_num = block_num;
                        tooplip_block_pos = (*msg).pos;
                        return true;
                    }
                }
            }
        }

        QToolTip::hideText();
        tooplip_block_num = -1;
        event -> ignore();
        return true;
    }

    return QPlainTextEdit::event(event);
}

void CodeEditor::paintEvent(QPaintEvent * e) {
    hideOverlayIfNoNeed();

    QPainter painter(viewport());

    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QColor::fromRgb(218, 206, 26, 224));
    painter.setBrush(QColor::fromRgb(255, 239, 11, 192));
    painter.drawRoundedRect(textRect(document() -> findBlockByNumber(16), 76, 5), 3, 3);
    painter.restore();

    painter.save();

    QPlainTextEdit::paintEvent(e);

    painter.restore();

    if (lineWrapMode() == NoWrap) {
        painter.setPen(QColor::fromRgb(192, 192, 192, 72));
        int x = round(symbol_width * CHARS_AMOUNT_LINE) + contentOffset().rx() + document() -> documentMargin();

        painter.drawLine(x, 0, x, height());
    }

/////////// HIGHLIGHT BLOCKS ////////////////

//    if (!d->m_highlightBlocksInfo.isEmpty()) {
//        const QColor baseColor = palette().base().color();

//        // extra pass for the block highlight

//        const int margin = 5;
//        QTextBlock blockFP = block;
//        QPointF offsetFP = offset;
//        while (blockFP.isValid()) {
//            QRectF r = blockBoundingRect(blockFP).translated(offsetFP);

//            int n = blockFP.blockNumber();
//            int depth = 0;
//            foreach (int i, d->m_highlightBlocksInfo.open)
//                if (n >= i)
//                    ++depth;
//            foreach (int i, d->m_highlightBlocksInfo.close)
//                if (n > i)
//                    --depth;

//            int count = d->m_highlightBlocksInfo.count();
//            if (count) {
//                for (int i = 0; i <= depth; ++i) {
//                    const QColor &blendedColor = calcBlendColor(baseColor, i, count);
//                    int vi = i > 0 ? d->m_highlightBlocksInfo.visualIndent.at(i-1) : 0;
//                    QRectF oneRect = r;
//                    oneRect.setWidth(qMax(viewport()->width(), documentWidth));
//                    oneRect.adjust(vi, 0, 0, 0);
//                    if (oneRect.left() >= oneRect.right())
//                        continue;
//                    if (lineX > 0 && oneRect.left() < lineX && oneRect.right() > lineX) {
//                        QRectF otherRect = r;
//                        otherRect.setLeft(lineX + 1);
//                        otherRect.setRight(oneRect.right());
//                        oneRect.setRight(lineX - 1);
//                        painter.fillRect(otherRect, blendedColor);
//                    }
//                    painter.fillRect(oneRect, blendedColor);
//                }
//            }
//            offsetFP.ry() += r.height();

//            if (offsetFP.y() > viewportRect.height() + margin)
//                break;

//            blockFP = blockFP.next();
//            if (!blockFP.isVisible()) {
//                // invisible blocks do have zero line count
//                blockFP = doc->findBlockByLineNumber(blockFP.firstLineNumber());
//            }
//        }
//    }
//////////////////////////////////////////////////////////////////

//////////////// DRAW OVERLAYS
//    if (!d->m_findScopeStart.isNull() && d->m_findScopeVerticalBlockSelectionFirstColumn < 0) {

//        TextEditorOverlay *overlay = new TextEditorOverlay(this);
//        overlay->addOverlaySelection(d->m_findScopeStart.position(),
//                                     d->m_findScopeEnd.position(),
//                                     searchScopeFormat.foreground().color(),
//                                     searchScopeFormat.background().color(),
//                                     TextEditorOverlay::ExpandBegin);
//        overlay->setAlpha(false);
//        overlay->paint(&painter, e->rect());
//        delete overlay;
//    }
/// //////////////////////////////////

    // TODO: need to use correct text block
//    showFoldingContentPopup(document() -> findBlockByNumber(60));
}

void CodeEditor::resizeEvent(QResizeEvent * e) {
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    extra_area -> setGeometry(QRect(cr.left(), cr.top(), extraAreaWidth(), cr.height()));
}

void CodeEditor::keyPressEvent(QKeyEvent * e) {
//    qDebug() << "KEY PRESSED:" << ((Qt::Key)e -> key());

    int curr_key = e -> key();

    if (completer && completer -> popup() -> isVisible()) {
        switch (curr_key) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
                e -> ignore();
                return; // let the completer do default behavior
            default: break;
        }
    }

    switch (curr_key) {
        case Qt::Key_Tab: { procSelectionIndent(); break;}
        case Qt::Key_Backtab: { procSelectionIndent(false); break; }

        case Qt::Key_Escape: // ignore non printable keys
        case Qt::Key_CapsLock:
        case Qt::Key_NumLock:
        case Qt::Key_ScrollLock:
        case Qt::Key_Meta:
        case Qt::Key_Alt:
        case Qt::Key_Shift:
        case Qt::Key_Control: { QPlainTextEdit::keyPressEvent(e); break;}

        case Qt::Key_Return: { emit wrapper -> enterPressed(); }
        default: {
            if (!completer) {
                QPlainTextEdit::keyPressEvent(e);
                return;
            }

            bool has_modifiers = e -> modifiers() != Qt::NoModifier;
            bool is_shortcut = has_modifiers && (e -> modifiers() & Qt::ControlModifier) && curr_key == Qt::Key_Space;

            if (!is_shortcut)
                QPlainTextEdit::keyPressEvent(e);

            if (completer -> popup() -> isHidden()) { // ignore showing of suggestions for action keys
                if (curr_key < Qt::Key_Space || curr_key > Qt::Key_ydiaeresis)
                    return;
            }

            QTextCursor tc = textCursor();
            bool has_selection = tc.hasSelection();

            QString completion_prefix = wordUnderCursor(tc, wuco_before_caret_part);
            QString text(wordUnderCursor(tc, wuco_full));

            if (is_shortcut && has_selection) {
                completer -> setCompletionPrefix(QString());
                completer -> popup() -> setCurrentIndex(
                    completer -> completionModel() -> index(0, 0)
                );
            } else {
                if (
                    !is_shortcut &&
                        (
                            has_modifiers || text.isEmpty() ||
                            //completion_prefix.length() < 3 ||
                            word_boundary.contains(text.right(1))
                        )
                    )
                {
                    completer -> popup() -> hide();
                    return;
                }

                if (completion_prefix != completer -> completionPrefix()) {
                    completer -> setCompletionPrefix(completion_prefix);
                    completer -> popup() -> setCurrentIndex(
                        completer -> completionModel() -> index(0, 0)
                    );
                }
            }

            if (is_shortcut && completer -> completionCount() == 1 && completion_prefix == text) {
                applyCompletion(completer -> currentCompletion());
            } else {
                QRect cr = cursorRect();
                cr.setLeft(cr.left() + extra_area -> width());
                cr.setWidth(
                    completer -> popup() -> sizeHintForColumn(0) +
                        completer -> popup() -> verticalScrollBar() -> sizeHint().width()
                );

                completer -> complete(cr);
            }
        }
    }
}

void CodeEditor::wheelEvent(QWheelEvent * e) {
    if (e -> modifiers() & Qt::ControlModifier) {
        const float delta = e -> angleDelta().y();

        if (delta > 0)
            zoomIn(4);
        else
            zoomOut(4);

        setFont(font());
        e -> accept();
        return;
    }

    QPlainTextEdit::wheelEvent(e);
}

void CodeEditor::focusInEvent(QFocusEvent * e) {
    if (completer)
        completer -> setWidget(this);

    QPlainTextEdit::focusInEvent(e);
}

void CodeEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extra_selections;

    QTextCursor cursor = textCursor();
    curr_block_number = cursor.blockNumber();

    emit cursorPosChanged(QStringLiteral("Line: %1, Col: %2").arg(curr_block_number + 1).arg(cursor.positionInBlock()));

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = currentLineColor();

        QTextBlock origin_block = cursor.block();

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);

        selection.cursor = cursor;
        selection.cursor.clearSelection();
        extra_selections.append(selection);

        if (wordWrapMode() != QTextOption::NoWrap) {
            int offset = 0;

            while(true) {
                if (cursor.movePosition(QTextCursor::Down) && origin_block == cursor.block()) {
                    ++offset;
                    selection.cursor = cursor;
                    extra_selections.append(selection);
                }
                else break;
            }

            if (offset != 0)
                cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, offset);

            while(true) {
                if (cursor.movePosition(QTextCursor::Up) && origin_block == cursor.block()) {
                    selection.cursor = cursor;
                    extra_selections.append(selection);
                }
                else break;
            }
        }

        for(QTextBlock::iterator it = origin_block.begin(); it != origin_block.end(); it++) {
            QTextFragment fragment = it.fragment();

            selection.cursor.setPosition(fragment.position());
            selection.cursor.setPosition(fragment.position() + fragment.length(), QTextCursor::KeepAnchor);
            selection.format = fragment.charFormat();
            extra_selections.append(selection);
        }
    }

    setExtraSelections(extra_selections);
}

void CodeEditor::extraAreaMouseEvent(QMouseEvent * event) {
    int folding_offset = foldingOffset();
    int x = event -> x();

    folding_y =
        x >= folding_offset && x < extra_area -> width() - HPADDING ?
            event -> y() : NO_FOLDING;

    switch(event -> type()) {
        case QEvent::MouseMove: {

        break;}

        case QEvent::MouseButtonPress: {
            if (event -> button() == Qt::LeftButton) {
                if (folding_y != NO_FOLDING) {
                    QTextCursor cursor = cursorForPosition(QPoint(1, folding_y));
                    QTextBlock blk = cursor.block();

                    if (blk.isValid()) {
                        BlockUserData * user_data = static_cast<BlockUserData *>(blk.userData());
                        DATA_FLAGS_TYPE folding_flags = user_data ? user_data -> foldingState() : 0;

                        if (folding_flags) {
                            user_data -> invertFoldingState();

                            bool show_blocks = (folding_flags & BlockUserData::udf_folding_opened) != BlockUserData::udf_folding_opened;
                            EDITOR_POS_TYPE lines_coverage = user_data -> para_control -> linesCoverage();
                            EDITOR_POS_TYPE start = blk.position() + blk.length();
                            EDITOR_LEN_TYPE chars = 0;

                            while(--lines_coverage >= 0) {
                                blk = blk.next();

//                                if (!blk.isValid())
//                                    break;

                                blk.setVisible(show_blocks);
                                chars += blk.length();
                            }

                            document() -> markContentsDirty(start, chars);
                        }
                    }
                }
            }
        break;}

//        case QEvent::MouseButtonRelease: {
//            return;
//        break;}

//        case QEvent::MouseButtonDblClick: {
//            return;
//        break;}

        default:
//            event -> ignore();
            return;
    }

    event -> accept();
    update();
}

void CodeEditor::extraAreaLeaveEvent(QEvent *) {
    // fake missing mouse move event from Qt
    QMouseEvent me(QEvent::MouseMove, QPoint(-1, -1), Qt::NoButton, 0, 0);
    extraAreaMouseEvent(&me);
}

void CodeEditor::extraAreaPaintEvent(QPaintEvent * event) {
    hideOverlayIfNoNeed();
//    bool is_caret_redrawing = height() - event -> rect().height() > 8;

    QPainter painter(extra_area);
    QTextBlock block = firstVisibleBlock();
    int screen_end_block_num = block.blockNumber();
    EDITOR_POS_TYPE folding_lines_coverage = 0;

    QRectF block_geometry_rect = blockBoundingGeometry(block).translated(contentOffset());

    int top = block_geometry_rect.top();
    int bottom = block_geometry_rect.bottom();

    int rect_top = event -> rect().top();
    int rect_bottom = event -> rect().bottom();

    while (block.isValid() && top <= rect_bottom) {
        if (block.isVisible() && bottom >= rect_top)
            extraAreaPaintBlock(painter, block, top, top, bottom, screen_end_block_num, folding_lines_coverage);

        block = block.next();
        top = bottom;
        bottom = top + (int)blockBoundingRect(block).height();
        ++screen_end_block_num;
    }

    event -> accept();
}

void CodeEditor::paintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom, EDITOR_POS_TYPE & folding_lines_coverage) {
    painter.save();

    painter.setRenderHint(QPainter::Antialiasing);

    int block_height = block_bottom - block_top;

    painter.fillRect(0, paint_top, extra_zone_width, block_height + 1, QColor::fromRgb(172, 229, 238));

    painter.translate(QPoint(1, 0));
    block.layout() -> draw(&painter, QPoint(extra_zone_width + contentOffset().rx(), paint_top));

    extraAreaPaintBlock(painter, block, paint_top, block_top, block_bottom, block.blockNumber(), folding_lines_coverage);

    painter.setRenderHint(QPainter::Antialiasing, false);

    painter.setPen(extra_area -> borderColor());
    painter.drawLine(extra_zone_width - 1, paint_top, extra_zone_width - 1, paint_top + block_height + 1);

    painter.restore();
}

void CodeEditor::extraAreaPaintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom, const EDITOR_POS_TYPE & block_num, EDITOR_POS_TYPE & folding_lines_coverage) {
    bool is_current = curr_block_number == block_num;

    if (is_current)
        painter.fillRect(0, paint_top, extra_zone_width, block_bottom - block_top, currentLineColor(48));

    BlockUserData * user_data = static_cast<BlockUserData *>(block.userData());
    DATA_FLAGS_TYPE folding_flags = user_data ? user_data -> foldingState() : 0;

    bool on_block = folding_y > 0 && folding_y > block_top && folding_y < block_bottom;

    if (folding_flags) {
        if (on_block) {
            folding_flags |= BlockUserData::udf_folding_hovered;

            if ((folding_flags & BlockUserData::udf_folding_opened) == BlockUserData::udf_folding_opened) {
                hideOverlay();

                if (!folding_lines_coverage)
                    folding_lines_coverage = user_data -> para_control -> linesCoverage() + 1;
            }
            else showFoldingContentPopup(block);
        }

        painter.drawPixmap(
            folding_offset_x,
            paint_top + (line_number_height - FOLDING_WIDTH) / 2,
            FOLDING_WIDTH,
            FOLDING_WIDTH,
            icons[folding_flags]
        );
    } else if (on_block)
        hideOverlay();

    if (folding_lines_coverage > 0) {
        painter.fillRect(folding_offset_x, paint_top, folding_width, block_bottom - block_top, foldingColor());

        --folding_lines_coverage;
    }

    painter.setFont(is_current ? curr_line_font : font());
    painter.drawText(
        0, paint_top, line_number_width, line_number_height, Qt::AlignRight, QString::number(block_num + 1)
    );
}

void CodeEditor::showFoldingContentPopup(const QTextBlock & block) {
    QRect parent_block_rect = blockBoundingGeometry(block).translated(contentOffset()).toRect();

    if (!rectOnScreen(parent_block_rect)) {
        return;
    }

    EDITOR_POS_TYPE uid = block.blockNumber();

    if (overlay -> shownFor(true, 0, uid))
        return;

    QRect popup_rect(parent_block_rect.topLeft(), size());

    int view_height = height();
    int rel_pos = view_height - parent_block_rect.top();

    qreal potential_height = 0;

    if (rel_pos >= view_height / 2) {
        popup_rect.translate(0, line_number_height + 2);
        potential_height = rel_pos - line_number_height - 3;
    }
    else {
        potential_height = parent_block_rect.top() - contentOffset().ry() - 1;
        popup_rect.translate(0, -potential_height);
    }

    popup_rect.translate(mapToGlobal(rect().topLeft()));
    popup_rect.setHeight(potential_height);
    popup_rect.setWidth(widthWithoutScroll());


    QPixmap pixmap(popup_rect.size());
    pixmap.fill(palette().base().color().darker(105));

    {
        QPainter painter(&pixmap);

        QTextBlock b = block.next();

        if (b.isVisible()) // ignore showing of not hidden items
            return;

        QPointF offset(0, 0);
        EDITOR_POS_TYPE folding_lines_coverage = -1;

        while (!b.isVisible() && potential_height > 0) {
            b.setVisible(true); // make sure block bounding rect works

            QRectF bl_geometry_rect = blockBoundingRect(b).translated(offset);

            paintBlock(painter, b, offset.ry(), bl_geometry_rect.top(), bl_geometry_rect.bottom(), folding_lines_coverage);

            offset.ry() += bl_geometry_rect.height();
            potential_height -= bl_geometry_rect.height();

            b.setVisible(false);
            b.setLineCount(0);

            b = b.next();
        }

        //    painter.setRenderHint(QPainter::Antialiasing, true);
            ////    painter.translate(.5, .5);

            ////    painter.setBrush(brush);
            ////    painter.drawRoundedRect(popup_rect, 3, 3);

        //    painter.drawLine(0, 0, pixmap.width(), 0);
        //    painter.drawLine(pixmap.height() - 1, 0, pixmap.width(), pixmap.height() - 1);
    }

    if (potential_height > 0) {
        popup_rect.setHeight(popup_rect.height() - potential_height);
        pixmap = pixmap.copy(0, 0, pixmap.width(), popup_rect.height());
    }

    showOverlay(popup_rect, pixmap, uid);
}

void CodeEditor::prepareIcons(const uint & size) {
    icons.insert(
        BlockUserData::udf_has_folding,
        PREPARE_PIXMAP(QStringLiteral(":/folding_close"), size)
    );

    icons.insert(
        BlockUserData::udf_has_folding | BlockUserData::udf_folding_hovered,
        PREPARE_PIXMAP(QStringLiteral(":/folding_close_hover"), size)
    );

    icons.insert(
        BlockUserData::udf_folding_opened,
        PREPARE_PIXMAP(QStringLiteral(":/folding_open"), size)
    );

    icons.insert(
        BlockUserData::udf_folding_opened | BlockUserData::udf_folding_hovered,
        PREPARE_PIXMAP(QStringLiteral(":/folding_open_hover"), size)
    );
}

int CodeEditor::widthWithoutScroll() {
    return width() - (verticalScrollBar() -> isVisible() ? verticalScrollBar() -> width() : 0);
}

void CodeEditor::showOverlay(const QRect & rect, const QPixmap & overlay_img, const qint32 & subuid) {
    overlay -> registerShowing(true, 0, subuid);
    overlay -> showInfo(rect, overlay_img);
}

void CodeEditor::showOverlay(const QTextBlock & block) {
    if (blockOnScreen(block)) {
        hideOverlay();
        return;
    }  

    EDITOR_POS_TYPE block_number = block.blockNumber();

    OverlayInfo::OverlayPos overlay_pos =
        textCursor().blockNumber() < block_number ? OverlayInfo::op_bottom : OverlayInfo::op_top;

    if (overlay -> shownFor(false, overlay_pos, block_number))
        return;

    QRect bl_geometry_rect = blockBoundingGeometry(block).translated(contentOffset()).toRect();
    bl_geometry_rect.setWidth(widthWithoutScroll());

    if (overlay_pos == OverlayInfo::op_top) {
        int height_limit = line_number_height * 3 + 3;

        if (bl_geometry_rect.height() > height_limit) {
            bl_geometry_rect.setHeight(height_limit);
        }
    }

    QPixmap pixmap(bl_geometry_rect.size());
    pixmap.fill(palette().base().color());

    QPainter painter(&pixmap);
    EDITOR_POS_TYPE folding_lines_coverage = -1;

    paintBlock(painter, block, 0, bl_geometry_rect.top(), bl_geometry_rect.bottom(), folding_lines_coverage);

    overlay -> registerShowing(false, overlay_pos, block_number);
    overlay -> showInfo(this, pixmap, overlay_pos);
}

void CodeEditor::hideOverlay() {
    if (overlay) overlay -> hide();
}

void CodeEditor::hideOverlayIfNoNeed() {
    if (extra_overlay_block_num == -1 && folding_y == NO_FOLDING && folding_overlay_y == NO_FOLDING)
        hideOverlay();
}

bool CodeEditor::rectOnScreen(const QRect & r) {
    int view_height = height();
    int rel_pos = view_height - r.top();
    return (rel_pos > line_number_height / 2) && (rel_pos <= view_height);
}

bool CodeEditor::blockOnScreen(const QTextBlock & block) {
    return rectOnScreen(blockBoundingGeometry(block).translated(contentOffset()).toRect());
}

QRect CodeEditor::textRect(const QTextBlock & block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length) {
    if (!block.isValid())
        return QRect();

    QTextLine line = block.layout() -> lineForTextPosition(pos);

    if (!line.isValid())
        return QRect();

    qreal x_offset = -horizontalScrollBar() -> value();
    QRectF rect = blockBoundingGeometry(block).translated(contentOffset());
    rect.setLeft(line.cursorToX(pos) + x_offset);
    rect.setRight(line.cursorToX(pos + length) + x_offset);

    return rect.toRect();
}

QString CodeEditor::wordUnderCursor(QTextCursor & tc, const WordUnderCursorOps & flags) {
    QTextBlock block = tc.block();
    const int pos = tc.positionInBlock();
    const int start_pos = block.position();
    const int end_pos = block.length() - 1;
    const QString block_text = block.text();

    if (block_text.isEmpty())
        return block_text;

    int offset = 0;
    for(int iter = pos - 1; iter >= 0; --iter, ++offset) {
        if (word_boundary.contains(block_text[iter]))
            break;
    }

    if (flags & wuco_before_caret_part)
        tc.setPosition(start_pos + pos - offset, QTextCursor::KeepAnchor);
    else {
        tc.setPosition(start_pos + pos - offset, QTextCursor::MoveAnchor);

        offset = 0;
        for(int iter = pos; iter < end_pos; ++iter, ++offset) {
            if (word_boundary.contains(block_text[iter]))
                break;
        }

        tc.setPosition(start_pos + pos + offset, QTextCursor::KeepAnchor);
    }

    if (flags & wuco_remove) {
        QString res(tc.selectedText());
        tc.removeSelectedText();
        return res;
    }
    else {
        if (flags & wuco_select)
            setTextCursor(tc);
        return tc.selectedText();
    }
}

void CodeEditor::applyCompletion(const QString & completion) {
    if (completer -> widget() != this) return;

    QTextCursor tc = textCursor();

    if (tc.hasSelection()) {
        tc.removeSelectedText();
//        wordUnderCursor(tc, wuco_remove_full);
//        tc.insertText(completion);
    }/* else {
        int extra = completion.length() - completer -> completionPrefix().length();
    //    tc.movePosition(QTextCursor::Left);
//        tc.movePosition(QTextCursor::EndOfWord);
        tc.insertText(completion.right(extra));
    }*/

    wordUnderCursor(tc, wuco_remove_full);
    tc.insertText(completion);

    completer -> popup() -> setCurrentIndex(
        completer -> completionModel() -> index(0, 0)
    );
}

void CodeEditor::procSelectionIndent(const bool & right) {
    QTextCursor curs = textCursor();
    const QString tab_space = document() -> property("tab_space").toString();
    const int tab_space_length = tab_space.length();

    if(!curs.hasSelection()) {
        if (right)
            curs.insertText(tab_space);
        else {
            curs.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
            curs.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, tab_space_length);

            if (curs.selectedText() == tab_space)
                curs.removeSelectedText();
            else {
                curs.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
                for(int i = 0; i < tab_space_length - 1; i++) {
                    curs.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
                    if (curs.selectedText()[0] == tab_space[0])
                        curs.removeSelectedText();
                    else break;
                }
            }
        }
        return;
    }

    int spos = curs.anchor();
    int epos = curs.position();

    if (spos > epos)
        std::swap(spos, epos);

    curs.setPosition(epos, QTextCursor::MoveAnchor);
    int eblock = curs.block().blockNumber();

    curs.setPosition(spos, QTextCursor::MoveAnchor);
    int sblock = curs.block().blockNumber();

    const int block_diff = eblock - sblock;

    curs.beginEditBlock();

    for(int i = 0; i <= block_diff; ++i) {
        curs.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);

        if (!right) {
            curs.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, tab_space_length);

            if (curs.selectedText() == tab_space)
                curs.removeSelectedText();
            else {
                curs.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
                for(int i = 0; i < tab_space_length - 1; i++) {
                    curs.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
                    if (curs.selectedText()[0] == tab_space[0])
                        curs.removeSelectedText();
                    else break;
                }
            }
        }
        else curs.insertText(tab_space);

        curs.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
    }

    curs.endEditBlock();
}
