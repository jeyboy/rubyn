#ifndef OVERLAY_INFO_H
#define OVERLAY_INFO_H

#include <qlabel.h>
#include <qdebug.h>

#include "misc/defines.h"

class OverlayInfo : public QLabel {
    Q_OBJECT
public:
    enum OverlayLocation : OVERLAY_POS_TYPE {
        ol_top = 0,
        ol_bottom,
        ol_hover
    };

    OverlayInfo() {
//        QPalette palette = palette();
//        palette.setBrush(QPalette::Base, Qt::transparent);

//        setPalette(palette);
//        setAttribute(Qt::WA_OpaquePaintEvent, false);
//        setAttribute(Qt::WA_TranslucentBackground, true);
//        setAttribute(Qt::WA_ShowWithoutActivating);
//        setWindowFlags(/*Qt::ToolTip | */Qt::FramelessWindowHint);



//        setAttribute(Qt::WA_NoSystemBackground);
//        setAttribute(Qt::WA_TranslucentBackground);
//        setAttribute(Qt::WA_PaintOnScreen);


        setAttribute(Qt::WA_ShowWithoutActivating);
//        setAttribute(Qt::WA_TransparentForMouseEvents);
        setParent(nullptr);
        setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setFocusPolicy(Qt::NoFocus);

        setMouseTracking(true);
    }

    bool shownFor(const EDITOR_POS_TYPE & uid) {
        return isVisible() && property("uid").toLongLong() == uid;
    }

    void showInfo(const EDITOR_POS_TYPE & uid, QWidget * widget, const QRect & rect, const OVERLAY_POS_TYPE & pos = ol_top, const int & bottom_offset = 0) {
        QPixmap pixmap(rect.size());
        widget -> render(&pixmap, QPoint(), QRegion(rect));

        showInfo(uid, widget, pixmap, pos, bottom_offset);
    }
    void showInfo(const EDITOR_POS_TYPE & uid, QWidget * widget, const QPixmap & pixmap, const OVERLAY_POS_TYPE & pos = ol_top, const int & bottom_offset = 0) {
        setProperty("uid", uid);
        setPixmap(pixmap);

        QPoint new_pos =
            pos == ol_top ?
                widget -> mapToGlobal(widget -> rect().topLeft()) - QPoint(0, pixmap.height())
                      :
                widget -> mapToGlobal(widget -> rect().bottomLeft()) + QPoint(0, 2 + bottom_offset);

        move(new_pos);
        resize(pixmap.width(), pixmap.height());

        show();
    }
    void showInfo(const EDITOR_POS_TYPE & uid, const QRect & rect, const QPixmap & pixmap) {
        setProperty("uid", uid);
        setPixmap(pixmap);

        move(rect.topLeft());
        resize(rect.size());

//        setAutoFillBackground(false);
//        setWindowOpacity(25);

        show();
    }

protected:
    void mouseMoveEvent(QMouseEvent * e) Q_DECL_OVERRIDE {
        hide();
    }
};

#endif // OVERLAY_INFO_H
