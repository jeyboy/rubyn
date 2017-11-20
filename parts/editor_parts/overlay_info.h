#ifndef OVERLAY_INFO_H
#define OVERLAY_INFO_H

#include <qlabel.h>
#include <qdebug.h>

class OverlayInfo : public QLabel {
    Q_OBJECT

public:
    enum OverlayPos {
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


        setAttribute(Qt::WA_ShowWithoutActivating);
        setParent(0);
        setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    }

    void showInfo(QWidget * widget, const QRect & rect, const OverlayPos & pos = op_top) {
        QPixmap pixmap(rect.size());
        widget -> render(&pixmap, QPoint(), QRegion(rect));

        showInfo(widget, pixmap, pos);
    }

    void showInfo(QWidget * widget, const QPixmap & pixmap, const OverlayPos & pos = op_top) {
        hide();

        setPixmap(pixmap);

        qDebug() << "XXX" << widget -> rect().topLeft() << widget -> mapToGlobal(widget -> rect().topLeft());

        QPoint new_pos =
            pos == op_top ?
                widget -> mapToGlobal(widget -> rect().topLeft()) - QPoint(0, pixmap.height() + 2)
                      :
                widget -> mapToGlobal(widget -> rect().bottomLeft()) + QPoint(0, 2);

        move(new_pos);
        resize(pixmap.width(), pixmap.height());

        show();
    }
};

#endif // OVERLAY_INFO_H
