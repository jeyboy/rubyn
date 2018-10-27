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

    QPoint face_center = face.center();

    qreal eye_size = face.height() / 4;
    qreal eye_x_offset = (face.width() / 2 - eye_size) / 2;

    left_eye = QRect(face_center - QPoint(eye_size + eye_x_offset, eye_size), QSize(eye_size, eye_size));
    right_eye = QRect(face_center + QPoint(eye_x_offset, -eye_size), QSize(eye_size, eye_size));

    qreal mouth_offset = face.width() / 4;
    mouth = QRect(QPoint(mouth_offset + 4, face.bottom() - eye_size * 1.5), QSize(mouth_offset * 2, eye_size));
}

void Eblet::paintEvent(QPaintEvent * e) {
    QPushButton::paintEvent(e);

    QPainter painter(this);

    painter.drawEllipse(face);

    painter.setBrush(QColor(255,0,0));

    painter.drawEllipse(left_eye);
    painter.drawEllipse(right_eye);

    painter.fillRect(mouth, QColor(0, 0, 0));
}

void Eblet::updateData() {
    cursor_pos = QCursor::pos();
}
