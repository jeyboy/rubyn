#include "code_editor.h"

#include <qstringbuilder.h>
#include <qwidget.h>
#include <qtextobject.h>
#include <qpainter.h>
#include <qfile.h>
#include <qscrollbar.h>
#include <qtooltip.h>

#include "project/file.h"

#include "editor/code_editor_cache.h"
#include "editor/block_user_data.h"
#include "editor/parts/overlay_info.h"
#include "editor/parts/extra_area.h"
#include "editor/document_types/text_document.h"

#include "controls/logger.h"
#include "controls/completer.h"

#include "highlighter/highlight_format_factory.h"

//qApp->setCursorFlashTime(0);


//    QTextCursor cursor = ui->textEdit->textCursor();
//    ui->textEdit->selectAll();
//    ui->textEdit->setFontPointSize(32);
//    ui->textEdit->setTextCursor( cursor );


//You can use QTextCharFormat to set the color of the text in your QPlainTextEdit. Use the QTextCharFormat::setForeground to set the color. Then use a stylesheet to change the color of the cursor by using the color property.

//QPlainTextEdit *p_textEdit = new QPlainTextEdit;
//p_textEdit->setStyleSheet("QPlainTextEdit{color: #ffff00; background-color: #303030;"
//                          " selection-background-color: #606060; selection-color: #ffffff;}");
//QTextCharFormat fmt;
//fmt.setForeground(QBrush(QColor(255,255,255)));
//p_textEdit->mergeCurrentCharFormat(fmt);

CodeEditor::CodeEditor(QWidget * parent) : QPlainTextEdit(parent), completer(nullptr), wrapper(nullptr),
    tooplip_block_num(NO_INFO), tooplip_block_pos(NO_INFO),
    can_show_folding_popup(true), folding_click(false), folding_y(NO_FOLDING), folding_overlay_y(NO_FOLDING),
    curr_block_number(NO_INFO), show_folding_scope_lines(false), show_folding_content_on_hover_overlay(false),
    unfold_on_click_overlay(false), show_foldings_panel(false), show_breakpoints_panel(false), show_extra_icons(false)
{
    overlays.insert(OverlayInfo::ol_bottom, new OverlayInfo(OverlayInfo::ol_bottom));
    overlays.insert(OverlayInfo::ol_top, new OverlayInfo(OverlayInfo::ol_top));
    overlays.insert(OverlayInfo::ol_hover, new OverlayInfo(OverlayInfo::ol_hover));

    connect(overlays[OverlayInfo::ol_bottom], &OverlayInfo::hidden, this, &CodeEditor::overlayHidden);
    connect(overlays[OverlayInfo::ol_top], &OverlayInfo::hidden, this, &CodeEditor::overlayHidden);
    connect(overlays[OverlayInfo::ol_hover], &OverlayInfo::hidden, this, &CodeEditor::overlayHidden);

    extra_area = new ExtraArea(this);
    display_cacher = new CodeEditorCache();

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateExtraAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateExtraArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::cursorMoved);

    updateExtraAreaWidth(0);

    setCharsLimiterLineAt(80);

//    setCursorWidth(8);
    setLineWrapMode(NoWrap);

    verticalScrollBar() -> setSingleStep(2);

    setMouseTracking(true);

    prepareIcons();
}

CodeEditor::~CodeEditor() {
    icons.clear();

    delete display_cacher;
    qDeleteAll(overlays);
}

void CodeEditor::setCompleter(Completer * new_completer) {
    if (completer)
        QObject::disconnect(completer, nullptr, this, nullptr);

    completer = new_completer;

    if (!completer)
        return;

    completer -> setWidget(this);
    completer -> setCompletionMode(QCompleter::PopupCompletion);
    completer -> setCaseSensitivity(Qt::CaseInsensitive);

    connect(completer, SIGNAL(activated(QString)), this, SLOT(applyCompletion(QString)));
}

void CodeEditor::openDocument(File * file) {
    if (file && file -> isText()) {
        QFont new_font(font().family(), 11);
        new_font.setKerning(true);
//        new_font.setLetterSpacing(QFont::AbsoluteSpacing, cursorWidth() - 1);
//        new_font.setStretch(90);

        QScrollBar * vscroll = verticalScrollBar();

        if (wrapper) {
            disconnect(this, SIGNAL(modificationChanged(bool)), wrapper, SLOT(hasUnsavedChanges(const bool &)));

            if (display_cacher -> size() > 0) {
                wrapper -> setVerticalScrollPos(vscroll -> value());
                if (display_cacher -> isShowOverlay())
                    hideOverlays();
            }
        }

        wrapper = file -> asText();

        change_scroll_pos_required = wrapper -> verticalScrollPos(false) > 0;

        QTextDocument * text_doc = wrapper -> toQDoc();

//        text_doc -> setUseDesignMetrics(true);

        text_doc -> setDefaultFont(new_font);
        setFont(new_font);

        text_doc -> setUndoRedoEnabled(false);
        setDocumentTitle(file -> name());
        setDocument(text_doc);
        text_doc -> setUndoRedoEnabled(true);

        connect(this, SIGNAL(modificationChanged(bool)), wrapper, SLOT(hasUnsavedChanges(const bool &)));

        show_foldings_panel = wrapper -> canHasFoldings();
        show_breakpoints_panel = wrapper -> canHasBreakpoints();
        show_extra_icons = false;

        updateExtraAreaWidth(0);
        setShowSpacesAndTabs(true);
        setShowFoldingScopeLines(true);
        setShowFoldingContentOnHoverOverlay(true);
        setUnfoldOnClickOverlay(true);

//        if (!file -> isFullyReaded()) {
//            //    verticalScrollBar()
//        }
    }
    // else inform user about fail
}

const QString & CodeEditor::documentUid() {
    return wrapper -> documentUid();
}

void CodeEditor::setFont(const QFont & font) {
    curr_line_font = QFont(font.family(), font.pointSize());
    curr_line_font.setUnderline(true);
    curr_line_font.setBold(true);

    QPlainTextEdit::setFont(font);

    line_number_height = fontMetrics().height();

    symbol_width = QFontMetricsF(font).averageCharWidth();

    pseudo_tab_width = static_cast<int>(symbol_width * wrapper -> tabSpace().size());

    setCharsLimiterLineAt(chars_limit_line);
}

void CodeEditor::setCharsLimiterLineAt(const uint & char_pos) {
    chars_limit_line = char_pos;
    chars_limit_offset_x = round(symbol_width * chars_limit_line);

    update();
}

///////////////////////// PROTECTED ///////////////////////

void CodeEditor::fillBackground(QPainter * p, const QRectF & rect, QBrush brush, const QRectF & gradientRect) {
    p -> save();

    if (brush.style() >= Qt::LinearGradientPattern && brush.style() <= Qt::ConicalGradientPattern) {
        if (!gradientRect.isNull()) {
            QTransform m = QTransform::fromTranslate(gradientRect.left(), gradientRect.top());
            m.scale(gradientRect.width(), gradientRect.height());
            brush.setTransform(m);
            const_cast<QGradient *>(brush.gradient()) -> setCoordinateMode(QGradient::LogicalMode);
        }
    } else {
        p -> setBrushOrigin(rect.topLeft());
    }

    p -> fillRect(rect, brush);

    p -> restore();
}

void CodeEditor::procRevision() {
    int doc_revision = document() -> revision();

    if (doc_revision != wrapper -> revision()) {
        wrapper -> setRevision(doc_revision);
        emit modificationChanged(true);
    }
}

