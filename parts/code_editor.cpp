#include "code_editor.h"
#include "editor_parts/extra_area.h"

#include <qwidget.h>
#include <qtextobject.h>
#include <qpainter.h>
#include <qfile.h>
#include <qscrollbar.h>

#include "document_types/idocument.h"

CodeEditor::CodeEditor(QWidget * parent) : QPlainTextEdit(parent), folding_y(-100) {
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
}

void CodeEditor::openDocument(IDocument * doc) {
    if (doc) {
        QFont new_font(font().family(), 11);

        doc -> setDefaultFont(new_font);
        setFont(new_font);

        setDocumentTitle(doc -> name());
        setDocument(doc);

        if (!doc -> isFullyReaded()) {
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

//        QColor lineColor = QColor(Qt::yellow).lighter(160);
        QColor lineColor = QColor::fromRgb(128, 128, 128, 24);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::extraAreaMouseEvent(QMouseEvent * event) {
    int folding_offset = foldingOffset();
    int x = event -> x();

    folding_y =
        x >= folding_offset && x < extra_area -> width() - HPADDING ?
            event -> y() : -100;

    event -> accept();
    update();
}

void CodeEditor::extraAreaPaintEvent(QPaintEvent * event) {
    QPainter painter(extra_area);
    painter.fillRect(event -> rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int block_number = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
//    int curr_block_number = textCursor().blockNumber();

    painter.setPen(Qt::black);
//    QFont curr_font = font();
//    QFont curr_line_font(curr_font.family(), curr_font.pointSize(), 100);

    int rect_top = event -> rect().top();
    int rect_bottom = event -> rect().bottom();
    int line_number_width = extra_area -> width() - HPADDING * 2 - FOLDING_WIDTH;
    int line_number_height = fontMetrics().height();


    while (block.isValid() && top <= rect_bottom) {
        if (block.isVisible() && bottom >= rect_top) {

//            BlockUserData * user_data = static_cast<BlockUserData *>(block.userData())

//            if (user_data) {

//            }

            drawFolding(painter, foldingOffset(), top, false, folding_y > top && folding_y < bottom);


            QString number = QString::number(block_number + 1);
//            painter.setFont(curr_block_number == block_number ? curr_line_font : curr_font);
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
    QString name = QStringLiteral(":/folding");
    name = name % (open ?  QStringLiteral("_open") : QStringLiteral("_close"));

    if (hover)
        name = name % QStringLiteral("_hover");

    p.drawPixmap(x, y, FOLDING_WIDTH, fontMetrics().height(), QPixmap(name).scaled(FOLDING_WIDTH, fontMetrics().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
