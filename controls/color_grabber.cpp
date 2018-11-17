#include "color_grabber.h"

#include <qevent.h>
#include <qdebug.h>

#include <qapplication.h>
#include <qscreen.h>
#include <qdesktopwidget.h>

ColorGrabber::ColorGrabber(QWidget * parent) : QWidget(parent, Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint) {
//    setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_NoSystemBackground);

    setWindowOpacity(.01);
//    setCursor(QCursor(QPixmap(":/tools/color_picker").scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    setMouseTracking(true);
}

void ColorGrabber::initiate() {
    QScreen * screen = qApp -> screenAt(QCursor::pos());
    QRect r = screen -> availableGeometry();

    move(r.topLeft());
    resize(r.size());
}

void ColorGrabber::mouseMoveEvent(QMouseEvent * e) {
    QRect screenGeometry = qApp -> primaryScreen() -> virtualGeometry();
    QPixmap p = qApp -> primaryScreen() -> grabWindow(qApp -> desktop() -> winId(), screenGeometry.x(), screenGeometry.y(), screenGeometry.width(), screenGeometry.height());
    emit colorHovered(p.toImage().pixel(QCursor::pos()));

//    QScreen * screen = qApp -> screenAt(QCursor::pos());
//    if (screen) {
//        QPixmap p = screen -> grabWindow(0);
//        qDebug() << p.size();
//        emit colorHovered(p.toImage().pixel(QCursor::pos()));
//    }

    QWidget::mouseMoveEvent(e);
}

void ColorGrabber::mousePressEvent(QMouseEvent * e) {
    QRect screenGeometry = qApp -> primaryScreen() -> virtualGeometry();
    QPixmap p = qApp -> primaryScreen() -> grabWindow(qApp -> desktop() -> winId(), screenGeometry.x(), screenGeometry.y(), screenGeometry.width(), screenGeometry.height());
    emit colorHovered(p.toImage().pixel(QCursor::pos()));

    hide();

    QWidget::mousePressEvent(e);
}
void ColorGrabber::keyPressEvent(QKeyEvent * e) {
    qDebug() << "keyPressEvent";

    switch(e -> key()) {
        case Qt::Key_Escape: {
            hide();
        break;}
    }

    QWidget::keyPressEvent(e);
}
void ColorGrabber::leaveEvent(QEvent * e) {
    QWidget::leaveEvent(e);

    if (!isHidden()) {
        initiate();
    }
}
