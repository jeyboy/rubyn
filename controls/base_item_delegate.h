#ifndef BASE_ITEM_DELEGATE_H
#define BASE_ITEM_DELEGATE_H

#include <qstyleditemdelegate.h>

class BaseItemDelegate : public QStyledItemDelegate {
public:
    BaseItemDelegate(QObject * parent = Q_NULLPTR);
protected:
    static QPixmap generateWavyPixmap(qreal max_radius, const QPen & pen);
};

#endif // BASE_ITEM_DELEGATE_H
