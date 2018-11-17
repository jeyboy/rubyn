#include "jslider_style.h"

#include <qpainter.h>
#include <qwidget.h>
#include <qstyleoption.h>

JSliderStyle::JSliderStyle(QStyle * style) : QProxyStyle(style) {

}

void JSliderStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex * option, QPainter * painter, const QWidget * widget) const {
    if (control == CC_Slider) {
        if (const QStyleOptionSlider * slider = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            if (slider -> subControls & SC_SliderGroove) {
                QRect groove_rect = subControlRect(CC_Slider, slider, SC_SliderGroove, widget);

                if (groove_rect.isValid()) {
                    painter -> save();
                    painter -> setRenderHint(QPainter::Antialiasing);
//                    painter -> setBrush(QColor(255, 0, 0, 32));
                    painter -> setBrush(QBrush(background));
                    painter -> drawRoundedRect(groove_rect, 8, 8);
                    painter -> restore();
                }

//                Qt::BGMode oldMode = painter -> backgroundMode();
//                painter -> setBackgroundMode(Qt::TransparentMode);
//                painter -> drawPixmap(groove, groovePixmap);
//                painter -> setBackgroundMode(oldMode);
            }

            if (slider -> subControls & SC_SliderHandle) {
                QRect handle_rect = subControlRect(CC_Slider, slider, SC_SliderHandle, widget);

                if (handle_rect.isValid()) {
                    painter -> save();
                    painter -> setRenderHint(QPainter::Antialiasing);
                    painter -> setPen(QColor(0, 0, 0));
                    painter -> drawEllipse(handle_rect);

                    painter -> setPen(QColor(0, 0, 0));
                    painter -> setBrush(QColor(255, 255, 255, 192));
                    painter -> drawEllipse(handle_rect.adjusted(1, 1, -1, -1));

                    painter -> restore();
                }

//                Qt::BGMode oldMode = painter -> backgroundMode();
//                painter -> setBackgroundMode(Qt::TransparentMode);
//                painter -> drawPixmap(handle, handlePixmap);
//                painter -> setBackgroundMode(oldMode);
            }
        }
    }
    else QProxyStyle::drawComplexControl(control, option, painter, widget);
}

QRect JSliderStyle::subControlRect(ComplexControl control, const QStyleOptionComplex * option, SubControl subControl, const QWidget * widget) const {
    if (control == CC_Slider) {
        if (const QStyleOptionSlider * slider = qstyleoption_cast<const QStyleOptionSlider *>(option)) {
            QRect ret;

            int tick_offset = 0;
            int thickness = handle_size;     // height
            int len = handle_size;           // width

            switch (subControl) {
                case SC_SliderHandle: {
                    bool is_horizontal = slider -> orientation == Qt::Horizontal;

                    int slider_pos = sliderPositionFromValue(slider -> minimum, slider -> maximum, slider -> sliderPosition,
                        (is_horizontal ? slider -> rect.width() : slider -> rect.height()) - len, slider -> upsideDown);

                    if (is_horizontal)
                        ret.setRect(slider -> rect.x() + slider_pos, slider -> rect.y() + tick_offset, len, thickness);
                    else
                        ret.setRect(slider -> rect.x() + tick_offset, slider -> rect.y() + slider_pos, thickness, len);
                break;}

                case SC_SliderGroove:
                    if (slider -> orientation == Qt::Horizontal)
                        ret = widget -> rect();
//                        ret.setRect(slider -> rect.x() + 1, slider -> rect.y() + tick_offset, slider -> rect.width() - 3, thickness);
                    else
                        ret = widget -> rect();
//                        ret.setRect(slider -> rect.x() + tick_offset, slider -> rect.y(), thickness, slider -> rect.height());
                    break;

                default:;
            }

            return visualRect(slider -> direction, slider -> rect, ret);
        }
    }

    return QCommonStyle::subControlRect(control, option, subControl, widget);
}