void CodeEditor::imitateClick() {
    highlightCurrentLine();
    cursorMoved();
}

void CodeEditor::prepareIcons(const int & size) {
    icons.insert(
        BlockUserData::udf_folded,
        PREPARE_PIXMAP(QStringLiteral(":/folding_close"), size)
    );

    icons.insert(
        BlockUserData::udf_folded | BlockUserData::udf_folding_hovered,
        PREPARE_PIXMAP(QStringLiteral(":/folding_close_hover"), size)
    );

    icons.insert(
        BlockUserData::udf_unfolded,
        PREPARE_PIXMAP(QStringLiteral(":/folding_open"), size)
    );

    icons.insert(
        BlockUserData::udf_unfolded | BlockUserData::udf_folding_hovered,
        PREPARE_PIXMAP(QStringLiteral(":/folding_open_hover"), size)
    );

    icons.insert(
        BlockUserData::udf_has_breakpoint,
        PREPARE_PIXMAP(QStringLiteral(":/breakpoint"), size)
    );
}

int CodeEditor::widthWithoutScroll() {
    return width() - (verticalScrollBar() -> isVisible() ? verticalScrollBar() -> width() : 0);
}


void CodeEditor::paintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom) {
    painter.save();

    painter.setRenderHint(QPainter::Antialiasing);

    int block_height = block_bottom - block_top;

//    const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(hid_folding_content_popup);
//    painter.fillRect(0, paint_top, extra_zone_width, block_height + 1, format.background());

    painter.translate(QPoint(1, 0));
    block.layout() -> draw(&painter, QPoint(extra_zone_width + contentOffset().rx(), paint_top));

    extraAreaPaintBlock(painter, block, paint_top, block_top, block_bottom, block.blockNumber());

    painter.setRenderHint(QPainter::Antialiasing, false);

    //TODO: move border color to HighlightFormatFactory
    painter.setPen(extra_area -> borderColor());
    painter.drawLine(extra_zone_width - 1, paint_top, extra_zone_width - 1, paint_top + block_height + 1);

    painter.restore();
}

void CodeEditor::extraAreaPaintBlock(QPainter & painter, CodeEditorCacheCell * cache) {
    bool is_current = curr_block_number == cache -> block_number;

    int block_top = cache -> bounding_rect.top();
    int block_bottom = cache -> bounding_rect.bottom();

    if (is_current) {
        const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(hid_current_line_extra);
        painter.fillRect(0, block_top, extra_zone_width, cache -> bounding_rect.height(), format.background());
    }

    bool on_block = folding_y != NO_FOLDING && folding_y > block_top && folding_y < block_bottom;
    bool initiated = false;

    if (on_block) {
        curr_folding_limits.rx() = block_top;
        curr_folding_limits.ry() = block_bottom;
    }

    BlockUserData * user_data = cache -> user_data;

    if (show_foldings_panel) {
        DATA_FLAGS_TYPE folding_flags = user_data ? user_data -> foldingState() : 0;

        if (folding_flags) {
            if (user_data -> para_control && !user_data -> para_control -> is_oneliner) {
                bool folded = user_data -> isFolded();

                if (on_block) {
                    folding_flags |= BlockUserData::udf_folding_hovered;

                    if (folded) {
                        if (folding_click) {
                            folding_click = false;
                        }
                        else if (can_show_folding_popup)
                            showFoldingContentPopup(document() -> findBlockByNumber(cache -> block_number));
                    }
                    else {
                        active_folding.level = user_data -> level;
                        active_folding.start_block_num = cache -> block_number;
                        active_folding.end_block_num = NO_INFO - (user_data -> para_control -> is_blockator ? 0 : 1);
                        initiated = true;
                    }
                }

                painter.drawPixmap(
                    QPoint(folding_offset_x, block_top + (line_number_height - ICO_WIDTH) / 2),
                    icons[folding_flags]
                );
            }
        }
    }

    if (user_data) {
//        ////////////////////////////// TEST /////////////////
//        painter.drawText(
//            breakpoint_offset_x, block_top, breakpoint_width, line_number_height, Qt::AlignRight, QString::number(user_data -> level)
//        );
//        ////////////////////////////// END TEST /////////////////

        if (show_foldings_panel) {
            if (!initiated && active_folding.end_block_num < 0 && user_data -> level <= active_folding.level)
                active_folding.end_block_num += cache -> block_number + 1;

            if (active_folding.containsBlockNumber(cache -> block_number)) {
                const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(hid_folding_hover_range);
                painter.setPen(format.foreground().color());
                painter.fillRect(folding_offset_x, block_top, folding_width, block_bottom - block_top, format.background());
            }
        }

        if (show_breakpoints_panel && user_data -> hasBreakpoint()) {
            painter.drawPixmap(
                QPoint(breakpoint_offset_x, block_top + (line_number_height - ICO_WIDTH) / 2),
                icons[BlockUserData::udf_has_breakpoint]
            );

            const QTextCharFormat & breakpoint_line_format = HighlightFormatFactory::obj().getFormatFor(hid_breakpoint_line);
            painter.fillRect(breakpoint_offset_x, block_top, extra_zone_width, block_bottom - block_top, breakpoint_line_format.background());
        }
    }

    if (show_foldings_panel && para_info.containsBlockNumber(cache -> block_number)) {
        const QTextCharFormat & scope_format = HighlightFormatFactory::obj().getFormatFor(hid_folding_para_range);
        painter.fillRect(folding_scope_offset_x, block_top, folding_scope_width, block_bottom - block_top, scope_format.background());
    }

    painter.setFont(is_current ? curr_line_font : font());
    painter.drawText(
        line_number_offset_x, block_top, line_number_width, line_number_height, Qt::AlignRight, QString::number(cache -> block_number + 1)
    );
}

void CodeEditor::extraAreaPaintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom, const EDITOR_POS_TYPE & block_num) {
    BlockUserData * user_data = TextDocumentLayout::getUserDataForBlock(block);

    if (show_foldings_panel) {
        DATA_FLAGS_TYPE folding_flags = user_data ? user_data -> foldingState() : 0;

        if (folding_flags) {
            if (!user_data -> para_control -> is_oneliner) {

                painter.drawPixmap(
                    QPoint(folding_offset_x, paint_top + (line_number_height - ICO_WIDTH) / 2),
                    icons[BlockUserData::udf_unfolded]
                );
            }
        }
    }

    if (user_data) {
        if (show_foldings_panel && active_folding.containsBlockNumber(block_num)) {
            const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(hid_folding_hover_range);
            painter.setPen(format.foreground().color());
            painter.fillRect(folding_offset_x, paint_top, folding_width, block_bottom - block_top, format.background());
        }

        if (show_breakpoints_panel && user_data -> hasBreakpoint()) {
            painter.drawPixmap(
                QPoint(breakpoint_offset_x, paint_top + (line_number_height - ICO_WIDTH) / 2),
                icons[BlockUserData::udf_has_breakpoint]
            );
        }
    }

    if (show_foldings_panel && para_info.containsBlockNumber(block_num)) {
        const QTextCharFormat & scope_format = HighlightFormatFactory::obj().getFormatFor(hid_folding_para_range);
        painter.fillRect(folding_scope_offset_x, paint_top, folding_scope_width, block_bottom - block_top, scope_format.background());
    }

    painter.setFont(font());
    painter.drawText(
        line_number_offset_x, paint_top, line_number_width, line_number_height, Qt::AlignRight, QString::number(block_num + 1)
    );
}


