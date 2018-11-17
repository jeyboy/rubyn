#include "color.h"

QLatin1String Color::componentName(const Component & c) {
    switch(c) {
        case cc_alpha: return QLatin1Literal("A");
        case cc_rgb_r: return QLatin1Literal("R");
        case cc_rgb_g: return QLatin1Literal("G");
        case cc_rgb_b: return QLatin1Literal("B");
        case cc_hsv_h: return QLatin1Literal("H");
        case cc_hsv_s: return QLatin1Literal("S");
        case cc_hsv_v: return QLatin1Literal("V");
        case cc_hsl_h: return QLatin1Literal("H");
        case cc_hsl_s: return QLatin1Literal("S");
        case cc_hsl_l: return QLatin1Literal("L");
        case cc_hwb_h: return QLatin1Literal("H");
        case cc_hwb_w: return QLatin1Literal("W");
        case cc_hwb_b: return QLatin1Literal("B");
        case cc_cmyk_c: return QLatin1Literal("C");
        case cc_cmyk_m: return QLatin1Literal("M");
        case cc_cmyk_y: return QLatin1Literal("Y");
        case cc_cmyk_k: return QLatin1Literal("K");

        default: return QLatin1Literal("Unknown");
    }
}

qreal Color::componentMax(const Component & c, const Metric & metric) {
    if (metric == cm_ranged) {
        switch(c)  {
            case cc_hsv_h:
            case cc_hsl_h:
            case cc_hwb_h: return 359;

            default: return 255;
        }
    }
    else if (metric == cm_percentage)
        return 100.0;
    else return 1.0;
}

