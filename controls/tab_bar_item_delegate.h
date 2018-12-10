#ifndef TAB_BAR_ITEM_DELEGATE_H
#define TAB_BAR_ITEM_DELEGATE_H

#include "controls/base_item_delegate.h"

class TabBarItemDelegate  : public BaseItemDelegate {
    Q_OBJECT

    int _close_btn_area_width;
    QRect close_btn_rect;
    QPixmap wave;
public:
    TabBarItemDelegate(QObject * parent);

    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

protected:
    bool editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index);
signals:
    void closeTabRequested(const QModelIndex &);
};

#endif // TAB_BAR_ITEM_DELEGATE_H
