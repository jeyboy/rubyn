#ifndef OVERLAY_INFO_H
#define OVERLAY_INFO_H

#include <qlabel.h>
#include <qdebug.h>

#include "misc/defines.h"

#define GENERATE_UID(by_rect, pos, sub_uid) QStringLiteral("%1%2%3").arg(by_rect).arg(pos).arg(sub_uid)

class OverlayInfo : public QLabel {
    Q_OBJECT
public:
    enum OverlayPos : OVERLAY_POS_TYPE {
        op_top = 0,
        op_bottom
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
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setParent(nullptr);
        setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setFocusPolicy(Qt::NoFocus);
    }

    void registerShowing(const bool & by_rect, const OVERLAY_POS_TYPE & pos, const qint32 & uid) {
        setProperty("by_rect", by_rect);
        setProperty("uid", GENERATE_UID(by_rect, pos, uid));
    }

    bool shownFor(const bool & by_rect, const OVERLAY_POS_TYPE & pos, const qint32 & uid) {
        return isVisible() && property("uid").toString() == GENERATE_UID(by_rect, pos, uid);
    }

    bool shownFor(const bool & by_rect) {
        return isVisible() && property("by_rect").toBool() == by_rect;
    }

    void showInfo(QWidget * widget, const QRect & rect, const OverlayPos & pos = op_top) {
        QPixmap pixmap(rect.size());
        widget -> render(&pixmap, QPoint(), QRegion(rect));

        showInfo(widget, pixmap, pos);
    }

    void showInfo(QWidget * widget, const QPixmap & pixmap, const OverlayPos & pos = op_top) {
        setPixmap(pixmap);

        QPoint new_pos =
            pos == op_top ?
                widget -> mapToGlobal(widget -> rect().topLeft()) - QPoint(0, pixmap.height() + 2)
                      :
                widget -> mapToGlobal(widget -> rect().bottomLeft()) + QPoint(0, 2);

        move(new_pos);
        resize(pixmap.width(), pixmap.height());

        show();
    }

    void showInfo(const QRect & rect, const QPixmap & pixmap) {
        setPixmap(pixmap);

        move(rect.topLeft());
        resize(rect.size());

//        setAutoFillBackground(false);
//        setWindowOpacity(25);

        show();
    }
};

#endif // OVERLAY_INFO_H