void Color::getRgb(qreal & r, qreal & g, qreal & b, qreal & a, const Metric & metric) const {
    switch(metric) {
        case cm_percentage: {
            QColor::getRgbF(&r, &g, &b, &a);
            r *= 100.0; g *= 100.0; b *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {
            QColor::getRgbF(&r, &g, &b, &a);
        break;}

        case cm_ranged: {
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
        case cm_percentage: {
            QColor::getHsvF(&h, &s, &v, &a);
            h *= 100.0; s *= 100.0; v *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {
            QColor::getHsvF(&h, &s, &v, &a);
        break;}

        case cm_ranged: {
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
    QColor col = *this;

    switch(metric) {
        case cm_percentage: {
            col.getCmykF(&c, &m, &y, &k, &a);
            c *= 100.0; m *= 100.0; y *= 100.0; k *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {
            col.getCmykF(&c, &m, &y, &k, &a);
        break;}

        case cm_ranged: {
            int cc, mm, yy, kk, aa;

            col.getCmyk(&cc, &mm, &yy, &kk, &aa);

            c = cc; m = mm; y = yy; k = kk; a = aa;
        break;}

        default: {
            c = 0; m = 0; y = 0; k = 0; a = 0;
        }
    }
}
void Color::getHsl(qreal & h, qreal & s, qreal & l, qreal & a, const Metric & metric) const {
    switch(metric) {
        case cm_percentage: {
            QColor::getHslF(&h, &s, &l, &a);
            h *= 100.0; s *= 100.0; l *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {
            QColor::getHslF(&h, &s, &l, &a);
        break;}

        case cm_ranged: {
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
        case cm_percentage: {
            h *= 100.0; w *= 100.0; b *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {

        break;}

        case cm_ranged: {
            h *= componentMax(cc_hwb_h); w *= componentMax(cc_hwb_w); b *= componentMax(cc_hwb_b); a *= componentMax(cc_alpha);
        break;}

        default: {
            h = 0; w = 0; b = 0; a = 0;
        }
    }
}

void Color::setRgb(const qreal & r, const qreal & g, const qreal & b, const qreal & a, const Metric & metric) {
    switch(metric) {
        case cm_percentage: {
            QColor::setRgbF(r / 100.0, g / 100.0, b / 100.0, a / 100.0);
        break;}

        case cm_proportional: {
            QColor::setRgbF(r, g, b, a);
        break;}

        case cm_ranged: {
            QColor::setRgb(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), static_cast<int>(a));
        break;}

        default:;
    }
}
void Color::setHsv(const qreal & h, const qreal & s, const qreal & v, const qreal & a, const Metric & metric) {
    switch(metric) {
        case cm_percentage: {
            QColor::setHsvF(h / 100.0, s / 100.0, v / 100.0, a / 100.0);
        break;}

        case cm_proportional: {
            QColor::setHsvF(h, s, v, a);
        break;}

        case cm_ranged: {
            QColor::setHsv(static_cast<int>(h), static_cast<int>(s), static_cast<int>(v), static_cast<int>(a));
        break;}

        default:;
    }
}
void Color::setCmyk(const qreal & c, const qreal & m, const qreal & y, const qreal & k, const qreal & a, const Metric & metric) {
    switch(metric) {
        case cm_percentage: {
            QColor::setCmykF(c / 100.0, m / 100.0, y / 100.0, k / 100.0, a / 100.0);
        break;}

        case cm_proportional: {
            QColor::setCmykF(c, m, y, k, a);
        break;}

        case cm_ranged: {
            QColor::setCmyk(static_cast<int>(c), static_cast<int>(m), static_cast<int>(y), static_cast<int>(k), static_cast<int>(a));
        break;}

        default:;
    }
}
void Color::setHsl(const qreal & h, const qreal & s, const qreal & l, const qreal & a, const Metric & metric) {
    switch(metric) {
        case cm_percentage: {
            QColor::setHslF(h / 100.0, s / 100.0, l / 100.0, a / 100.0);
        break;}

        case cm_proportional: {
            QColor::setHslF(h, s, l, a);
        break;}

        case cm_ranged: {
            QColor::setHsl(static_cast<int>(h), static_cast<int>(s), static_cast<int>(l), static_cast<int>(a));
        break;}

        default:;
    }
}
void Color::setHwb(const qreal & h, const qreal & w, const qreal & b, const qreal & a, const Metric & metric) {
    qreal hh = h, ww = w, bb = b, aa = a;

    switch(metric) {
        case cm_percentage: {
            hh /= 100.0; ww /= 100.0; bb /= 100.0; aa /= 100.0;
        break;}

        case cm_proportional: { break;}

        case cm_ranged: {
            hh /= componentMax(cc_hwb_h);
            ww /= componentMax(cc_hwb_w);
            bb /= componentMax(cc_hwb_b);
            aa /= componentMax(cc_alpha);
        break;}

        default: { return; }
    }

    qreal s, v;

    hwbToHsv(ww, bb, s, v);

    setHsv(hh, s, v, aa, cm_proportional);
}

void Color::setComponent(const Namespace & color_space, const Component & c, const qreal & val, const Metric & metric) {
    if (c == cc_invalid) return;

    qreal c1, c2, c3, c4, a;

    getComponents(color_space, c1, c2, c3, c4, a, metric);

    switch(c) {
        case cc_alpha: { a = val; break;}
        case cc_rgb_r:
        case cc_hsv_h:
        case cc_hsl_h:
        case cc_hwb_h:
        case cc_cmyk_c: { c1 = val; break; }

        case cc_rgb_g:
        case cc_hsv_s:
        case cc_hsl_s:
        case cc_hwb_w:
        case cc_cmyk_m: { c2 = val; break; }

        case cc_rgb_b:
        case cc_hsv_v:
        case cc_hsl_l:
        case cc_hwb_b:
        case cc_cmyk_y: { c3 = val; break; }

        case cc_cmyk_k: { c4 = val; break; }

        default:;
    }

    setComponents(color_space, c1, c2, c3, c4, a, metric);
}

void Color::setComponents(const Namespace & color_space, qreal & c1, qreal & c2, qreal & c3, qreal & c4, qreal & a, const Metric & metric) {
    switch(color_space) {
        case Rgb:   { setRgb(c1, c2, c3, a, metric); break;}
        case Hsv:   { setHsv(c1, c2, c3, a, metric); break;}
        case Cmyk:  { setCmyk(c1, c2, c3, c4, a, metric); break;}
        case Hsl:   { setHsl(c1, c2, c3, a, metric); break;}
        case Hwb:   { setHwb(c1, c2, c3, a, metric);  break;}

        default: {
            c1 = 0; c2 = 0; c3 = 0; c4 = 0; a = 0;
        }
    }
}

void Color::getComponents(const Namespace & color_space, qreal & c1, qreal & c2, qreal & c3, qreal & c4, qreal & a, const Metric & metric) const {
    switch(color_space) {
        case Rgb:   { getRgb(c1, c2, c3, a, metric); c4 = 0; break;}
        case Hsv:   { getHsv(c1, c2, c3, a, metric); c4 = 0; break;}
        case Cmyk:  { getCmyk(c1, c2, c3, c4, a, metric); break;}
        case Hsl:   { getHsl(c1, c2, c3, a, metric); c4 = 0; break;}
        case Hwb:   { getHwb(c1, c2, c3, a, metric); c4 = 0; break;}

        default: {
            c1 = 0; c2 = 0; c3 = 0; c4 = 0; a = 0;
        }
    }
}

Color Color::convertTo(const Namespace & color_space) const Q_DECL_NOTHROW {
    switch(color_space) {
        case Hwb: { return QColor::convertTo(QColor::Hsv); }

        default: {
            QColor::Spec spec = static_cast<QColor::Spec>(color_space);
            return QColor::convertTo(spec);
        }
    }
}

QColor::Spec Color::componentToSpec(const Component & component) {
    switch(component) {
        case cc_alpha: return QColor::Rgb;
        case cc_rgb_r: return QColor::Rgb;
        case cc_rgb_g: return QColor::Rgb;
        case cc_rgb_b: return QColor::Rgb;
        case cc_hsv_h: return QColor::Hsv;
        case cc_hsv_s: return QColor::Hsv;
        case cc_hsv_v: return QColor::Hsv;
        case cc_hsl_h: return QColor::Hsl;
        case cc_hsl_s: return QColor::Hsl;
        case cc_hsl_l: return QColor::Hsl;
        case cc_hwb_h: return QColor::Hsv;
        case cc_hwb_w: return QColor::Hsv;
        case cc_hwb_b: return QColor::Hsv;
        case cc_cmyk_c: return QColor::Cmyk;
        case cc_cmyk_m: return QColor::Cmyk;
        case cc_cmyk_y: return QColor::Cmyk;
        case cc_cmyk_k: return QColor::Cmyk;

        default: return QColor::Invalid;
    };
}
