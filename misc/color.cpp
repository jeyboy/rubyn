#include "color.h"

void Color::getRgb(qreal & r, qreal & g, qreal & b, qreal & a, const Metric & metric) const {
    switch(metric) {
        case pm_percentage: {
            QColor::getRgbF(&r, &g, &b, &a);
            r /= 1.0 * 100.0;
            g /= 1.0 * 100.0;
            b /= 1.0 * 100.0;
            a /= 1.0 * 100.0;
        break;}

        case pm_proportional: {
            QColor::getRgbF(&r, &g, &b, &a);
        break;}

        case pm_ranged: {
            int rr, gg, bb, aa;

            QColor::getRgb(&rr, &gg, &bb, &aa);
            r = rr; g = gg; b = bb; a = aa;
        break;}

        default: {
            r = 0; g = 0; b = 0; a = 0;
        }
    }
}
void Color::getHsv(qreal & h, qreal & s, qreal & v, qreal & a, const Metric & metric) const {
    switch(metric) {
        case pm_percentage: {
            QColor::getHsvF(&h, &s, &v, &a);
            h /= 1.0 * 100.0;
            s /= 1.0 * 100.0;
            v /= 1.0 * 100.0;
            a /= 1.0 * 100.0;
        break;}

        case pm_proportional: {
            QColor::getHsvF(&h, &s, &v, &a);
        break;}

        case pm_ranged: {
            int hh, ss, vv, aa;

            QColor::getHsv(&hh, &ss, &vv, &aa);
            h = hh; s = ss; v = vv; a = aa;
        break;}

        default: {
            h = 0; s = 0; v = 0; a = 0;
        }
    }
}
void Color::getCmyk(qreal & c, qreal & m, qreal & y, qreal & k, qreal & a, const Metric & metric) const {
    switch(metric) {
        case pm_percentage: {
            c = QColor::cyanF(); m = QColor::magentaF(); y = QColor::yellowF(); k = QColor::blackF();
            c /= 1.0 * 100.0;
            m /= 1.0 * 100.0;
            y /= 1.0 * 100.0;
            k /= 1.0 * 100.0;
            a /= 1.0 * 100.0;
        break;}

        case pm_proportional: {
            c = QColor::cyanF(); m = QColor::magentaF(); y = QColor::yellowF(); k = QColor::blackF();
        break;}

        case pm_ranged: {
            c = QColor::cyan(); m = QColor::magenta(); y = QColor::yellow(); k = QColor::black();
        break;}

        default: {
            c = 0; m = 0; y = 0; k = 0; a = 0;
        }
    }
}
void Color::getHsl(qreal & h, qreal & s, qreal & l, qreal & a, const Metric & metric) const {
    switch(metric) {
        case pm_percentage: {
            QColor::getHslF(&h, &s, &l, &a);
            h /= 1.0 * 100.0;
            s /= 1.0 * 100.0;
            l /= 1.0 * 100.0;
            a /= 1.0 * 100.0;
        break;}

        case pm_proportional: {
            QColor::getHslF(&h, &s, &l, &a);
        break;}

        case pm_ranged: {
            int hh, ss, ll, aa;

            QColor::getHsl(&hh, &ss, &ll, &aa);
            h = hh; s = ss; l = ll; a = aa;
        break;}

        default: {
            h = 0; s = 0; l = 0; a = 0;
        }
    }
}
void Color::getHwb(qreal & h, qreal & w, qreal & b, qreal & a, const Metric & metric) const {
    qreal s, v;

    QColor::getHsvF(&h, &s, &v, &a);

    hsvToHwb(s, v, w, b);

    switch(metric) {
        case pm_percentage: {
            h /= 1.0 * 100.0;
            s /= 1.0 * 100.0;
            v /= 1.0 * 100.0;
            a /= 1.0 * 100.0;
        break;}

        case pm_proportional: {

        break;}

        case pm_ranged: {
            h *= componentMax(cc_hvb_h); v *= componentMax(cc_hvb_v); b *= componentMax(cc_hvb_b); a *= componentMax(cc_alpha);
        break;}

        default: {
            h = 0; v = 0; b = 0; a = 0;
        }
    }
}

void Color::setRgb(qreal & r, qreal & g, qreal & b, qreal & a, const Metric & metric) const {

}
void Color::setHsv(qreal & h, qreal & s, qreal & v, qreal & a, const Metric & metric) const {

}
void Color::setCmyk(qreal & c, qreal & m, qreal & y, qreal & k, qreal & a, const Metric & metric) const {

}
void Color::setHsl(qreal & h, qreal & s, qreal & l, qreal & a, const Metric & metric) const {

}
void Color::setHwb(qreal & h, qreal & w, qreal & b, qreal & a, const Metric & metric) const {

}
