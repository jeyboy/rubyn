#ifndef EBLET_H
#define EBLET_H

#include <qpushbutton.h>

class QTimer;
class QPen;

class Eblet : public QPushButton {
    Q_OBJECT
public:
    enum State {
        es_normal = 0,
        es_happy = 1,
        es_sad = 2,
        es_blink = 4
    };

    Eblet(QWidget * parent = nullptr);
    ~Eblet() Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent * e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent * e) Q_DECL_OVERRIDE;
private:
    QPen * face_pen;

    State state;
    QTimer * timer;
    QPoint cursor_pos;
    QPoint face_pos;

    qreal eye_apple;

    QRectF face;
    QRectF left_eye;
    QRectF center_left_eye_apple;
    QRectF right_eye;
    QRectF center_right_eye_apple;
    QRectF mouth;
private slots:
    void updateData();
};

#endif // EBLET_H