void CodeEditor::drawParaOverlays(QPainter & painter) {
    if (para_info.isValid()) {
        QTextBlock opener_blk = document() -> findBlockByNumber(para_info.start_block_num);
        drawTextOverlay(hid_para_hover_overlay, painter, opener_blk, para_info.opener_pos, para_info.opener_length);

        if (para_info.closer_pos != NO_INFO) {
            QTextBlock closer_blk = para_info.start_block_num == para_info.end_block_num ? opener_blk : document() -> findBlockByNumber(para_info.end_block_num);
            drawTextOverlay(hid_para_hover_overlay, painter, closer_blk, para_info.closer_pos, para_info.closer_length);
        }

        if (alt_para_info.isValid()) {
            QTextBlock opener_blk = document() -> findBlockByNumber(alt_para_info.start_block_num);
            drawTextOverlay(hid_para_hover_overlay2, painter, opener_blk, alt_para_info.opener_pos, alt_para_info.opener_length);

            if (alt_para_info.closer_pos != NO_INFO) {
                QTextBlock closer_blk = alt_para_info.start_block_num == alt_para_info.end_block_num ? opener_blk : document() -> findBlockByNumber(alt_para_info.end_block_num);
                drawTextOverlay(hid_para_hover_overlay2, painter, closer_blk, alt_para_info.closer_pos, alt_para_info.closer_length);
            }
        }
    }
}

void CodeEditor::drawFoldingOverlays(QPainter & painter, const QRect & target_rect) {
    int target_top = target_rect.top();
    int target_bottom = target_rect.bottom();

    for (CodeEditorCacheCell * it = display_cacher -> begin(); !it -> is_service; it = it -> next) {
        if (!it -> is_visible || (!show_folding_content_on_hover_overlay && it -> bounding_rect.bottom() < target_top)) {
            continue;
        }

        if (!show_folding_content_on_hover_overlay && it -> bounding_rect.top() > target_bottom) {
            break;
        }

        if (it -> user_data && it -> user_data -> isFolded()) {
            if (it -> folding_overlay_text.isNull()) {
                wrapper -> paraOpositionStr(it -> user_data -> para_control -> para_type, it -> folding_overlay_text);
                it -> folding_overlay_text = QLatin1Literal("...") % it -> folding_overlay_text;
            }

            EDITOR_POS_TYPE text_pos = it -> block_length - 1;
            it -> folding_description_rect = textRect(it, text_pos, 1);
            it -> folding_description_rect.adjust(3, 0, it -> folding_overlay_text.length() * symbol_width + 10, 0);

            drawTextOverlay(it -> is_folding_selected ? hid_folded_selected_overlay : hid_folded_overlay, painter, it -> folding_description_rect);

            painter.setPen(QColor::fromRgb(0, 0, 0));
            painter.drawText(it -> folding_description_rect, Qt::AlignCenter, it -> folding_overlay_text);
        }
    }
}

void CodeEditor::drawCharsLimiter(QPainter & painter) {
// TODO: optimize me: return if 'x' not on the screen

//    if (lineWrapMode() == NoWrap) {
        painter.save();

        const QTextCharFormat & chars_limiter_format = HighlightFormatFactory::obj().getFormatFor(hid_chars_limiter_line);
        painter.setPen(chars_limiter_format.background().color());
        int x = chars_limit_offset_x + contentOffset().rx() + document() -> documentMargin();

        painter.drawLine(x, 0, x, height());

        painter.restore();
//    }
}

void CodeEditor::drawAdditionalCarets(QPainter & painter) {
//    bool editable = hasFocus() && (!isReadOnly() || (textInteractionFlags() & Qt::TextSelectableByKeyboard));

//    blink = !blink;

//    if (!editable || blink)
//        return;

////    bool drawCursorAsBlock = drawCursor && overwriteMode() ;

//    QTextBlock block = firstVisibleBlock();

//    QTextLayout * layout = block.layout();

//    int cpos = layout -> leftCursorPosition(5);

//    textRect(block, cpos, 1).adjust(-3, -1, 1, 2); // check adjust result! // use this for sending of update events

//    qDebug() << "PO" << cpos << textRect(block, cpos, 1); // QRect(44,4 10x18) // QRect(39,3 11x20)

//    layout -> drawCursor(&painter, contentOffset(), cpos, cursorWidth());
}

void CodeEditor::drawTextOverlay(const UID_TYPE & draw_uid, QPainter & painter, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length) {
    drawTextOverlay(draw_uid, painter, textRect(block, pos, length));
}

void CodeEditor::drawTextOverlay(const UID_TYPE & draw_uid, QPainter & painter, const QRect & fold_rect) {
    painter.save();
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.setRenderHint(QPainter::Antialiasing);

    const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(static_cast<Identifier>(draw_uid));

    painter.setPen(format.foreground().color());
    painter.setBrush(format.background().color());

    painter.drawRoundedRect(fold_rect, 3, 3);
    painter.restore();
}

void CodeEditor::showFoldingContentPopup(const QTextBlock & block) {
    EDITOR_POS_TYPE uid = block.blockNumber();

    if (!display_cacher -> isBlockOnScreen(uid)) {
        return;
    }

    OverlayInfo::OverlayLocation olocation = OverlayInfo::ol_hover;

    if (overlays[olocation] -> shownFor(uid)) {
        return;
    }

    QRect parent_block_rect = blockRect(block).toRect();
    QRect popup_rect(parent_block_rect.topLeft(), size());

    int view_height = height();
    int rel_pos = view_height - parent_block_rect.top();

    int potential_height = rel_pos - line_number_height - 3;
    bool place_after = potential_height >= line_number_height * 3 + 3;

    if (place_after) {
        popup_rect.translate(0, line_number_height + 2);
    }
    else {
        potential_height = parent_block_rect.top() - contentOffset().ry() - 1;
        popup_rect.translate(0, -potential_height);
    }

    popup_rect.translate(mapToGlobal(rect().topLeft()));
    popup_rect.setHeight(potential_height);
    popup_rect.setWidth(widthWithoutScroll());


    QPixmap pixmap(popup_rect.size());
    const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(hid_folding_content_popup);
    pixmap.fill(format.background().color());

    {
        QPainter painter(&pixmap);

        QTextBlock b = block.next();

        if (b.isVisible()) // ignore showing of not hidden items
            return;

        QPointF offset(0, 0);

        while (!b.isVisible() && potential_height > 0) {
//            b.setVisible(true); // make sure block bounding rect works

//            QRectF bl_geometry_rect = blockBoundingRect(b).translated(offset);
            QRectF bl_geometry_rect = b.layout() -> boundingRect().translated(offset);

            paintBlock(painter, b, offset.ry(), bl_geometry_rect.top(), bl_geometry_rect.bottom());

            offset.ry() += bl_geometry_rect.height();
            potential_height -= bl_geometry_rect.height();

//            b.setVisible(false);
//            b.setLineCount(0);

            b = b.next();
        }

        //    painter.setRenderHint(QPainter::Antialiasing, true);
            ////    painter.translate(.5, .5);

            ////    painter.setBrush(brush);
            ////    painter.drawRoundedRect(popup_rect, 3, 3);

//            painter.setPen(QPen(Qt::red, 2));

//            painter.drawLine(0, 1, pixmap.width(), 1);
//            painter.drawLine(0, pixmap.height() - 2, pixmap.width(), pixmap.height() - 2);
    }

    if (potential_height > 0) {
        popup_rect.setHeight(popup_rect.height() - potential_height);
        if (!place_after)
            popup_rect.translate(0, potential_height);

        //TODO: need remove this
        pixmap = pixmap.copy(0, 0, pixmap.width(), popup_rect.height());
    }

    showOverlay(olocation, popup_rect, pixmap, uid);
}



