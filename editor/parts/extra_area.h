#ifndef EXTRA_AREA_H
#define EXTRA_AREA_H

#include "editor/code_editor.h"

class ExtraArea : public QWidget {
    CodeEditor * code_editor;
public:
    ExtraArea(CodeEditor * editor) : QWidget(editor), code_editor(editor) {
        setMouseTracking(true);

//        painter.setPen(QPen(QColor::fromRgb(0,127,255), 3));
        setStyleSheet("border-right: 1px solid " + borderColor().name(QColor::HexRgb) + ";");
    }

    inline QSize sizeHint() const Q_DECL_OVERRIDE { return QSize(code_editor -> extraAreaWidth(), 0); }

    inline QColor borderColor() { return palette().base().color().darker(150); }

protected:
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE {
        code_editor -> extraAreaPaintEvent(event);
    }

    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE {
        code_editor -> extraAreaMouseEvent(event);
    }
    void mouseMoveEvent(QMouseEvent * event) Q_DECL_OVERRIDE {
        code_editor -> extraAreaMouseEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE {
        code_editor -> extraAreaMouseEvent(event);
    }
    void leaveEvent(QEvent * event) Q_DECL_OVERRIDE {
        code_editor -> extraAreaLeaveEvent(event);
    }
//    void contextMenuEvent(QContextMenuEvent * event) {
//        code_editor -> extraAreaContextMenuEvent(event);
//    }

    void wheelEvent(QWheelEvent * event) Q_DECL_OVERRIDE {
        QCoreApplication::sendEvent(code_editor -> viewport(), event);
    }
};

#endif // EXTRA_AREA_H
