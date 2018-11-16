#include "color_slider.h"

#include <qpainter.h>
#include <qvariant.h>
#include <qdebug.h>

#include "jslider_style.h"
#include "misc/color.h"

ColorSlider::ColorSlider(QWidget * parent) : QSlider(parent) {
    setMinimumWidth(80);
    setOrientation(Qt::Horizontal);

    jstyle = new JSliderStyle(style());
    jstyle -> setHandleSize(height());
    setStyle(jstyle);
}

void ColorSlider::resizeEvent(QResizeEvent * e) {
    QSlider::resizeEvent(e);
    calcBackground();
}

void ColorSlider::calcBackground(const bool & updating) {
    jstyle -> setHandleSize(height());

    int w = width();
    int h = height();

    if (w == 0 || h == 0) return;

//    Qt::Orientation orientation()

    QPixmap p(w, h);

    QPainter painter(&p);

    Color::Component component = static_cast<Color::Component>(property("component_id").toInt());

    Color c(component);
    Color fc;
    bool fc_init = false;

    if (component == Color::cc_alpha) {
        QBrush brush(QPixmap(":/tools/transparency").scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        painter.fillRect(p.rect(), brush);
    }

    qreal len = w - h;
    qreal step = 1.0 / len;
    qreal offset = h / 2.0;
    qreal x = offset;

    QPointF u(offset, 0);
    QPointF b(offset, p.height());

    for(qreal i = 0; i <= 1; i += step, ++x) {
        u.rx() = x;
        b.rx() = x;

        switch(component) {
            case Color::cc_alpha: { c.setAlphaF(i); break;}
            case Color::cc_rgb_r: { c.setRedF(i); break;}
            case Color::cc_rgb_g: { c.setGreenF(i); break;}
            case Color::cc_rgb_b: { c.setBlueF(i); break;}
            case Color::cc_hsv_h: { c.setHsv(i, 0, 0, 1, Color::cm_proportional); break;}
            case Color::cc_hsv_s: { c.setHsv(0, i, 0, 1, Color::cm_proportional); break;}
            case Color::cc_hsv_v: { c.setHsv(0, 0, i, 1, Color::cm_proportional); break;}
            case Color::cc_hsl_h: { c.setHsl(i, 0, 0, 1, Color::cm_proportional); break;}
            case Color::cc_hsl_s: { c.setHsl(0, i, 0, 1, Color::cm_proportional); break;}
            case Color::cc_hsl_l: { c.setHsl(0, 0, i, 1, Color::cm_proportional); break;}
            case Color::cc_hwb_h: { c.setHwb(i, 0, 0, 1, Color::cm_proportional); break;}
            case Color::cc_hwb_w: { c.setHwb(0, i, 0, 1, Color::cm_proportional); break;}
            case Color::cc_hwb_b: { c.setHwb(0, 0, i, 1, Color::cm_proportional); break;}
            case Color::cc_cmyk_c: { c.setCmyk(i, 0, 0, 0, 1, Color::cm_proportional); break;}
            case Color::cc_cmyk_m: { c.setCmyk(0, i, 0, 0, 1, Color::cm_proportional); break;}
            case Color::cc_cmyk_y: { c.setCmyk(0, 0, i, 0, 1, Color::cm_proportional); break;}
            case Color::cc_cmyk_k: { c.setCmyk(0, 0, 0, i, 1, Color::cm_proportional); break;}

            default: return;
        }

        if (!fc_init) {
            fc_init = true;
            fc = c;
        }

        painter.setPen(c);
        painter.drawLine(u, b);
    }

    painter.fillRect(0, 0, offset, p.height(), fc);
    painter.fillRect(x, 0, offset, p.height(), c);

    jstyle -> setBackground(p);

    if (updating)
        update();
}
