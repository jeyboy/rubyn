#include "tab_bar_item_delegate.h"

#include <qpainter.h>
#include <qapplication.h>

TabBarItemDelegate::TabBarItemDelegate(QObject * parent) : QStyledItemDelegate(parent) {
    _close_btn_width = QApplication::style() -> pixelMetric(QStyle::PM_TabCloseIndicatorWidth, 0);
    _close_btn_height = QApplication::style() -> pixelMetric(QStyle::PM_TabCloseIndicatorHeight, 0);
    _close_btn_double_padd = (_close_btn_padd = 10) * 2;
}

QSize TabBarItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);

    return size + QSize(_close_btn_width + _close_btn_double_padd, 0);
}

void TabBarItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QStyledItemDelegate::paint(painter, option, index);

    QStyleOption opt;
    opt.rect = QRect(option.rect.topRight() - QPoint(_close_btn_width + _close_btn_double_padd, 0), option.rect.bottomRight());

    opt.state = option.state;
    opt.state |= QStyle::State_AutoRaise;

//    if (isEnabled() && underMouse() && !isChecked() && !isDown())
//        opt.state |= QStyle::State_Raised;
//    if (isChecked())
//        opt.state |= QStyle::State_On;
//    if (isDown())
//        opt.state |= QStyle::State_Sunken;

//    qDebug() << "STATE:" << opt.state;

    QApplication::style() -> drawPrimitive(QStyle::PE_IndicatorTabClose, &opt, painter);
}

bool TabBarItemDelegate::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index) {
    switch(event -> type()) {
        case QEvent::MouseButtonPress: {
            QMouseEvent * e = reinterpret_cast<QMouseEvent *>(event);

            if (e) {
                QRect btn_area(option.rect.topRight() - QPoint(_close_btn_width + _close_btn_double_padd, 0), option.rect.bottomRight());

                QRectF btn_rect(
                    btn_area.center() - QPoint(_close_btn_width / 2, _close_btn_height / 2 - 1),
                    QSize(_close_btn_width - 1, _close_btn_height - 1)
                );

                if (btn_rect.contains(e -> localPos())) {
                    emit closeTabRequested(index);
                    return true;
                }
            }
        break;}
        default: ;
    };

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
