#ifndef TREE_VIEW_ITEM_DELEGATE_H
#define TREE_VIEW_ITEM_DELEGATE_H

#include <qstyleditemdelegate.h>

#include "highlighter/pseudo_highlighter.h"

class TreeViewItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    static QLatin1String default_text;

    TreeViewItemDelegate(QObject * parent = Q_NULLPTR);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;

    QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;
signals:
    void editorShown(QWidget *);
};

#endif // TREE_VIEW_ITEM_DELEGATE_H
