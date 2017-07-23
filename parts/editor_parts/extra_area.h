#ifndef EXTRA_AREA_H
#define EXTRA_AREA_H

#include "parts/code_editor.h"

class ExtraArea : public QWidget {
    CodeEditor * codeEditor;
public:
    ExtraArea(CodeEditor * editor) : QWidget(editor), codeEditor(editor) {
        setMouseTracking(true);
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor -> extraAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE {
        codeEditor -> extraAreaPaintEvent(event);
    }

//    void paintEvent(QPaintEvent *event) {
//        textEdit->extraAreaPaintEvent(event);
//    }
//    void mousePressEvent(QMouseEvent *event) {
//        textEdit->extraAreaMouseEvent(event);
//    }
    void mouseMoveEvent(QMouseEvent * event) {
        codeEditor -> extraAreaMouseEvent(event);
    }
//    void mouseReleaseEvent(QMouseEvent *event) {
//        textEdit->extraAreaMouseEvent(event);
//    }
//    void leaveEvent(QEvent *event) {
//        textEdit->extraAreaLeaveEvent(event);
//    }
//    void contextMenuEvent(QContextMenuEvent *event) {
//        textEdit->extraAreaContextMenuEvent(event);
//    }

    void wheelEvent(QWheelEvent * event) {
        QCoreApplication::sendEvent(codeEditor -> viewport(), event);
    }
};

#endif // EXTRA_AREA_H
