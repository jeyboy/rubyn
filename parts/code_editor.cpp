#include "code_editor.h"
#include "editor_parts/extra_area.h"

#include <qwidget.h>
#include <qtextobject.h>
#include <qpainter.h>
#include <qfile.h>

#include "document_types/idocument.h"

CodeEditor::CodeEditor(QWidget * parent) : QPlainTextEdit(parent) {
    extraArea = new ExtraArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateExtraAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateExtraArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateExtraAreaWidth(0);
    highlightCurrentLine();

    // setTabStopWidth(int width)//set tab width
}

void CodeEditor::openDocument(IDocument * doc) {
    if (doc) {
        setDocumentTitle(doc -> name());
        setDocument(doc);

        if (!doc -> isFullyReaded()) {
            //    verticalScrollBar()
        }
    }
    // else inform user about fail
}

int CodeEditor::extraAreaWidth() {
    int digits = qMax(1, QString::number(blockCount()).length());
    return HPADDING * 2 + fontMetrics().width(QLatin1Char('9')) * digits;
}

void CodeEditor::updateExtraAreaWidth(int /* newBlockCount */) {
    setViewportMargins(extraAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateExtraArea(const QRect & rect, int dy) {
    if (dy)
        extraArea -> scroll(0, dy);
    else
        extraArea -> update(0, rect.y(), extraArea -> width(), rect.height());

    if (rect.contains(viewport() -> rect()))
        updateExtraAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent * e) {
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    extraArea -> setGeometry(QRect(cr.left(), cr.top(), extraAreaWidth(), cr.height()));
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

void CodeEditor::extraAreaPaintEvent(QPaintEvent * event) {
    QPainter painter(extraArea);
    painter.fillRect(event -> rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int block_number = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    int curr_block_number = textCursor().blockNumber();

    while (block.isValid() && top <= event -> rect().bottom()) {
        if (block.isVisible() && bottom >= event -> rect().top()) {
            painter.setPen(curr_block_number == block_number ? Qt::red : Qt::black);
            QString number = QString::number(block_number + 1);
            painter.drawText(0, top, extraArea -> width() - HPADDING, fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++block_number;
    }
}
