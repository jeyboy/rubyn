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

QString CodeEditor::word_boundary("~!@#$%^&*()+{}|:\"<>?,./;'[]\\-= "); // end of word

CodeEditor::CodeEditor(QWidget * parent) : QPlainTextEdit(parent), completer(0), wrapper(0), overlay(0),
    tooplip_block_num(-1), tooplip_block_pos(-1), screen_start_block_num(-1), screen_end_block_num(-1),
    folding_y(NO_FOLDING), folding_click(false)
{
    extra_area = new ExtraArea(this);  

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateExtraAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateExtraArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

//    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateExtraAreaWidth(int)));
//    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateExtraArea(QRect,int)));
//    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateExtraAreaWidth(0);
    highlightCurrentLine();

//    setLineWrapMode(NoWrap);

    verticalScrollBar() -> setSingleStep(2);
//    scrollBarWidgets()

    //    QTextCursor cursor = ui->textEdit->textCursor();
    //    ui->textEdit->selectAll();
    //    ui->textEdit->setFontPointSize(32);
    //    ui->textEdit->setTextCursor( cursor );

    setMouseTracking(true);
}

CodeEditor::~CodeEditor() {
   delete overlay;
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
//        new_font.setStretch(110);

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
    return HPADDING * 2 + fontMetrics().width(QLatin1Char('9')) * digits;
}

int CodeEditor::extraAreaWidth() {
    return foldingOffset() + HPADDING + FOLDING_WIDTH;
}