bool CodeEditor::isShowOverlayForBlock(const OVERLAY_POS_TYPE & overlay_type, const EDITOR_POS_TYPE & subuid) {
    return overlays[overlay_type] -> shownFor(subuid);
}


void CodeEditor::showOverlay(const OVERLAY_POS_TYPE & overlay_type, const QRect & rect, const QPixmap & overlay_img, const qint32 & subuid) {
    display_cacher -> mapOverlayState(overlay_type, true);
    overlays[overlay_type] -> showInfo(subuid, rect, overlay_img);
}

void CodeEditor::showOverlay(const OVERLAY_POS_TYPE & overlay_type, const UID_TYPE & draw_uid, const QTextBlock & block) {
//    if (blockOnScreen(block)) {
//        hideOverlay(overlay_type);
//        return;
//    }

    EDITOR_POS_TYPE block_number = block.blockNumber();

//    OverlayInfo::OverlayLocation overlay_pos =
//        textCursor().blockNumber() < block_number ? OverlayInfo::op_bottom : OverlayInfo::op_top;

    if (overlays[overlay_type] -> shownFor(block_number)) {
        return;
    }

    QRect bl_geometry_rect = blockRect(block).toRect();
    bl_geometry_rect.setWidth(widthWithoutScroll());

//    if (overlay_pos == OverlayInfo::op_top) {
//        int height_limit = line_number_height * 3 + 3;

//        if (bl_geometry_rect.height() > height_limit) {
//            bl_geometry_rect.setHeight(height_limit);
//        }
//    }

    QPixmap pixmap(bl_geometry_rect.size());
    const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(static_cast<Identifier>(draw_uid));
    pixmap.fill(format.background().color());

    QPainter painter(&pixmap);

    paintBlock(painter, block, 0, bl_geometry_rect.top(), bl_geometry_rect.bottom());

    overlays[overlay_type] -> showInfo(block_number, this, pixmap, overlay_type, (horizontalScrollBar() -> isVisible() ? -horizontalScrollBar() -> height() : 0));
    display_cacher -> mapOverlayState(overlay_type, true);
}

void CodeEditor::hideOverlay(const OVERLAY_POS_TYPE & overlay_type) {
    display_cacher -> mapOverlayState(overlay_type, false);

    overlays[overlay_type] -> hide();
}

void CodeEditor::hideOverlays() {
    display_cacher -> clearOverlaysState();

    for(QHash<OVERLAY_POS_TYPE, OverlayInfo *>::Iterator it = overlays.begin(); it != overlays.end(); it++)
        it.value() -> hide();
}


bool CodeEditor::rectOnScreen(const QRect & r) {
    int view_height = height();
    int rel_pos = view_height - r.top();
    return (rel_pos > line_number_height / 2) && (rel_pos <= view_height);
}

//QString CodeEditor::blockText(const EDITOR_POS_TYPE & block_num, const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length) {
//    QTextBlock block = document() -> findBlockByNumber(block_num);

//    if (block.isValid()) {
//        return block.text().mid(pos, length);
//    }
//    else return QString();
//}

QRect CodeEditor::textRect(const QTextBlock & block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length) {
    if (!block.isValid() || !block.isVisible())
        return QRect();

    QTextLine line = block.layout() -> lineForTextPosition(pos);

    if (!line.isValid())
        return QRect();

    QRectF rect = blockRect(block);

    return textRect(rect, line, pos, length);
}

QRect CodeEditor::textRect(CodeEditorCacheCell * cache, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length) {
    if (cache -> is_service || !cache -> is_visible)
        return QRect();

    QTextLine line = cache -> layout -> lineForTextPosition(pos);
    QRectF rect = cache -> bounding_rect;

    return textRect(rect, line, pos, length);
}

QRect CodeEditor::textRect(QRectF & block_rect, const QTextLine & line, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length) {
    if (!line.isValid())
        return QRect();

    qreal x_offset = -horizontalScrollBar() -> value();
    block_rect.setLeft(line.cursorToX(pos) + x_offset);
    block_rect.setRight(line.cursorToX(pos + length) + x_offset);

    return block_rect.toRect();
}


