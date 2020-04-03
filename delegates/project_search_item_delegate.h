#ifndef PROJECT_SEARCH_ITEM_DELEGATE_H
#define PROJECT_SEARCH_ITEM_DELEGATE_H

#include "delegates/base_item_delegate.h"

class ProjectSearchItemDelegate : public BaseItemDelegate {
    bool ignore_back_fill;
    QPixmap wave;
public:
    ProjectSearchItemDelegate(QObject * parent = nullptr);

    inline bool isFilled() { return !ignore_back_fill; }
    inline void setFill(const bool & fill) { ignore_back_fill = !fill; }
    inline void toggleFill() { ignore_back_fill = !ignore_back_fill; }
protected:
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
//    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // PROJECT_SEARCH_ITEM_DELEGATE_H