void CodeEditor::updateExtraAreaWidth(int /* newBlockCount */) {
    setViewportMargins(extraAreaWidth(), 0, 0, 0);
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

        showOverlay(firstVisibleBlock());
//        showOverlay(document() -> findBlockByNumber(screen_end_block_num + 1));

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
        hideOverlay();
        tooplip_block_num = -1;
        event -> ignore();
        return true;
    }

    return QPlainTextEdit::event(event);
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
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = currentLineColor();

        QTextCursor cursor = textCursor();
        QTextBlock origin_block = cursor.block();

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);

        selection.cursor = cursor;
        selection.cursor.clearSelection();
        extraSelections.append(selection);

        if (wordWrapMode() != QTextOption::NoWrap) {
            int offset = 0;

            while(true) {
                if (cursor.movePosition(QTextCursor::Down) && origin_block == cursor.block()) {
                    ++offset;
                    selection.cursor = cursor;
                    extraSelections.append(selection);
                }
                else break;
            }

            if (offset != 0)
                cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, offset);

            while(true) {
                if (cursor.movePosition(QTextCursor::Up) && origin_block == cursor.block()) {
                    selection.cursor = cursor;
                    extraSelections.append(selection);
                }
                else break;
            }
        }

        for(QTextBlock::iterator it = origin_block.begin(); it != origin_block.end(); it++) {
            QTextFragment fragment = it.fragment();

            selection.cursor.setPosition(fragment.position());
            selection.cursor.setPosition(fragment.position() + fragment.length(), QTextCursor::KeepAnchor);
            selection.format = fragment.charFormat();
            extraSelections.append(selection);
        }
    }

    setExtraSelections(extraSelections);
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
            folding_click = folding_y != NO_FOLDING;
        break;}

        case QEvent::MouseButtonRelease: {
            folding_click = false;
            return;
        break;}

        case QEvent::MouseButtonDblClick: {
            return;
        break;}

        default:
            event -> ignore();
            return;
    }


    if (event -> type() == QEvent::MouseButtonPress && event -> button() == Qt::LeftButton) {

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
    // TODO: need to use code without loop if is_caret_redrawing eql true

    int current_last_line_index = screen_end_block_num;
    bool is_caret_redrawing = height() - event -> rect().height() > 30;

    QPainter painter(extra_area);
//    painter.fillRect(event -> rect(), palette().base().color());

//    painter.setPen(QPen(QColor::fromRgb(0,127,255), 3));
//    painter.drawLine(event -> rect().topRight(), event -> rect().bottomRight());

    painter.setPen(extra_area -> palette().base().color().darker(150));
    painter.drawLine(event -> rect().topRight(), event -> rect().bottomRight());

    QTextBlock block = firstVisibleBlock();
    screen_end_block_num = screen_start_block_num = block.blockNumber();

    QRectF block_geometry_rect = blockBoundingGeometry(block).translated(contentOffset());

    int top = block_geometry_rect.top();
    int bottom = block_geometry_rect.bottom();
    int curr_block_number = textCursor().blockNumber();

    painter.setPen(Qt::black);
    QFont curr_font = font();
    QFont curr_line_font(curr_font.family(), curr_font.pointSize());
    curr_line_font.setUnderline(true);
    curr_line_font.setBold(true);

    int rect_top = event -> rect().top();
    int rect_bottom = event -> rect().bottom();
    int line_number_width = extra_area -> width() - HPADDING * 2 - FOLDING_WIDTH;
    int line_number_height = fontMetrics().height();


    while (block.isValid() && top <= rect_bottom) {
        if (block.isVisible() && bottom >= rect_top) {
            if (curr_block_number == screen_end_block_num)
                painter.fillRect(0, top, event -> rect().width(), line_number_height, currentLineColor(48));

//            BlockUserData * user_data = static_cast<BlockUserData *>(block.userData())

//            if (user_data) {
//              bool curr_folding = folding_y > top && folding_y < bottom;

//              drawFolding(painter, foldingOffset(), top, curr_folding && folding_click, curr_folding);
//            }

            QString number = QString::number(screen_end_block_num + 1);
            painter.setFont(curr_block_number == screen_end_block_num ? curr_line_font : curr_font);
            painter.drawText(0, top, line_number_width, line_number_height, Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++screen_end_block_num;
    }

    event -> accept();

    if (is_caret_redrawing)
        screen_end_block_num = current_last_line_index;
}

void CodeEditor::drawFolding(QPainter & p, const int & x, const int & y, const bool & open, const bool & hover) {
    //TODO: rewrite me: use cached pixmaps
    QString name = QStringLiteral(":/folding");
    name = name % (open ?  QStringLiteral("_open") : QStringLiteral("_close"));

    if (hover)
        name = name % QStringLiteral("_hover");

    int row_height = fontMetrics().height();

    p.drawPixmap(x, y + (row_height - FOLDING_WIDTH) / 2, FOLDING_WIDTH, FOLDING_WIDTH, QPixmap(name).scaled(FOLDING_WIDTH, FOLDING_WIDTH, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CodeEditor::showOverlay(const QTextBlock & block) {
//    if (blockOnScreen(block)) {
//        hideOverlay();
//        return;
//    }

    if (!overlay)
        overlay = new OverlayInfo();

    OverlayInfo::OverlayPos overlay_pos =
        textCursor().blockNumber() < block.blockNumber() ? OverlayInfo::op_bottom : OverlayInfo::op_top;

//    //////////////////////////////////
//    QRect bl_rect = blockBoundingGeometry(block).translated(contentOffset()).toRect();
//    bl_rect.setTop(bl_rect.top() + 1);
//    bl_rect.setWidth(width() - (verticalScrollBar() -> isVisible() ? verticalScrollBar() -> width() : 0));
//    overlay -> showInfo(this, bl_rect, overlay_pos);
//    //////////////////////////////////





    QRect rect = blockBoundingRect(block).toRect();
    rect.setWidth(width() - (verticalScrollBar() -> isVisible() ? verticalScrollBar() -> width() : 0));

    int extra_x_offset = extraAreaWidth() + 1;

    QPixmap pixmap(rect.size());
    QPainter p(&pixmap);
    p.fillRect(pixmap.rect(), palette().base().color());

    block.layout() -> draw(&p, QPoint(extra_x_offset, 0));

    overlay -> showInfo(this, pixmap, overlay_pos);
}

void CodeEditor::hideOverlay() {
    if (overlay) overlay -> hide();
}

bool CodeEditor::blockOnScreen(const QTextBlock & block) {
    int num = block.blockNumber();
    return num >= screen_start_block_num && num <= screen_end_block_num;
}

QString CodeEditor::wordUnderCursor(QTextCursor & tc, const WordUnderCursorOps & flags) {
//    QTextCursor tc = textCursor();
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