QString CodeEditor::wordUnderCursor(QTextCursor & tc, const WordUnderCursorOps & flags) {
    bool only_before_caret_part = flags & wuco_before_caret_part;

    QTextBlock block = tc.block();
    EDITOR_POS_TYPE pos = tc.positionInBlock();
    EDITOR_POS_TYPE start = 0;
    EDITOR_POS_TYPE length = only_before_caret_part ? -1 : 0;

    wrapper -> getWordBoundaries(start, length, block, pos);

    if (length != 0) {
        if (only_before_caret_part)
            tc.setPosition(start, QTextCursor::KeepAnchor);
        else {
            tc.setPosition(start, QTextCursor::MoveAnchor);
            tc.setPosition(start + length, QTextCursor::KeepAnchor);
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
    } else {
        if (flags & wuco_select) {
            tc.clearSelection();
            setTextCursor(tc);
        }

        return QString();
    }
}

void CodeEditor::procSelectionIndent(const bool & right) {
    //TODO: optimize me: add text and update char length for first token and pos for second in token sequence for each line
    QTextCursor curs = textCursor();
    const QString & tab_space = wrapper -> tabSpace();
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


void CodeEditor::extraAreaMouseEvent(QMouseEvent * event) {
    QPoint pos = event -> pos();
    int prev_folding_y = folding_y;

    bool invalidation_required = false;

    bool in_breakpoint_zone = pos.rx() >= breakpoint_offset_x && pos.rx() <= breakpoint_offset_x + breakpoint_width;
    bool in_number_zone = !in_breakpoint_zone && pos.rx() >= line_number_offset_x && pos.rx() <= line_number_offset_x + line_number_width;
    bool in_folding_zone = !in_number_zone && (pos.rx() >= folding_offset_x && pos.rx() <= folding_offset_x + folding_width);

    if (!in_folding_zone) {
        active_folding.clear();
        folding_y = NO_FOLDING;
    }
    else folding_y = pos.ry();

    switch(event -> type()) {
        case QEvent::MouseMove: {
            invalidation_required =
                    //TODO: possible refactor required?
                (folding_y == NO_FOLDING || (folding_y >= 0 && folding_y <= display_cacher -> fill_bottom)) && // cancel invalidation if blocks do not fully cover screen height and mouse pointer below the last block
                    (
                        (
                            in_folding_zone && (folding_y <= curr_folding_limits.rx() || folding_y >= curr_folding_limits.ry())
                        )
                        ||
                        (
                            (folding_y != NO_FOLDING) == (prev_folding_y == NO_FOLDING)
                        )
                    );

            if (invalidation_required) {
                hideOverlay(OverlayInfo::ol_hover);

                can_show_folding_popup = true;

                if (folding_click)
                    folding_click = false;

                curr_folding_limits.ry() = NO_FOLDING;
                active_folding.clear();
            }
        break;}

//        case QEvent::MouseButtonPress: {

//        break;}

        case QEvent::MouseButtonRelease: {
            if (event -> button() == Qt::LeftButton) {
                if (in_breakpoint_zone || in_number_zone || in_folding_zone) {
                    // fix for paded click
                    if (display_cacher -> fill_bottom >= pos.ry()) {
                        QTextCursor cursor = cursorForPosition(QPoint(1, pos.ry()));

                        QTextBlock blk = cursor.block();

                        if (blk.isValid()) {
                            if (in_breakpoint_zone) {
                                BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);

                                if (udata) {
                                    udata -> invertBreakpointState();
                                    invalidation_required = true;

                                    QRect r(blockRect(blk).toRect());
                                    r.setWidth(r.width() + 50);
                                    viewport() -> update(r);
                                }
                            } else if (in_number_zone) {
                                cursor.setPosition(blk.position() + blk.length() - 1, QTextCursor::MoveAnchor);
                                cursor.setPosition(blk.position(), QTextCursor::KeepAnchor);

                                setTextCursor(cursor);
                            } else {
                                if (wrapper -> layout -> toggleFolding(blk)) {
                                    folding_click = true;
                                    can_show_folding_popup = false;
                                    invalidation_required = false;

                                    //INFO: move the cursor out from folded block
                                    QTextCursor current_cursor = textCursor();

                                    QTextBlock cursor_blk = current_cursor.block();

                                    if (!cursor_blk.isVisible() || !display_cacher -> isBlockOnScreen(cursor_blk.blockNumber())) {
                                        current_cursor.setPosition(blk.position());
                                        setTextCursor(current_cursor);
                                    }

                                    //INFO: monkey patch for folding in first line if doc opened but not edited yet
                                    if (curr_block_number == NO_INFO) {
                                        imitateClick();
                                    }

                                    if (display_cacher -> isShowOverlay())
                                        hideOverlays();
                                }
                            }
                        }
                    }
                }
            }
        break;}

//        case QEvent::MouseButtonDblClick: {
//            return;
//        break;}

        default:
//            event -> ignore();
            return;
    }

    event -> accept();

    if (invalidation_required)
        update();
}

void CodeEditor::extraAreaLeaveEvent(QEvent *) {
    // fake missing mouse move event from Qt
    QMouseEvent me(QEvent::MouseMove, QPoint(-1, -1), Qt::NoButton, nullptr, nullptr);
    extraAreaMouseEvent(&me);
}

void CodeEditor::extraAreaPaintEvent(QPaintEvent * event) {
//    Logger::obj().startMark();

    int target_top = event -> rect().top();
    int target_bottom = event -> rect().bottom();

    QPainter painter(extra_area);

    if (show_breakpoints_panel) {
        const QTextCharFormat & breackpoints_scope_format = HighlightFormatFactory::obj().getFormatFor(hid_breakpoints_range);
        painter.fillRect(breakpoint_offset_x, target_top, breakpoint_width, rect().height(), breackpoints_scope_format.background());
    }

    if (show_extra_icons) {
        const QTextCharFormat & extra_icons_scope_format = HighlightFormatFactory::obj().getFormatFor(hid_extra_icons_range);
        painter.fillRect(extra_ico_offset_x, target_top, extra_ico_width, rect().height(), extra_icons_scope_format.background());
    }

    for (CodeEditorCacheCell * it = display_cacher -> begin(); !it -> is_service; it = it -> next) {
        if (!it -> is_visible || it -> bounding_rect.bottom() < target_top) {
            continue;
        }

        if (it -> bounding_rect.top() > target_bottom || it -> is_service) {
            break;
        }

        extraAreaPaintBlock(painter, it);
    };

    event -> accept();

//    Logger::obj().endMark(false, QLatin1Literal("extraAreaPaintEvent"));
}


void CodeEditor::customPaintEvent(QPainter & painter, QPaintEvent * e) {   
    QRect view_rect = viewport() -> rect();
    QRect er = e -> rect();
    QHash<int, bool> folding_scopes;

    CodeEditorCacheCell * cache_cell = nullptr;

    bool editable = !isReadOnly();
    bool need_placeholder = !placeholderText().isEmpty() && document() -> isEmpty();
    bool has_active_para = para_info.isValid();

    QPointF offset(contentOffset());
    QTextBlock block = firstVisibleBlock();
    qreal max_width = document() -> documentLayout() -> documentSize().width();
    qreal doc_margin = document() -> documentMargin();

    // Set a brush origin so that the WaveUnderline knows where the wave started
    painter.setBrushOrigin(offset);

    ///// CACHING ///////
    display_cacher -> setTab(wrapper -> tabSpace(), symbol_width);
    display_cacher -> clear();
    display_cacher -> top_block_number = block.blockNumber();
    cache_cell = display_cacher -> append(display_cacher -> top_block_number);

    if (show_folding_scope_lines)
        cache_cell -> initLevels(block);

    // keep right margin clean from full-width selection
    int max_x = offset.x() + qMax(static_cast<qreal>(view_rect.width()), max_width) - doc_margin;

    er.setRight(qMin(er.right(), max_x));
    painter.setClipRect(er);

    QAbstractTextDocumentLayout::PaintContext context = getPaintContext();
    const QTextCharFormat & selection_format = HighlightFormatFactory::obj().getFormatFor(hid_selection);
    const QTextCharFormat & folding_level_line_format = HighlightFormatFactory::obj().getFormatFor(hid_folding_level_line);
    const QTextCharFormat & breakpoint_line_format = HighlightFormatFactory::obj().getFormatFor(hid_breakpoint_line); //
    const QTextCharFormat & active_para_line_format = HighlightFormatFactory::obj().getFormatFor(hid_para_hover_line); //
    const QTextCharFormat & current_line_format = HighlightFormatFactory::obj().getFormatFor(hid_current_line);

    forever {
        cache_cell -> bounding_rect = blockBoundingRect(block).translated(offset);
        cache_cell -> layout = block.layout();

        if (show_folding_scope_lines)
            cache_cell -> setUserData(TextDocumentLayout::getUserDataForBlock(block));
        else
            cache_cell -> user_data = TextDocumentLayout::getUserDataForBlock(block);

        if (!block.isVisible()) {
            cache_cell -> is_visible = false;
            offset.ry() += cache_cell -> bounding_rect.height();
            block = block.next();

            cache_cell = display_cacher -> append(cache_cell -> block_number + 1);

            continue;
        }

        cache_cell -> block_pos = block.position();
        cache_cell -> block_length = block.length();

        if (cache_cell -> bounding_rect.bottom() >= er.top() && cache_cell -> bounding_rect.top() <= er.bottom()) {
            QTextBlockFormat blockFormat = block.blockFormat();
            QBrush bg = blockFormat.background();

            if (bg != Qt::NoBrush) {
                QRectF contents_rect = cache_cell -> bounding_rect;
                contents_rect.setWidth(qMax(cache_cell -> bounding_rect.width(), max_width));
                fillBackground(&painter, contents_rect, bg);
            }

            if (show_folding_scope_lines && display_cacher -> hasLevels()) {
                folding_scopes.clear();

                painter.save();
                painter.setPen(folding_level_line_format.foreground().color());

                int level = cache_cell -> user_data ? cache_cell -> user_data -> level - (cache_cell -> is_folding_opener ? 1 : 0) : DEFAULT_LEVEL;
                int def_line_offset = offset.rx() + doc_margin;
                int line_height = cache_cell -> bounding_rect.height();
                int it = -1;
                bool has_active = has_active_para && para_info.containsBlockNumber(cache_cell -> block_number);

                while(++it <= level) {
                    int folding_line_offset = display_cacher -> levelIndent(it);

                    if (
                        folding_line_offset == 0 || (
                            folding_scopes.contains(folding_line_offset) &&
                                (!has_active || (has_active && para_info.level != it))
                        )
                    ) continue;

                    folding_scopes[folding_line_offset] = true;
                    folding_line_offset += def_line_offset;

                    QLine line(folding_line_offset, offset.ry(), folding_line_offset, offset.ry() + line_height);

                    if (has_active && it == para_info.level) {
                        painter.save();

                        painter.setPen(active_para_line_format.foreground().color());
                        painter.drawLine(line);

                        painter.restore();
                    }
                    else painter.drawLine(line);
                }
                painter.restore();
            }

            QVector<QTextLayout::FormatRange> selections;
            int blpos = cache_cell -> block_pos;
            int bllen = cache_cell -> block_length;

            for (int i = 0; i < context.selections.size(); ++i) {
                const QAbstractTextDocumentLayout::Selection & range = context.selections.at(i);
                const int sel_start = range.cursor.selectionStart() - blpos;
                const int sel_end = range.cursor.selectionEnd() - blpos;

                cache_cell -> is_folding_selected = sel_start < bllen && sel_end > bllen;

                if (sel_start < bllen && sel_end > 0 && sel_end > sel_start) {
                    QTextLayout::FormatRange o;
                    o.start = sel_start;
                    o.length = sel_end - sel_start;
                    o.format = selection_format; //range.format; //selection_format; //
                    selections.append(o);
                } else if (!range.cursor.hasSelection() && range.format.hasProperty(QTextFormat::FullWidthSelection)
                           && block.contains(range.cursor.position())) {
                    // for full width selections we don't require an actual selection, just
                    // a position to specify the line. that's more convenience in usage.
                    QTextLayout::FormatRange o;
                    QTextLine l = cache_cell -> layout -> lineForTextPosition(range.cursor.position() - blpos);
                    o.start = l.textStart();
                    o.length = l.textLength();

                    if (o.start + o.length == bllen - 1)
                        ++o.length; // include newline

                    o.format = selection_format; //range.format; // selection_format
                    selections.append(o);
                }
            }

            bool draw_cursor = ((editable || (textInteractionFlags() & Qt::TextSelectableByKeyboard))
                               && context.cursorPosition >= blpos
                               && context.cursorPosition < blpos + bllen);

            bool draw_cursor_as_block = draw_cursor && overwriteMode() ;

            if (draw_cursor_as_block) {
                if (context.cursorPosition == blpos + bllen - 1) {
                    draw_cursor_as_block = false;
                } else {
                    QTextLayout::FormatRange o;
                    o.start = context.cursorPosition - blpos;
                    o.length = 1;
                    o.format.setForeground(palette().base());
                    o.format.setBackground(palette().text());
                    selections.append(o);
                }
            }

            if (need_placeholder && cache_cell -> layout -> preeditAreaText().isEmpty()) {
              QColor col = palette().text().color();
              col.setAlpha(128);
              painter.setPen(col);
              painter.drawText(cache_cell -> bounding_rect.adjusted(doc_margin, 0, 0, 0), Qt::AlignTop | Qt::TextWordWrap, placeholderText());
            } else {
              cache_cell -> layout -> draw(&painter, offset, selections, er);
            }

            if ((draw_cursor && !draw_cursor_as_block)
                || (editable && context.cursorPosition < -1
                    && !cache_cell -> layout -> preeditAreaText().isEmpty())) {
                int cpos = context.cursorPosition;
                if (cpos < -1)
                    cpos = cache_cell -> layout -> preeditAreaPosition() - (cpos + 2);
                else
                    cpos -= blpos;
                cache_cell -> layout -> drawCursor(&painter, offset, cpos, cursorWidth());
            }

            bool is_breakpoint_line = cache_cell -> user_data && cache_cell -> user_data -> hasBreakpoint();
            bool is_current_line = cache_cell -> block_number == curr_block_number;

            if (is_current_line || is_breakpoint_line) {
                QRect r(0, offset.ry(), max_x, cache_cell -> bounding_rect.height());

                if (is_breakpoint_line)
                    painter.fillRect(r, breakpoint_line_format.background());

                if (is_current_line) {
                    painter.fillRect(r, current_line_format.background());
                }
            }
        }

        offset.ry() += cache_cell -> bounding_rect.height();

        if (offset.y() > view_rect.height())
            break;

        block = block.next();

        if (block.isValid()) {
            cache_cell = display_cacher -> append(cache_cell -> block_number + 1);
        } else {
            display_cacher -> partialy_filled = true;
            break;
        }
    }

    if (backgroundVisible() && !block.isValid() && offset.y() <= er.bottom()
        && (centerOnScroll() || verticalScrollBar() -> maximum() == verticalScrollBar() -> minimum())) {
        painter.fillRect(
            QRect(
                QPoint(static_cast<int>(er.left()), static_cast<int>(offset.y())),
                er.bottomRight()
            ),
            palette().background()
        );
    }

    display_cacher -> fill_bottom = offset.ry();
    display_cacher -> bottom_block_number = cache_cell -> block_number;

    if (change_scroll_pos_required) {
         verticalScrollBar() -> setValue(wrapper -> verticalScrollPos(false));
         change_scroll_pos_required = false;
    }
}


bool CodeEditor::event(QEvent * event) {
//    qDebug() << "EVENT" << event -> type();

    if (event -> type() == QEvent::ToolTip) {
        QHelpEvent * helpEvent = static_cast<QHelpEvent*>(event);

        QTextCursor cursor = cursorForPosition(helpEvent -> pos() - QPoint(extraAreaWidth(), 0));
        QTextBlock blk = cursor.block();

        if (blk.isValid()) {
            EDITOR_POS_TYPE pos = cursor.positionInBlock();
            bool tip_is_visible = QToolTip::isVisible();

            BlockUserData * udata = reinterpret_cast<BlockUserData *>(blk.userData());
            if (udata && !udata -> msgs.isEmpty()) {
                int block_num = blk.blockNumber();
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
        tooplip_block_num = NO_INFO;
        event -> ignore();
        return true;
    }

    return QPlainTextEdit::event(event);
}

void CodeEditor::paintEvent(QPaintEvent * e) {
//    Logger::obj().startMark();

    QPainter painter(viewport());

    painter.save();

    customPaintEvent(painter, e);

    painter.restore();

    drawCharsLimiter(painter);

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

    drawFoldingOverlays(painter, e -> rect());

    drawParaOverlays(painter);

    drawAdditionalCarets(painter);

    e -> accept();

//    Logger::obj().endMark(false, QLatin1Literal("paintEvent"));
}

void CodeEditor::resizeEvent(QResizeEvent * e) {
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    extra_area -> setGeometry(QRect(cr.left(), cr.top(), extraAreaWidth(), cr.height()));
}

void CodeEditor::keyPressEvent(QKeyEvent * e) {
//    qDebug() << "KEY PRESSED:" << ((Qt::Key)e -> key());
    int curr_key = e -> key();

    if (completer && completer -> isVisible()) {
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
        case Qt::Key_Delete: {
            para_info.clear();
            QPlainTextEdit::keyPressEvent(e);
        break;}

//        case Qt::Key_Backspace: {
//            QPlainTextEdit::keyPressEvent(e);
//        break;}

        case Qt::Key_Return: {
            emit wrapper -> enterPressed();

            QPlainTextEdit::keyPressEvent(e);

            QTextCursor cursor = textCursor();
            int level = TextDocumentLayout::getBlockLevel(cursor.block());

            if (level > DEFAULT_LEVEL) {
                const QLatin1String & tab_str = wrapper -> tabSpace();
                QString str = QString(level * tab_str.size(), tab_str[0].toLatin1());

                cursor.insertText(str);
            }
        break;}

        case Qt::Key_Tab: { procSelectionIndent(); break;}
        case Qt::Key_Backtab: { procSelectionIndent(false); break; }

        case Qt::Key_Right:
        case Qt::Key_Left: {
            QTextCursor cursor = textCursor();
            QTextBlock blk = cursor.block();
            int pos_in_block = cursor.positionInBlock();

            if (curr_key == Qt::Key_Right && pos_in_block == blk.length() - 1) {
                BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);

                if (udata -> isFolded()) {
                    wrapper -> layout -> toggleFolding(blk);
                }
            }

            QPlainTextEdit::keyPressEvent(e);

            if (curr_key == Qt::Key_Left && pos_in_block == 0) {
                QTextBlock tail_blk = blk.previous();

                if (!tail_blk.isVisible()) {
                    cursor = textCursor();
                    QTextBlock head_blk = cursor.block().previous();

                    cursor.setPosition(tail_blk.position() + tail_blk.length() - 1);
                    setTextCursor(cursor);
                    wrapper -> layout -> toggleFolding(head_blk);
                }
            }
        break;}

        case Qt::Key_Escape: // ignore non printable keys
        case Qt::Key_CapsLock:
        case Qt::Key_NumLock:
        case Qt::Key_ScrollLock:
        case Qt::Key_Meta:
        case Qt::Key_Alt:
        case Qt::Key_Shift:
        case Qt::Key_Control: { QPlainTextEdit::keyPressEvent(e); break;}

        default: {
            if (!completer || (!completer -> isVisible() &&
                    (curr_key < Qt::Key_Space || curr_key > Qt::Key_ydiaeresis)
                )
            ) {
                QPlainTextEdit::keyPressEvent(e);
                procRevision();
                return;
            }

            bool has_modifiers = e -> modifiers() != Qt::NoModifier;
            bool is_shortcut = (e -> modifiers() & Qt::ControlModifier) && curr_key == Qt::Key_Space;

            if (!is_shortcut)
                QPlainTextEdit::keyPressEvent(e);

            QTextCursor tc = textCursor();
            procCompleterForCursor(tc, is_shortcut, has_modifiers);
        }
    }

    procRevision();
}

void CodeEditor::keyReleaseEvent(QKeyEvent * e) {
    int curr_key = e -> key();

    switch (curr_key) {
        case Qt::Key_Delete: { cursorMoved(); break;}
    }

    QPlainTextEdit::keyReleaseEvent(e);
}

void CodeEditor::wheelEvent(QWheelEvent * e) {
    if (display_cacher -> isShowOverlay())
        hideOverlays();

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
    if (display_cacher -> isShowOverlay())
        hideOverlays();

    if (completer)
        completer -> setWidget(this);

    emit inFocus();

    QPlainTextEdit::focusInEvent(e);
}

void CodeEditor::mouseDoubleClickEvent(QMouseEvent * e) {
    QTextCursor tc = cursorForPosition(e -> pos());

    if (tc.isNull())
        QPlainTextEdit::mouseDoubleClickEvent(e);
    else {
        wordUnderCursor(tc, wuco_select_full);
    }

    e -> accept();
}

void CodeEditor::mousePressEvent(QMouseEvent * e) {
    if (display_cacher -> isShowOverlay())
        hideOverlays();

    if (unfold_on_click_overlay) {
        QPoint point = e -> localPos().toPoint();
        int y = point.y();

        for (CodeEditorCacheCell * it = display_cacher -> begin(); !it -> is_service; it = it -> next) {
            if (it -> folding_description_rect.width() == 0 || it -> folding_description_rect.bottom() < y) {
                continue;
            }

            if (it -> folding_description_rect.top() > y) {
                break;
            }

            if (it -> folding_description_rect.contains(point)) {
                QTextBlock blk = document() -> findBlockByNumber(it -> block_number);

                if (wrapper -> layout -> toggleFolding(blk)) {
                    restoreDefaultMouseCursor();

                    if (display_cacher -> isShowOverlay())
                        hideOverlays();

                    QTextCursor current_cursor = textCursor();
                    QTextBlock cursor_blk = current_cursor.block();

                    if (!display_cacher -> isBlockOnScreen(cursor_blk.blockNumber())) {
                        current_cursor.setPosition(blk.position());
                        setTextCursor(current_cursor);
                    }
                }
            }
        }

        QPlainTextEdit::mousePressEvent(e);
    }
    else QPlainTextEdit::mousePressEvent(e);

    //INFO: monkey patch for mouse click in pos(0, 0) after a doc opened
    if (curr_block_number == NO_INFO) {
        imitateClick();
    }
}

void CodeEditor::mouseMoveEvent(QMouseEvent * e) {
    QPlainTextEdit::mouseMoveEvent(e);

    if (!show_folding_content_on_hover_overlay) return;

    QPoint point = e -> localPos().toPoint();
    int y = point.y();

    for (CodeEditorCacheCell * it = display_cacher -> begin(); !it -> is_service; it = it -> next) {
        if (it -> folding_description_rect.width() == 0 || it -> folding_description_rect.bottom() < y) {
            continue;
        }

        if (it -> folding_description_rect.top() > y) {
            break;
        }

        if (it -> folding_description_rect.contains(point)) {
            if (!overlays[OverlayInfo::ol_hover] -> shownFor(it -> block_number)) {
                setMouseCursor(Qt::PointingHandCursor);
                showFoldingContentPopup(document() -> findBlockByNumber(it -> block_number));
            }

            return;
        }
    }

    if (overlays[OverlayInfo::ol_hover] -> isVisible()) {
        restoreDefaultMouseCursor();
        hideOverlay(OverlayInfo::ol_hover);
    }
}

void CodeEditor::procCompleterForCursor(QTextCursor & tc, const bool & initiate_popup, const bool & has_modifiers) {
    QTextBlock block = tc.block();
//    bool has_selection = tc.hasSelection();

    completer_info.cursor_pos = tc.positionInBlock();
    completer_info.word_start = 0;
    completer_info.word_length = 0;
    completer_info.lex = wrapper -> getWordBoundaries(completer_info.word_start, completer_info.word_length, block, completer_info.cursor_pos, false);
    completer_info.at_word_end = completer_info.cursor_pos - completer_info.word_start == completer_info.word_length;

    QString block_text = block.text();
    QStringRef completion_prefix = block_text.midRef(completer_info.word_start, completer_info.cursor_pos - completer_info.word_start);
    QStringRef text = block_text.midRef(completer_info.word_start, completer_info.word_length);

    if (!wrapper -> isCompleterInitiable(completer_info.lex, completer_info.at_word_end)) {
        completer -> hide();
        return;
    }

    if (initiate_popup/* && has_selection*/) {
        completer -> setCompletionPrefix(QString());
        completer -> reset();
    } else {
        if (!initiate_popup && (has_modifiers || text.length() < 2)) {
            completer -> hide();
            return;
        }

        if (completion_prefix != completer -> completionPrefix()) {
            completer -> reset();

            bool from_scratch = !wrapper -> isCompleterContinuable(completer_info.lex, completer_info.at_word_end);

            Logger::info("Completer: prefix from_scratch", from_scratch ? "true" : "false");

            completer -> setCompletionPrefix(
                from_scratch ? QString() : completion_prefix.toString()
            );
        }
    }

    int completions_amount = completer -> completionCount();

    if (completions_amount == 0) {
        completer -> hide();
        return;
    }

    if (initiate_popup && completions_amount == 1 && completion_prefix == text) {
        applyCompletion(completer -> currentCompletion());
    } else {
        QRect cr = cursorRect();
        cr.setLeft(cr.left() + extra_area -> width());
        cr.setWidth(completer -> execWidth());

        completer -> complete(cr);
    }
}

bool CodeEditor::findPara(ActiveParaInfo & info, QTextBlock blk, ParaCell * para, int start_pos) {
    bool initiated = false;
    int end_pos = start_pos;
    info.level = TextDocumentLayout::getBlockLevel(blk);

    if (para) {
        if (para -> is_blockator) {
            ParaCell * stoper = para -> closer;

            if (!stoper) {
                stoper = info.findOpositePara(para);
            }

            if (stoper) {
                if (para -> is_opener) {
                    info.setOpener(para -> pos, para -> length);
                    info.setCloser(stoper -> pos, stoper -> length);

                    while(para && para != stoper) {
                        if (para -> para_type == pt_max)
                            ++end_pos;

                        para = para -> next;
                    }
                } else {
                    info.setOpener(stoper -> pos, stoper -> length);
                    info.setCloser(para -> pos, para -> length);

                    while(para && para != stoper) {
                        if (para -> para_type == pt_max)
                            --start_pos;

                        para = para -> prev;
                    }
                }

                initiated = true;
            } else {
                qDebug() << "PARA WITHOUT CLOSER";
            }
        } else {
            info.setOpener(para -> pos, para -> length);
            info.setCloser(NO_INFO);

            while(para -> next) {
                if (para -> para_type == pt_max) {
                    blk = blk.next();

                    if (TextDocumentLayout::getBlockLevel(blk) <= info.level)
                        break;
                    else
                        ++end_pos;
                }

                para = para -> next;
            }

            initiated = true;
        }
    }

    if (initiated) {
        info.start_block_num = start_pos;
        info.end_block_num = end_pos;
    }

    return initiated;
}

void CodeEditor::overlayHidden(const OVERLAY_POS_TYPE & uid) {
    display_cacher -> mapOverlayState(uid, false);
    restoreDefaultMouseCursor();
}

void CodeEditor::applyCompletion(const QString & completion) {
    QTextCursor tc = textCursor();

    if (!tc.hasSelection()) {
        bool is_replaceable = wrapper -> isCompleterReplaceable(completer_info.lex, completer_info.at_word_end);

        if (is_replaceable) {
            int pos = tc.block().position();
            tc.setPosition(pos + completer_info.word_start, QTextCursor::MoveAnchor);
            tc.setPosition(pos + completer_info.word_start + completer_info.word_length, QTextCursor::KeepAnchor);
        }
    }

//        wordUnderCursor(tc, wuco_remove_full);

    tc.insertText(completion);

    completer -> reset();
}

void CodeEditor::highlightCurrentLine() {
    int pos_in_block = 0;
    curr_block_number = NO_INFO;

    if (hasFocus()) {
        QTextCursor cursor = textCursor();
        curr_block_number = cursor.blockNumber();
        pos_in_block = cursor.positionInBlock();
    }

    emit cursorPosChanged(
        QLatin1Literal("Line: ") % QString::number(curr_block_number + 1) % QLatin1Literal(", Col: ") % QString::number(pos_in_block)
    );

    if (display_cacher -> size() > 0)
        viewport() -> update();
}

void CodeEditor::cursorMoved() {
    bool initiated = false;
    bool alt_initiated = false;

    alt_para_info.clear();

    //INFO: when a document opened but do not have the focus yet we always have the cursor in pos 0:0 but it's not drawn. We should ignore this case.
    if (hasFocus()) {
        ParaCell * para = nullptr;

        QTextCursor cursor = textCursor();

        QTextBlock blk = cursor.block();
        int start_pos = blk.blockNumber();
        int pos_in_block = cursor.positionInBlock();
        bool can_has_second_para = false;

        if (show_folding_scope_lines) {
            CodeEditorCacheCell * cache = display_cacher -> cacheForBlockNumber(start_pos);

            if (cache && cache -> scope_offsets.size() > pos_in_block) {
                CacheScopeOffset & scope_offset = cache -> scope_offsets[pos_in_block];

                if (!scope_offset.isNull()) {
                    start_pos = scope_offset.start_block_number;
                    blk = document() -> findBlockByNumber(start_pos);

                    BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);

                    if (udata)
                        para = udata -> para_control;
                }
            }
        }

        if (!para) {
            can_has_second_para = true;
            para = wrapper -> getPara(blk, pos_in_block);
        }

        initiated = findPara(para_info, blk, para, start_pos);

        if (can_has_second_para && para) {
            if (para -> pos == pos_in_block) {
                para = para -> prevInLine();

                if (para && para -> pos != para_info.opener_pos && para -> pos + para -> length == pos_in_block)
                    alt_initiated = findPara(alt_para_info, blk, para, start_pos);
            } else if (para -> pos + para -> length == pos_in_block) {
                para = para -> nextInLine();

                if (para && para -> pos != para_info.closer_pos && para -> pos == pos_in_block)
                    alt_initiated = findPara(alt_para_info, blk, para, start_pos);
            }
        }
    }

    if (initiated) {
        if (para_info.start_block_num < display_cacher -> top_block_number)
            showOverlay(OverlayInfo::ol_top, hid_para_content_popup, document() -> findBlockByNumber(para_info.start_block_num));

        if (para_info.end_block_num > display_cacher -> bottom_block_number)
            showOverlay(OverlayInfo::ol_bottom, hid_para_content_popup, document() -> findBlockByNumber(para_info.end_block_num));

        viewport() -> update(); // update editor marks
        update(); // update folding scope on extra area
    }
    else if (para_info.isValid()) {
        para_info.clear();

        if (display_cacher -> isShowOverlay())
            hideOverlays();

        viewport() -> update(); // update editor marks
        update(); // update folding scope on extra area
    }
}

void CodeEditor::updateExtraAreaWidth(int /*newBlockCount*/) {    
    breakpoint_offset_x = 2;
    breakpoint_width = show_breakpoints_panel ? (ICO_WIDTH + HPADDING) : 0;

    line_number_offset_x = breakpoint_offset_x + breakpoint_width + (show_breakpoints_panel ? 1 : 0);
    line_number_width = lineNumsWidth();

    extra_ico_offset_x = line_number_offset_x + line_number_width + HPADDING;
    extra_ico_width = show_extra_icons ? (ICO_WIDTH + HPADDING) : 0;

    if (show_foldings_panel) {
        folding_offset_x = extra_ico_offset_x + extra_ico_width + 1;
        folding_width = ICO_WIDTH;

        folding_scope_offset_x = folding_offset_x + folding_width + 1;
        folding_scope_width = FOLDING_SCOPE_WIDTH + 1;

        extra_zone_width = folding_scope_offset_x + folding_scope_width;
    }
    else extra_zone_width = extra_ico_offset_x + extra_ico_width;

    setViewportMargins(extra_zone_width += 2, 0, 0, 0);
}

void CodeEditor::updateExtraArea(const QRect & rect, int dy) {
    if (dy)
        extra_area -> scroll(0, dy);
    else
        extra_area -> update(0, rect.y(), extra_area -> width(), rect.height());

    if (rect.contains(viewport() -> rect()))
        updateExtraAreaWidth(0);
}
