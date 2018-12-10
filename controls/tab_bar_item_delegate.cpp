#include "tab_bar_item_delegate.h"

#include <qpainter.h>
#include <qapplication.h>
#include <qevent.h>
#include <qpushbutton.h>
#include <qdebug.h>

//TODO: fill all except icon zone - icon should output in white circle

TabBarItemDelegate::TabBarItemDelegate(QObject * parent) : BaseItemDelegate(parent) {
    wave = generateWavyPixmap(2, QPen(Qt::red, 2));

    int _close_btn_width = QApplication::style() -> pixelMetric(QStyle::PM_TabCloseIndicatorWidth, nullptr);
    int _close_btn_height = QApplication::style() -> pixelMetric(QStyle::PM_TabCloseIndicatorHeight, nullptr);
    int _close_btn_padd = 10;

    QSize parent_size = reinterpret_cast<QWidget *>(parent) -> size();

    int top = parent_size.height() / 2 - _close_btn_height / 2 - 2;

    close_btn_rect = QRect(_close_btn_padd, top, _close_btn_width, _close_btn_height);

    _close_btn_area_width = _close_btn_padd * 2 + close_btn_rect.width();
}

QSize TabBarItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);

    return size + QSize(_close_btn_area_width, 0);
}

void TabBarItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QStyleOptionViewItem item_opt(option);
    item_opt.state ^= QStyle::State_Selected;

    QStyledItemDelegate::paint(painter, item_opt, index);

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

//STATE: QFlags<QStyle::StateFlag>(State_Enabled|State_AutoRaise|State_Selected)
//STATE: QFlags<QStyle::StateFlag>(State_Enabled|State_AutoRaise|State_MouseOver|State_Selected)
//STATE: QFlags<QStyle::StateFlag>(State_Enabled|State_HasFocus|State_AutoRaise|State_MouseOver|State_Selected|State_Active)
//STATE: QFlags<QStyle::StateFlag>(State_Enabled|State_HasFocus|State_AutoRaise|State_MouseOver|State_Selected|State_Active)
//STATE: QFlags<QStyle::StateFlag>(State_Enabled|State_HasFocus|State_AutoRaise|State_Selected|State_Active)
//STATE: QFlags<QStyle::StateFlag>(State_Enabled|State_AutoRaise|State_Selected)

    if ((option.state & QStyle::State_Selected) == 0) {
        painter -> fillRect(QRect(option.rect.bottomLeft() - QPoint(0, 1), option.rect.bottomRight() + QPoint(0, 1)), QBrush(QColor::fromRgb(0,0,0, 192)));
    }

    QApplication::style() -> drawPrimitive(QStyle::PE_IndicatorTabClose, &opt, painter);

    painter -> drawLine(option.rect.topRight(), option.rect.bottomRight());

    QVariant has_error_subline = index.data(Qt::UserRole + 21);
    if (has_error_subline.isValid() && has_error_subline.toBool()) {
        painter -> save();
        int sx = option.rect.left() + option.decorationSize.width() + 10;
        int wy = 6;
        int sy = option.rect.bottom() - wy;
        int wx = option.rect.right() - _close_btn_area_width - 2 - sx;

        painter -> setBrushOrigin(sx, sy);
        painter -> setClipRect(sx, sy, wx, wave.height());
        painter -> fillRect(sx, sy, wx, wy, wave);
        painter -> restore();
    }
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
