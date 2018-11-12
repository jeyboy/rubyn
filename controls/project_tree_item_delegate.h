#ifndef PROJECT_TREE_ITEM_DELEGATE_H
#define PROJECT_TREE_ITEM_DELEGATE_H

#include <qstyleditemdelegate.h>

class ProjectTreeItemDelegate : public QStyledItemDelegate {
public:
    ProjectTreeItemDelegate();
protected:
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // PROJECT_TREE_ITEM_DELEGATE_H
