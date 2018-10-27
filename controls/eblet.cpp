#include "eblet.h"

#include <qpainter.h>
#include <qtimer.h>

Eblet::Eblet(QWidget * parent) : QPushButton(parent) {
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));

    timer -> start(100);
}

Eblet::~Eblet() {
    timer -> stop();
}

void Eblet::resizeEvent(QResizeEvent * e) {
    QPushButton::resizeEvent(e);

    int margin = 3;

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

    qreal mouth_offset = face.width() / 4;
    mouth = QRectF(QPointF(mouth_offset + 4, face.bottom() - eye_size * 1.5), QSizeF(mouth_offset * 2, eye_size));
}

void Eblet::paintEvent(QPaintEvent * e) {
    QPushButton::paintEvent(e);

    QPainter painter(this);

    painter.drawEllipse(face);

    painter.drawEllipse(left_eye);
    painter.drawEllipse(right_eye);

    painter.setBrush(QColor(0, 0, 0));

    qreal half_eye_apple = eye_apple / 2;

    QRectF left_eye_apple = QRectF(left_eye.center().rx() - half_eye_apple, left_eye.bottom() - eye_apple, eye_apple, eye_apple);
    painter.drawEllipse(left_eye_apple);

    QRectF right_eye_apple = QRectF(right_eye.center().rx() - half_eye_apple, right_eye.bottom() - eye_apple, eye_apple, eye_apple);
    painter.drawEllipse(right_eye_apple);

    painter.fillRect(mouth, QColor(0, 0, 0));
}

void Eblet::updateData() {
    cursor_pos = QCursor::pos();
}
