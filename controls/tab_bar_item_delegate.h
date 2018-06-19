#ifndef TAB_BAR_ITEM_DELEGATE_H
#define TAB_BAR_ITEM_DELEGATE_H

#include <qstyleditemdelegate.h>
#include <qpushbutton.h>
#include <qdebug.h>
#include <qevent.h>

class TabBarItemDelegate  : public QStyledItemDelegate {
    Q_OBJECT

    uint _close_btn_area_width;
    QRect close_btn_rect;
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
