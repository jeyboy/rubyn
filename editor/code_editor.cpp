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

#include "project/file.h"

#include "editor/code_editor_cache.h"
#include "editor/block_user_data.h"
#include "editor/parts/overlay_info.h"
#include "editor/parts/extra_area.h"
#include "editor/document_types/text_document.h"

#include "controls/logger.h"

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
    overlay(new OverlayInfo()), tooplip_block_num(-1), tooplip_block_pos(-1), extra_overlay_block_num(-1),
    can_show_folding_popup(true), folding_click(false), folding_y(NO_FOLDING), folding_overlay_y(NO_FOLDING),
    active_para_limits(QPoint(-1, -1)), active_para_opener(QPoint(-1, -1)), active_para_closer(QPoint(-1, -1)),
    curr_block_number(-1), screen_top_block_number(-1), screen_bottom_block_number(-1),
    folding_lines_coverage_level(-1), folding_lines_coverage_level_stoper_min(FOLDING_COVERAGE_LEVEL_STOPER),
    folding_lines_coverage_level_stoper_max(FOLDING_COVERAGE_LEVEL_STOPER)
{
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
    delete overlay;
    icons.clear();

    delete display_cacher;
}

void CodeEditor::setCompleter(QCompleter * new_completer) {
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
        new_font.setLetterSpacing(QFont::AbsoluteSpacing, cursorWidth() - 1);
//        new_font.setStretch(90);

        wrapper = file -> asText();
        QTextDocument * text_doc = wrapper -> toQDoc();

//        text_doc -> setUseDesignMetrics(true);

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

void CodeEditor::setFont(const QFont & font) {
    curr_line_font = QFont(font.family(), font.pointSize());
    curr_line_font.setUnderline(true);
    curr_line_font.setBold(true);

    QPlainTextEdit::setFont(font);

    line_number_height = fontMetrics().height();

    symbol_width = QFontMetricsF(font).averageCharWidth();

    pseudo_tab_width = symbol_width * wrapper -> tabSpace().size();

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

void CodeEditor::prepareIcons(const int & size) {
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

void CodeEditor::extraAreaPaintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom, const EDITOR_POS_TYPE & block_num) {
    bool is_current = curr_block_number == block_num;

    if (is_current) {
        const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(hid_current_line_extra);
        painter.fillRect(0, paint_top, extra_zone_width, block_bottom - block_top, format.background());
    }

    BlockUserData * user_data = TextDocumentLayout::getUserDataForBlock(block);
    DATA_FLAGS_TYPE folding_flags = user_data ? user_data -> foldingState() : 0;

    bool on_block = folding_y != NO_FOLDING && folding_y > block_top && folding_y < block_bottom;
    bool initiated = false;

    if (on_block) {
        curr_folding_limits.rx() = block_top;
        curr_folding_limits.ry() = block_bottom;
    }

    if (folding_flags) {
        if (!user_data -> para_control -> is_oneliner) {
            bool opened = (folding_flags & BlockUserData::udf_folding_opened) == BlockUserData::udf_folding_opened;

            if (on_block) {
                folding_flags |= BlockUserData::udf_folding_hovered;

                if (opened) {
                    hideOverlay();

                    folding_lines_coverage_level = user_data -> level;
                    folding_lines_coverage_level_stoper_min = block_num;
                    folding_lines_coverage_level_stoper_max = FOLDING_COVERAGE_LEVEL_STOPER - (user_data -> para_control -> is_blockator ? 0 : 1);
                    initiated = true;
                }
                else {
                    if (folding_click) {
                        folding_click = false;
                    }
                    else if (can_show_folding_popup)
                        showFoldingContentPopup(block);
                }
            }

            painter.drawPixmap(
                QPoint(folding_offset_x, paint_top + (line_number_height - ICO_WIDTH) / 2),
                icons[folding_flags]
            );
        }
    }
    else if (on_block) {
        hideOverlay();
    }

    if (user_data) {
        ////////////////////////////// TEST /////////////////
        painter.drawText(
            breakpoint_offset_x, paint_top, breakpoint_width, line_number_height, Qt::AlignRight, QString::number(user_data -> level)
        );
        ////////////////////////////// END TEST /////////////////

        if (!initiated && folding_lines_coverage_level_stoper_max < 0 && user_data -> level <= folding_lines_coverage_level)
            folding_lines_coverage_level_stoper_max = block_num + folding_lines_coverage_level_stoper_max + 1;

        if (folding_lines_coverage_level_stoper_min >= 0 &&
            block_num >= folding_lines_coverage_level_stoper_min &&
                (folding_lines_coverage_level_stoper_max < 0 || block_num <= folding_lines_coverage_level_stoper_max)
        ) {
            const QTextCharFormat & format = HighlightFormatFactory::obj().getFormatFor(hid_folding_hover_range);
            painter.setPen(format.foreground().color());
            painter.fillRect(folding_offset_x, paint_top, folding_width, block_bottom - block_top, format.background());
        }

        if (user_data -> hasBreakpoint()) {
            painter.drawPixmap(
                QPoint(breakpoint_offset_x, paint_top + (line_number_height - ICO_WIDTH) / 2),
                icons[BlockUserData::udf_has_breakpoint]
            );

            const QTextCharFormat & breakpoint_line_format = HighlightFormatFactory::obj().getFormatFor(hid_breakpoint_line);
            painter.fillRect(breakpoint_offset_x, paint_top, extra_zone_width, block_bottom - block_top, breakpoint_line_format.background());
        }
    }

    if (active_para_limits.rx() >= 0 && block_num >= active_para_limits.rx() && block_num <= active_para_limits.ry()) {
        const QTextCharFormat & scope_format = HighlightFormatFactory::obj().getFormatFor(hid_folding_para_range);
        painter.fillRect(folding_scope_offset_x, paint_top, folding_scope_width, block_bottom - block_top, scope_format.background());
    }

    painter.setFont(is_current ? curr_line_font : font());
    painter.drawText(
        line_number_offset_x, paint_top, line_number_width, line_number_height, Qt::AlignRight, QString::number(block_num + 1)
    );
}


void CodeEditor::drawFoldingOverlays(QPainter & painter, const QRect & target_rect) {
    //TODO: need to cache blocks info and use it in "extraAreaPaintEvent"

    QTextBlock block = firstVisibleBlock();
    screen_top_block_number = screen_bottom_block_number = block.blockNumber();
    QRectF block_geometry_rect = blockBoundingGeometry(block).translated(contentOffset());

    qreal top = block_geometry_rect.top();
    qreal bottom = block_geometry_rect.bottom();

    int rect_top = target_rect.top();
    int rect_bottom = target_rect.bottom();

    while (block.isValid() && top <= rect_bottom) {
        if (block.isVisible() && bottom >= rect_top) {
            BlockUserData * user_data = TextDocumentLayout::getUserDataForBlock(block);

            bool opened = user_data && !user_data -> folded();
            bool ignore = opened || !user_data;

            if (!ignore && user_data -> para_control) {
                ignore = user_data -> para_control -> is_oneliner;
            }

            if (!ignore) {
                if (user_data -> para_control) {
                    QString end_str;
                    wrapper -> paraOpositionStr(user_data -> para_control -> para_type, end_str);

                    EDITOR_POS_TYPE text_pos = block.length() - 1;

                    QString mark = QLatin1Literal("...") + end_str;
                    QRect rect = textRect(block, text_pos, 1);
                    rect.adjust(3, 0, mark.length() * symbol_width + 10, 0);

                    drawTextOverlay(hid_folded_overlay, painter, rect);

                    painter.setPen(QColor::fromRgb(0, 0, 0));
                    painter.drawText(rect, Qt::AlignCenter, mark);
                }
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + blockBoundingRect(block).height();
        ++screen_bottom_block_number;
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
            b.setVisible(true); // make sure block bounding rect works

            QRectF bl_geometry_rect = blockBoundingRect(b).translated(offset);

            paintBlock(painter, b, offset.ry(), bl_geometry_rect.top(), bl_geometry_rect.bottom());

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

//            painter.setPen(QPen(Qt::red, 2));

//            painter.drawLine(0, 1, pixmap.width(), 1);
//            painter.drawLine(0, pixmap.height() - 2, pixmap.width(), pixmap.height() - 2);
    }

    if (potential_height > 0) {
        popup_rect.setHeight(popup_rect.height() - potential_height);
        if (!place_after)
            popup_rect.translate(0, potential_height);

        pixmap = pixmap.copy(0, 0, pixmap.width(), popup_rect.height());
    }

    showOverlay(popup_rect, pixmap, uid);
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

    paintBlock(painter, block, 0, bl_geometry_rect.top(), bl_geometry_rect.bottom());

    overlay -> registerShowing(false, overlay_pos, block_number);
    overlay -> showInfo(this, pixmap, overlay_pos);
}

void CodeEditor::hideOverlay() {
    if (overlay) overlay -> hide();
}

void CodeEditor::hideOverlayIfNoNeed() {
    if (extra_overlay_block_num == -1 && (folding_y == NO_FOLDING || curr_folding_limits.ry() == NO_FOLDING) && folding_overlay_y == NO_FOLDING)
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


//QString CodeEditor::blockText(const EDITOR_POS_TYPE & block_num, const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length) {
//    QTextBlock block = document() -> findBlockByNumber(block_num);

//    if (block.isValid()) {
//        return block.text().mid(pos, length);
//    }
//    else return QString();
//}

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
        folding_lines_coverage_level = -1;
        folding_lines_coverage_level_stoper_min = FOLDING_COVERAGE_LEVEL_STOPER;
        folding_lines_coverage_level_stoper_max = FOLDING_COVERAGE_LEVEL_STOPER;
        folding_y = NO_FOLDING;
    }
    else folding_y = pos.ry();

    switch(event -> type()) {
        case QEvent::MouseMove: {
            invalidation_required =
                (
                    in_folding_zone && (folding_y <= curr_folding_limits.rx() || folding_y >= curr_folding_limits.ry())
                )
                    || ((folding_y != NO_FOLDING) == (prev_folding_y == NO_FOLDING));

            if (invalidation_required) {
                can_show_folding_popup = true;

                if (folding_click)
                    folding_click = false;

                curr_folding_limits.ry() = NO_FOLDING;
                folding_lines_coverage_level = -1;
                folding_lines_coverage_level_stoper_min = FOLDING_COVERAGE_LEVEL_STOPER;
                folding_lines_coverage_level_stoper_max = FOLDING_COVERAGE_LEVEL_STOPER;
            }
        break;}

//        case QEvent::MouseButtonPress: {

//        break;}

        case QEvent::MouseButtonRelease: {
            if (event -> button() == Qt::LeftButton) {
                if (in_breakpoint_zone || in_number_zone || in_folding_zone) {
                    QTextCursor cursor = cursorForPosition(QPoint(1, pos.ry()));
                    QTextBlock blk = cursor.block();

                    if (blk.isValid()) {
                        if (in_breakpoint_zone) {
                            BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);

                            udata -> invertBreakpointState();
                            invalidation_required = true;

                            QRect r(blockBoundingGeometry(blk).translated(contentOffset()).toRect());
                            r.setWidth(r.width() + 50);
                            viewport() -> update(r);
                        } else if (in_number_zone) {
                            cursor.setPosition(blk.position() + blk.length(), QTextCursor::MoveAnchor);
                            cursor.setPosition(blk.position(), QTextCursor::KeepAnchor);

                            setTextCursor(cursor);
                        } else {
                            if (wrapper -> layout -> toggleFolding(blk)) {
                                folding_click = true;
                                can_show_folding_popup = false;
                                invalidation_required = false;

                                //INFO: move the cursor out from folded block
                                QTextCursor current_cursor = textCursor();

                                if (!current_cursor.block().isVisible()) {
                                    current_cursor.setPosition(blk.position());
                                    setTextCursor(current_cursor);
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
    Logger::obj().startMark();

    hideOverlayIfNoNeed();
//    bool is_caret_redrawing = height() - event -> rect().height() > 8;

    QPainter painter(extra_area);
    QTextBlock block = firstVisibleBlock();
    int screen_end_block_num = block.blockNumber();

    QRectF block_geometry_rect = blockBoundingGeometry(block).translated(contentOffset());

    qreal top = block_geometry_rect.top();
    qreal bottom = block_geometry_rect.bottom();

    int rect_top = event -> rect().top();
    int rect_bottom = event -> rect().bottom();

    const QTextCharFormat & breackpoints_scope_format = HighlightFormatFactory::obj().getFormatFor(hid_breakpoints_range);
    painter.fillRect(breakpoint_offset_x, rect_top, breakpoint_width, rect_bottom - rect_top, breackpoints_scope_format.background());

    while (block.isValid() && top <= rect_bottom) {
        if (block.isVisible() && bottom >= rect_top)
            extraAreaPaintBlock(painter, block, top, top, bottom, screen_end_block_num);

        block = block.next();
        top = bottom;
        bottom = top + blockBoundingRect(block).height();
        ++screen_end_block_num;
    }

    event -> accept();

    Logger::obj().endMark(true, QLatin1Literal("extraAreaPaintEvent"));
}


void CodeEditor::customPaintEvent(QPainter & painter, QPaintEvent * e) {
    QPointF offset(contentOffset());
    QRect view_rect = viewport() -> rect();

    bool editable = !isReadOnly();
    bool need_placeholder = !placeholderText().isEmpty() && document() -> isEmpty();

    QTextBlock block = firstVisibleBlock();
    qreal max_width = document() -> documentLayout() -> documentSize().width();
    qreal doc_margin = document() -> documentMargin();

    // Set a brush origin so that the WaveUnderline knows where the wave started
    painter.setBrushOrigin(offset);

    // keep right margin clean from full-width selection
    int max_x = offset.x() + qMax((qreal)view_rect.width(), max_width) - doc_margin;

    QRect er = e -> rect();
    er.setRight(qMin(er.right(), max_x));
    painter.setClipRect(er);

    QAbstractTextDocumentLayout::PaintContext context = getPaintContext();
    const QTextCharFormat & selection_format = HighlightFormatFactory::obj().getFormatFor(hid_selection);
    const QTextCharFormat & folding_level_line_format = HighlightFormatFactory::obj().getFormatFor(hid_folding_level_line);
    const QTextCharFormat & breakpoint_line_format = HighlightFormatFactory::obj().getFormatFor(hid_breakpoint_line); //

    while (block.isValid()) {
        QRectF r = blockBoundingRect(block).translated(offset);
        QTextLayout * layout = block.layout();

        if (!block.isVisible()) {
            offset.ry() += r.height();
            block = block.next();
            continue;
        }

        if (r.bottom() >= er.top() && r.top() <= er.bottom()) {
            QTextBlockFormat blockFormat = block.blockFormat();
            QBrush bg = blockFormat.background();

            if (bg != Qt::NoBrush) {
                QRectF contentsRect = r;
                contentsRect.setWidth(qMax(r.width(), max_width));
                fillBackground(&painter, contentsRect, bg);
            }

            //TODO: implement switcher and draw this only if enabled showing of folding scopes
            BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(block);
            int level = udata -> level;

            if (level > 0) {
                painter.save();
                painter.setPen(folding_level_line_format.foreground().color());
                int folding_line_offset = offset.rx() + doc_margin + pseudo_tab_width;

                while(--level > 0) {
                    painter.drawLine(folding_line_offset, offset.ry(), folding_line_offset, offset.ry() + r.height());

                    folding_line_offset += pseudo_tab_width;
                }
                painter.restore();
            }
            /////////

            QVector<QTextLayout::FormatRange> selections;
            int blpos = block.position();
            int bllen = block.length();

            for (int i = 0; i < context.selections.size(); ++i) {
                const QAbstractTextDocumentLayout::Selection & range = context.selections.at(i);
                const int selStart = range.cursor.selectionStart() - blpos;
                const int selEnd = range.cursor.selectionEnd() - blpos;

                if (selStart < bllen && selEnd > 0 && selEnd > selStart) {
                    QTextLayout::FormatRange o;
                    o.start = selStart;
                    o.length = selEnd - selStart;
                    o.format = range.format; //selection_format; //
                    selections.append(o);
                } else if (!range.cursor.hasSelection() && range.format.hasProperty(QTextFormat::FullWidthSelection)
                           && block.contains(range.cursor.position())) {
                    // for full width selections we don't require an actual selection, just
                    // a position to specify the line. that's more convenience in usage.
                    QTextLayout::FormatRange o;
                    QTextLine l = layout -> lineForTextPosition(range.cursor.position() - blpos);
                    o.start = l.textStart();
                    o.length = l.textLength();

                    if (o.start + o.length == bllen - 1)
                        ++o.length; // include newline

                    o.format = range.format; // selection_format
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

            if (need_placeholder && layout -> preeditAreaText().isEmpty()) {
              QColor col = palette().text().color();
              col.setAlpha(128);
              painter.setPen(col);
              painter.drawText(r.adjusted(doc_margin, 0, 0, 0), Qt::AlignTop | Qt::TextWordWrap, placeholderText());
            } else {
              layout -> draw(&painter, offset, selections, er);
            }

            if ((draw_cursor && !draw_cursor_as_block)
                || (editable && context.cursorPosition < -1
                    && !layout -> preeditAreaText().isEmpty())) {
                int cpos = context.cursorPosition;
                if (cpos < -1)
                    cpos = layout->preeditAreaPosition() - (cpos + 2);
                else
                    cpos -= blpos;
                layout -> drawCursor(&painter, offset, cpos, cursorWidth());
            }

            if (udata -> hasBreakpoint()) {
                painter.fillRect(0, offset.ry(), max_x, r.height(), breakpoint_line_format.background());
            }
        }

        offset.ry() += r.height();

        if (offset.y() > view_rect.height())
            break;

        block = block.next();
    }

    if (backgroundVisible() && !block.isValid() && offset.y() <= er.bottom()
        && (centerOnScroll() || verticalScrollBar() -> maximum() == verticalScrollBar() -> minimum())) {
        painter.fillRect(QRect(QPoint((int)er.left(), (int)offset.y()), er.bottomRight()), palette().background());
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
    Logger::obj().startMark();

    hideOverlayIfNoNeed();

    QPainter painter(viewport());

    painter.save();

//    QPlainTextEdit::paintEvent(e);
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

    drawFoldingOverlays(painter, e -> rect());

    if (active_para_limits.rx() != -1) {
        QTextBlock opener_blk = document() -> findBlockByNumber(active_para_limits.rx());
        drawTextOverlay(hid_para_hover_overlay, painter, opener_blk, active_para_opener.rx(), active_para_opener.ry());

        if (active_para_closer.rx() != -1) {
            QTextBlock closer_blk = active_para_limits.rx() == active_para_limits.ry() ? opener_blk : document() -> findBlockByNumber(active_para_limits.ry());
            drawTextOverlay(hid_para_hover_overlay, painter, closer_blk, active_para_closer.rx(), active_para_closer.ry());
        }
    }

    drawAdditionalCarets(painter);

    Logger::obj().endMark(true, QLatin1Literal("paintEvent"));
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
            procCompleterForCursor(tc, is_shortcut, has_modifiers);
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
}


void CodeEditor::procCompleterForCursor(QTextCursor & tc, const bool & initiate_popup, const bool & has_modifiers) {
    QTextBlock block = tc.block();
    bool has_selection = tc.hasSelection();

    EDITOR_POS_TYPE pos = tc.positionInBlock();
    EDITOR_POS_TYPE start = 0;
    EDITOR_POS_TYPE length = 0;

    LEXEM_TYPE lex = wrapper -> getWordBoundaries(start, length, block, pos, false);
    QString block_text = block.text();

    QStringRef completion_prefix = block_text.midRef(start, pos - start);//wordUnderCursor(tc, wuco_before_caret_part);
    QStringRef text = block_text.midRef(start, length); //(wordUnderCursor(tc, wuco_full));

    if (initiate_popup && has_selection) {
        completer -> setCompletionPrefix(QString());
        completer -> popup() -> reset();
//                completer -> popup() -> setCurrentIndex(
//                    completer -> completionModel() -> index(0, 0)
//                );
    } else {
        if (!initiate_popup && (has_modifiers || text.isEmpty() /*|| completion_prefix.length() < 3*/)) {
            completer -> popup() -> hide();
            return;
        }

        if (completion_prefix != completer -> completionPrefix()) {
            completer -> popup() -> reset();

            int prefix_len = completion_prefix.length();
            bool from_scratch = !wrapper -> isCompleterContinuable(lex, prefix_len == length);

            Logger::obj().write("Completer: prefix from_scratch", from_scratch ? "true" : "false");

            completer -> setCompletionPrefix(
                from_scratch ? QString() : completion_prefix.toString()
            );
//                    completer -> popup() -> setCurrentIndex(
//                        completer -> completionModel() -> index(0, 0)
//                    );
        }
    }

    int completions_amount = completer -> completionCount();

    if (completions_amount == 0) {
        completer -> popup() -> hide();
        return;
    }

    if (initiate_popup && completions_amount == 1 && completion_prefix == text) {
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

    completer -> popup() -> clearSelection();
}

void CodeEditor::highlightCurrentLine() {
    // need to show overlay for foldings in folding start/end not on the screen right now
    //                showOverlay(document() -> findBlockByNumber(60));


    QList<QTextEdit::ExtraSelection> extra_selections;

    QTextCursor cursor = textCursor();
    curr_block_number = cursor.blockNumber();
    cursor.clearSelection();

    emit cursorPosChanged(QStringLiteral("Line: %1, Col: %2").arg(curr_block_number + 1).arg(cursor.positionInBlock()));

    if (!isReadOnly()) { //
        QTextEdit::ExtraSelection selection;

        const QTextCharFormat & selection_format = HighlightFormatFactory::obj().getFormatFor(hid_current_line);
        QColor lineColor = selection_format.background().color();

        QTextBlock origin_block = cursor.block();

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = cursor;
        selection.cursor.clearSelection();
//        extra_selections.append(selection);

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

        selection.format.setProperty(QTextFormat::UserProperty, true);

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

void CodeEditor::cursorMoved() {
    bool initiated = false;

    //INFO: when a document opened but do not have the focus yet we always have the cursor in pos 0:0 but it's not drawn. We should ignore this case.
    if (hasFocus()) {
        QTextCursor cursor = textCursor();

        QTextBlock blk = cursor.block();
        ParaCell * para = wrapper -> getPara(blk, cursor.positionInBlock());

        int start_pos = blk.firstLineNumber();
        int end_pos = start_pos;

        if (para) {
            if (para -> closer) {
                ParaCell * stoper = para -> closer;

                if (para -> is_opener) {
                    active_para_opener.rx() = para -> pos;
                    active_para_opener.ry() = para -> length;

                    active_para_closer.rx() = stoper -> pos;
                    active_para_closer.ry() = stoper -> length;

                    while(para && para != stoper) {
                        if (para -> para_type == pt_max)
                            ++end_pos;

                        para = para -> next;
                    }
                } else {
                    active_para_opener.rx() = stoper -> pos;
                    active_para_opener.ry() = stoper -> length;

                    active_para_closer.rx() = para -> pos;
                    active_para_closer.ry() = para -> length;

                    while(para && para != stoper) {
                        if (para -> para_type == pt_max)
                            --start_pos;

                        para = para -> prev;
                    }
                }

                initiated = true;
            } else {
                if (!para -> is_blockator) {
                    int level = TextDocumentLayout::getBlockLevel(blk);

                    active_para_opener.rx() = para -> pos;
                    active_para_opener.ry() = para -> length;

                    active_para_closer.rx() = -1;

                    while(para -> next) {
                        if (para -> para_type == pt_max) {
                            blk = blk.next();

                            if (TextDocumentLayout::getBlockLevel(blk) <= level)
                                break;
                            else
                                ++end_pos;
                        }

                        para = para -> next;
                    }

                    initiated = true;
                }
                else qDebug() << "PARA WITHOUT CLOSER";
            }
        }

        if (initiated) {
            active_para_limits.rx() = start_pos;
            active_para_limits.ry() = end_pos;

            viewport() -> update(); // update editor marks
            update(); // update folding scope on extra area
        }
    }

    if (!initiated && active_para_limits.rx() != -1) {
        active_para_limits.rx() = -1;
        active_para_opener.rx() = -1;
        active_para_closer.rx() = -1;

        viewport() -> update(); // update editor marks
        update(); // update folding scope on extra area
    }
}

void CodeEditor::updateExtraAreaWidth(int /* newBlockCount */) {
    breakpoint_offset_x = 2;
    breakpoint_width = ICO_WIDTH + HPADDING;

    line_number_offset_x = breakpoint_offset_x + breakpoint_width + 1;
    line_number_width = lineNumsWidth();

    folding_offset_x = line_number_offset_x + line_number_width + HPADDING;
    folding_width = ICO_WIDTH;

    folding_scope_offset_x = folding_offset_x + folding_width + 1;
    folding_scope_width = FOLDING_SCOPE_WIDTH + 1;

    extra_zone_width = folding_scope_offset_x + folding_scope_width + 2;

    setViewportMargins(extra_zone_width, 0, 0, 0);
}

void CodeEditor::updateExtraArea(const QRect & rect, int dy) {
    if (dy)
        extra_area -> scroll(0, dy);
    else
        extra_area -> update(0, rect.y(), extra_area -> width(), rect.height());

    if (rect.contains(viewport() -> rect()))
        updateExtraAreaWidth(0);
}
