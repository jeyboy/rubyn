#ifndef CODE_EDITOR
#define CODE_EDITOR

#include <qplaintextedit.h>

#include "documents/text_document.h"

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class LineNumberArea;

#define HPADDING 3

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT
    QWidget * lineNumberArea;
public:
    CodeEditor(QWidget * parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent * event);
    int lineNumberAreaWidth();

    void openDocument(TextDocument * doc);
protected:
    void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
};

#endif // CODE_EDITOR
