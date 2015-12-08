#ifndef LINE_NUMBERS_H
#define LINE_NUMBERS_H

#include "code_editor.h"

class LineNumberArea : public QWidget {
    CodeEditor * codeEditor;
public:
    LineNumberArea(CodeEditor * editor) : QWidget(editor), codeEditor(editor) {}

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor -> lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE {
        codeEditor -> lineNumberAreaPaintEvent(event);
    }
};

#endif // LINE_NUMBERS_H
