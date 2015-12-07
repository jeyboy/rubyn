#include "code_editor.h"
#include "line_numbers.h"
#include "services/highligters/highligters_factory.h"

#include <qtextobject.h>
#include <qpainter.h>
#include <qfile.h>

CodeEditor::CodeEditor(QWidget * parent) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void CodeEditor::openDocument(const QString & filePath) {
    QFile file((currentPath = filePath));
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        setPlainText(file.readAll());
        extractExtension();
        HighlightersFactory::obj().proceedDocument(currentMime, document());
    }
}

int CodeEditor::lineNumberAreaWidth() {
    int digits = qMax(1, QString::number(blockCount()).length());
    return 3 + fontMetrics().width(QLatin1Char('9')) * digits;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect & rect, int dy) {
    if (dy)
        lineNumberArea -> scroll(0, dy);
    else
        lineNumberArea -> update(0, rect.y(), lineNumberArea -> width(), rect.height());

    if (rect.contains(viewport() -> rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent * e) {
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea -> setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent * event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event -> rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event -> rect().bottom()) {
        if (block.isVisible() && bottom >= event -> rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea -> width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
