#include "code_editor.h"

#include <qstringbuilder.h>
#include <qwidget.h>
#include <qtextobject.h>
#include <qpainter.h>
#include <qfile.h>
#include <qscrollbar.h>
#include <qtooltip.h>

#include "editor_parts/file.h"
#include "editor_parts/extra_area.h"

#include "parts/document_types/text_document.h"

CodeEditor::CodeEditor(QWidget * parent) : QPlainTextEdit(parent), folding_y(NO_FOLDING), folding_click(false) {
    extra_area = new ExtraArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateExtraAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateExtraArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

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

void CodeEditor::openDocument(File * file) {
    if (file && file -> isText()) {
        QFont new_font(font().family(), 11);
//        new_font.setStretch(110);

        QTextDocument * text_doc = file -> asText() -> toQDoc();

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
        QTextCursor cursor = cursorForPosition(helpEvent -> pos());
        cursor.select(QTextCursor::WordUnderCursor);

        if (!cursor.selectedText().isEmpty())
            QToolTip::showText(helpEvent -> globalPos(), /*your text*/QString("%1 %2").arg(cursor.selectedText()).arg(cursor.selectedText().length()));
        else
            QToolTip::hideText();
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
    switch (e -> key()) {
        case Qt::Key_Tab: {
            textCursor().insertText(QLatin1Literal("  "));
            e -> accept();
        break;}
//        case Qt::Key_Backtab
        default: QPlainTextEdit::keyPressEvent(e);
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
    QPainter painter(extra_area);
    painter.fillRect(event -> rect(), palette().base().color());

    painter.setPen(QPen(QColor::fromRgb(0,127,255), 3));
    painter.drawLine(event -> rect().topRight(), event -> rect().bottomRight());

    QTextBlock block = firstVisibleBlock();
    int block_number = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
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
            if (curr_block_number == block_number)
                painter.fillRect(0, top, event -> rect().width(), line_number_height, currentLineColor(48));

//            BlockUserData * user_data = static_cast<BlockUserData *>(block.userData())

//            if (user_data) {
//              bool curr_folding = folding_y > top && folding_y < bottom;

//              drawFolding(painter, foldingOffset(), top, curr_folding && folding_click, curr_folding);
//            }

            QString number = QString::number(block_number + 1);
            painter.setFont(curr_block_number == block_number ? curr_line_font : curr_font);
            painter.drawText(0, top, line_number_width, line_number_height, Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++block_number;
    }

    event -> accept();
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
