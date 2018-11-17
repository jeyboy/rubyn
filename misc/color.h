#ifndef COLOR_H
#define COLOR_H

//https://github.com/dmilos/color

#include <qcolor.h>

class Color : public QColor {
public:
    enum Namespace { Invalid, Rgb, Hsv, Cmyk, Hsl, Hwb };

    enum Metric {
        cm_invalid = 0,
        cm_proportional, // 0..1
        cm_ranged, // 0..255
        cm_percentage // 0..100%
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
        cc_hwb_h, // 359
        cc_hwb_w, // 255
        cc_hwb_b, // 255
        cc_cmyk_c, // 255
        cc_cmyk_m, // 255
        cc_cmyk_y, // 255
        cc_cmyk_k // 255
    };

    static QLatin1String componentName(const Component & c);
    static qreal componentMax(const Component & c, const Metric & metric = cm_ranged);

    inline Color() : QColor() {}
    inline Color(Qt::GlobalColor color) : QColor(color) {}
    inline Color(int r, int g, int b, int a = 255) : QColor(r, g, b, a) {}
    inline Color(const QString & name) : QColor(name) {}
    inline Color(const char * aname) : Color(QLatin1String(aname)) {}
    inline Color(QLatin1String name) : QColor(name) {}
    inline Color(const QColor & color) : QColor(color) {}
    inline Color(QColor && color) : QColor(color) {}
    inline Color(const Component & component) : QColor(componentToSpec(component)) {}

    inline QColor & operator=(QColor && color) { return QColor::operator=(color); }
    inline QColor & operator=(const QColor & color) { return QColor::operator=(color); }

    void getRgb(qreal & r, qreal & g, qreal & b, qreal & a, const Metric & metric = cm_ranged) const;
    void getHsv(qreal & h, qreal & s, qreal & v, qreal & a, const Metric & metric = cm_ranged) const;
    void getCmyk(qreal & c, qreal & m, qreal & y, qreal & k, qreal & a, const Metric & metric = cm_ranged) const;
    void getHsl(qreal & h, qreal & s, qreal & l, qreal & a, const Metric & metric = cm_ranged) const;
    void getHwb(qreal & h, qreal & w, qreal & b, qreal & a, const Metric & metric = cm_ranged) const;

    void setRgb(const qreal & r, const qreal & g, const qreal & b, const qreal & a, const Metric & metric = cm_ranged);
    void setHsv(const qreal & h, const qreal & s, const qreal & v, const qreal & a, const Metric & metric = cm_ranged);
    void setCmyk(const qreal & c, const qreal & m, const qreal & y, const qreal & k, const qreal & a, const Metric & metric = cm_ranged);
    void setHsl(const qreal & h, const qreal & s, const qreal & l, const qreal & a, const Metric & metric = cm_ranged);
    void setHwb(const qreal & h, const qreal & w, const qreal & b, const qreal & a, const Metric & metric = cm_ranged);

    void setComponent(const Namespace & color_space, const Component & c, const qreal & val, const Metric & metric = cm_ranged);
    void setComponents(const Namespace & color_space, qreal & c1, qreal & c2, qreal & c3, qreal & c4, qreal & a, const Metric & metric = cm_ranged);
    void getComponents(const Namespace & color_space, qreal & c1, qreal & c2, qreal & c3, qreal & c4, qreal & a, const Metric & metric = cm_ranged) const;

    Color convertTo(const Namespace & color_space) const Q_DECL_NOTHROW;
private:
    QColor::Spec componentToSpec(const Component & component);

    inline void hsvToHwb(const qreal & s, const qreal & v, qreal & w, qreal & b) const {
        w = (1.0 - s) * v;
        b = 1.0 - v;
    }
    inline void hwbToHsv(const qreal & w, const qreal & b, qreal & s, qreal & v) const {
        v = 1.0 - b;
        s = b == 1.0 ? 0 : (1.0 - w / v);

        if (s < 0) {
            v += s;
            s = -s;
        }
    }
};

#endif // COLOR_H
