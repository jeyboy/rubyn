#include "eblet.h"

#include <qpainter.h>
#include <qpen.h>
#include <qtimer.h>
#include <qdebug.h>

Eblet::Eblet(QWidget * parent) : QPushButton(parent), face_pen(nullptr), eye_pen(nullptr), mouth_pen(nullptr) {
    timer = new QTimer(this);
    face_pen = new QPen(QColor(0, 0, 0, 192), 3);
    eye_pen = new QPen(QColor(0, 0, 0, 192), 2);
    mouth_pen = new QPen(QColor(0, 0, 0, 192), 2);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));

    timer -> start(100);
//    timer -> start(10000);
}

Eblet::~Eblet() {
    timer -> stop();
    delete face_pen;
}

void Eblet::resizeEvent(QResizeEvent * e) {
    QPushButton::resizeEvent(e);

    int margin = 5;

    face = rect();
    face.translate(margin, margin);
    face.setWidth(face.width() - margin * 2 - 1);
    face.setHeight(face.height() - margin * 2 - 1);

    QPointF face_center = face.center();

    qreal eye_size = face.height() / 4;
    qreal eye_x_offset = (face.width() / 2 - eye_size) / 2;

    left_eye = QRectF(face_center - QPointF(eye_size + eye_x_offset, eye_size), QSizeF(eye_size, eye_size));
    right_eye = QRectF(face_center + QPointF(eye_x_offset, -eye_size), QSizeF(eye_size, eye_size));

    eye_apple = left_eye.width() / 3;
    qreal half_eye_apple = eye_apple / 2;
    eye_apple_possible_offset = left_eye.width() / 2 - half_eye_apple;

    //    QRectF left_eye_apple = QRectF(left_eye.center().rx() - half_eye_apple, left_eye.bottom() - eye_apple, eye_apple, eye_apple);
    center_left_eye_apple = QRectF(left_eye.center().rx() - half_eye_apple, left_eye.center().ry() - half_eye_apple, eye_apple, eye_apple);

    //    QRectF right_eye_apple = QRectF(right_eye.center().rx() - half_eye_apple, right_eye.bottom() - eye_apple, eye_apple, eye_apple);
    center_right_eye_apple = QRectF(right_eye.center().rx() - half_eye_apple, right_eye.center().ry() - half_eye_apple, eye_apple, eye_apple);

    qreal mouth_offset = face.width() / 4;
    mouth = QRectF(QPointF(mouth_offset + 4, face.bottom() - eye_size * 1.5), QSizeF(mouth_offset * 2, eye_size));
}

void Eblet::paintEvent(QPaintEvent * e) {
    QPushButton::paintEvent(e);

    QPainter painter(this);

    painter.setRenderHint(QPainter::HighQualityAntialiasing);

//    painter.save();
    painter.setPen(*face_pen);
    painter.drawEllipse(face);
//    painter.restore();


    painter.setPen(*eye_pen);
    painter.drawEllipse(left_eye);
    painter.drawEllipse(right_eye);

    painter.setBrush(QColor(0, 0, 0));

    painter.drawEllipse(calcLeftEyeApple());
    painter.drawEllipse(calcRightEyeApple());

    painter.setPen(*mouth_pen);
    painter.fillRect(mouth, QColor(0, 0, 0));
}

QRectF Eblet::calcLeftEyeApple() {
    return center_left_eye_apple.translated(left_eye_apple_offset);
}
QRectF Eblet::calcRightEyeApple() {
    return center_right_eye_apple.translated(right_eye_apple_offset);
}

void Eblet::updateData() {
    QPoint left_eye_apple_pos = mapToGlobal(center_left_eye_apple.center().toPoint());
    QPoint right_eye_apple_pos = mapToGlobal(center_right_eye_apple.center().toPoint());

    cursor_pos = QCursor::pos();

    left_eye_apple_offset = cursor_pos - left_eye_apple_pos;
    right_eye_apple_offset = cursor_pos - right_eye_apple_pos;

//    if (qAbs(left_eye_apple_offset.rx()) > eye_apple_possible_offset) {
//        qreal lefy = left_eye_apple_offset.ry() != 0.0 ? left_eye_apple_offset.ry() / left_eye_apple_offset.rx() : 0;

//        left_eye_apple_offset = QPointF(
//            eye_apple_possible_offset * (left_eye_apple_offset.rx() < 0 ? -1 : 1),
//            eye_apple_possible_offset * lefy * (left_eye_apple_offset.ry() < 0 ? -1 : 1)
//        );
//    } else if (qAbs(left_eye_apple_offset.ry()) > eye_apple_possible_offset) {
//        qreal lefx = left_eye_apple_offset.rx() != 0.0 ? left_eye_apple_offset.rx() / left_eye_apple_offset.ry() : 0;

//        left_eye_apple_offset = QPointF(
//            eye_apple_possible_offset * lefx * (left_eye_apple_offset.rx() < 0 ? -1 : 1),
//            eye_apple_possible_offset * (left_eye_apple_offset.ry() < 0 ? -1 : 1)
//        );
//    }


//    if (qAbs(right_eye_apple_offset.rx()) > eye_apple_possible_offset) {
//        qreal lefy = right_eye_apple_offset.ry() != 0.0 ? right_eye_apple_offset.ry() / right_eye_apple_offset.rx() : 0;

//        right_eye_apple_offset = QPointF(
//            eye_apple_possible_offset * (right_eye_apple_offset.rx() < 0 ? -1 : 1),
//            eye_apple_possible_offset * lefy * (right_eye_apple_offset.ry() < 0 ? -1 : 1)
//        );
//    } else if (qAbs(right_eye_apple_offset.ry()) > eye_apple_possible_offset) {
//        qreal lefx = right_eye_apple_offset.rx() != 0.0 ? right_eye_apple_offset.rx() / right_eye_apple_offset.ry() : 0;

//        right_eye_apple_offset = QPointF(
//            eye_apple_possible_offset * lefx * (right_eye_apple_offset.rx() < 0 ? -1 : 1),
//            eye_apple_possible_offset * (right_eye_apple_offset.ry() < 0 ? -1 : 1)
//        );
//    }

    update();
}
