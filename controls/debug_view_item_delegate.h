#ifndef DEBUG_VIEW_ITEM_DELEGATE_H
#define DEBUG_VIEW_ITEM_DELEGATE_H

#include <qstyleditemdelegate.h>

#include "highlighter/pseudo_highlighter.h"

class DebugViewItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    static QLatin1String default_text;

    DebugViewItemDelegate(QObject * parent = Q_NULLPTR);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;

    QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;

signals:
    void editorShown(QWidget *);
};

#endif // DEBUG_VIEW_ITEM_DELEGATE_H
