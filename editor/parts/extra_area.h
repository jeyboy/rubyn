#ifndef EXTRA_AREA_H
#define EXTRA_AREA_H

#include "editor/code_editor.h"

class ExtraArea : public QWidget {
    CodeEditor * codeEditor;
public:
    ExtraArea(CodeEditor * editor) : QWidget(editor), codeEditor(editor) {
        setMouseTracking(true);

//        painter.setPen(QPen(QColor::fromRgb(0,127,255), 3));
        setStyleSheet("border-right: 1px solid " + borderColor().name(QColor::HexRgb) + ";");
    }

    inline QSize sizeHint() const Q_DECL_OVERRIDE { return QSize(codeEditor -> extraAreaWidth(), 0); }

    inline QColor borderColor() { return palette().base().color().darker(150); }

protected:
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE {
        codeEditor -> extraAreaPaintEvent(event);
    }

    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE {
        codeEditor -> extraAreaMouseEvent(event);
    }
    void mouseMoveEvent(QMouseEvent * event) Q_DECL_OVERRIDE {
        codeEditor -> extraAreaMouseEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE {
        codeEditor -> extraAreaMouseEvent(event);
    }
    void leaveEvent(QEvent * event) Q_DECL_OVERRIDE {
        codeEditor -> extraAreaLeaveEvent(event);
    }
//    void contextMenuEvent(QContextMenuEvent * event) {
//        codeEditor -> extraAreaContextMenuEvent(event);
//    }

    void wheelEvent(QWheelEvent * event) Q_DECL_OVERRIDE {
        QCoreApplication::sendEvent(codeEditor -> viewport(), event);
    }
};

#endif // EXTRA_AREA_H
