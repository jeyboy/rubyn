#include "tab_bar_item_delegate.h"

#include <qpainter.h>
#include <qapplication.h>

//TODO: fill all except icon zone - icon should output in white circle

TabBarItemDelegate::TabBarItemDelegate(QObject * parent) : QStyledItemDelegate(parent) {
    uint _close_btn_width = QApplication::style() -> pixelMetric(QStyle::PM_TabCloseIndicatorWidth, 0);
    uint _close_btn_height = QApplication::style() -> pixelMetric(QStyle::PM_TabCloseIndicatorHeight, 0);
    uint _close_btn_padd = 10;

    QSize parent_size = reinterpret_cast<QWidget *>(parent) -> size();

    uint top = parent_size.height() / 2 - _close_btn_height / 2 - 2;

    close_btn_rect = QRect(_close_btn_padd, top, _close_btn_width, _close_btn_height);

    _close_btn_area_width = _close_btn_padd * 2 + close_btn_rect.width();
}

QSize TabBarItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);

    return size + QSize(_close_btn_area_width, 0);
}

void TabBarItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QStyledItemDelegate::paint(painter, option, index);

    QStyleOption opt;
    opt.rect = close_btn_rect.translated(option.rect.topRight() - QPoint(_close_btn_area_width, 0));

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

    painter -> drawLine(option.rect.topRight(), option.rect.bottomRight());
}

bool TabBarItemDelegate::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index) {
    switch(event -> type()) {
        case QEvent::MouseButtonPress: {
            QMouseEvent * e = reinterpret_cast<QMouseEvent *>(event);

            if (e) {
                QRect btn_rect = close_btn_rect.translated(option.rect.topRight() - QPoint(_close_btn_area_width, 0));

                if (btn_rect.contains(e -> pos())) {
                    emit closeTabRequested(index);
                    return true;
                }
            }
        break;}
        default: ;
    };

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
