#ifndef COLOR_H
#define COLOR_H

#include <qcolor.h>

class Color : public QColor {
public:
    enum Namespace { Invalid, Rgb, Hsv, Cmyk, Hsl, Hvb };

    enum Metric {
        pm_invalid = 0,
        pm_proportional, // 0..1
        pm_ranged, // 0..255
        pm_percentage // 0..100%
    };

    enum Component : int {
        cc_invalid = 0,
        cc_alpha, // 255
        cc_rgb_r, // 255
        cc_rgb_g, // 255
        cc_rgb_b, // 255
        cc_hsv_h, // 359
        cc_hsv_s, // 255
        cc_hsv_v, // 255
        cc_hsl_h, // 359
        cc_hsl_s, // 255
        cc_hsl_l, // 255
        cc_hvb_h, // 359
        cc_hvb_v, // 255
        cc_hvb_b, // 255
        cc_cmyk_c, // 255
        cc_cmyk_m, // 255
        cc_cmyk_y, // 255
        cc_cmyk_k // 255
    };

    static int componentMax(const Component & c, const Metric & metric = pm_ranged) {
        if (metric == pm_ranged) {
            switch(c)  {
                case cc_hsv_h:
                case cc_hsl_h:
                case cc_hvb_h: return 359;

                default: return 255;
            }
        }
        else return 1000;
    }

    inline Color() : QColor() {}
    inline Color(Qt::GlobalColor color) : QColor(color) {}
    inline Color(int r, int g, int b, int a = 255) : QColor(r, g, b, a) {}
    inline Color(const QString & name) : QColor(name) {}
    inline Color(const char * aname) : Color(QLatin1String(aname)) {}
    inline Color(QLatin1String name) : QColor(name) {}

    void getRgb(qreal & r, qreal & g, qreal & b, qreal & a, const Metric & metric = pm_ranged) const;
    void getHsv(qreal & h, qreal & s, qreal & v, qreal & a, const Metric & metric = pm_ranged) const;
    void getCmyk(qreal & c, qreal & m, qreal & y, qreal & k, qreal & a, const Metric & metric = pm_ranged) const;
    void getHsl(qreal & h, qreal & s, qreal & l, qreal & a, const Metric & metric = pm_ranged) const;
    void getHwb(qreal & h, qreal & w, qreal & b, qreal & a, const Metric & metric = pm_ranged) const;

    void setRgb(qreal & r, qreal & g, qreal & b, qreal & a, const Metric & metric = pm_ranged) const;
    void setHsv(qreal & h, qreal & s, qreal & v, qreal & a, const Metric & metric = pm_ranged) const;
    void setCmyk(qreal & c, qreal & m, qreal & y, qreal & k, qreal & a, const Metric & metric = pm_ranged) const;
    void setHsl(qreal & h, qreal & s, qreal & l, qreal & a, const Metric & metric = pm_ranged) const;
    void setHwb(qreal & h, qreal & w, qreal & b, qreal & a, const Metric & metric = pm_ranged) const;
private:
    void hsvToHwb(const qreal & s, const qreal & v, qreal & w, qreal & b) const {
        w = (1.0 - s) * v;
        b = 1.0 - v;
    }

    void hwbToHsv(const qreal & w, const qreal & b, qreal & s, qreal & v) const {
        s = 1.0 - (w / (1.0 - b));
        v = 1.0 - b;
    }
};

#endif // COLOR_H
