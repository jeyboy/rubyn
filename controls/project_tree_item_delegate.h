#ifndef PROJECT_TREE_ITEM_DELEGATE_H
#define PROJECT_TREE_ITEM_DELEGATE_H

#include "controls/base_item_delegate.h"

class ProjectTreeItemDelegate : public BaseItemDelegate {
    bool ignore_back_fill;
    QPixmap wave;
public:
    ProjectTreeItemDelegate(QObject * parent = nullptr);

    inline bool isFilled() { return !ignore_back_fill; }
    inline void setFill(const bool & fill) { ignore_back_fill = !fill; }
    inline void toggleFill() { ignore_back_fill = !ignore_back_fill; }
protected:
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
//    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // PROJECT_TREE_ITEM_DELEGATE_H
