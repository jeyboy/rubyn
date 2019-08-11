#include "tree_view_item_delegate.h"

#include "lexer/lexers_factory.h"
#include "lexer/ilexer.h"

#include <qpainter.h>

QLatin1String TreeViewItemDelegate::default_text = QLatin1Literal("Evaluate...");

TreeViewItemDelegate::TreeViewItemDelegate(QObject * parent) : QStyledItemDelegate(parent) {

}

void TreeViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
//    int column_index = index.column();

    QString txt = index.data().toString();

//    bool skipable = column_index == 2 && txt == default_text;

//    if (!(column_index == 1 || !skipable))
//        QStyledItemDelegate::paint(painter, option, index);

//    if (column_index == 0 || skipable)
//        return;

    ILexer * lexer = LexersFactory::obj().lexerFor(ft_file_rb);

    if (!txt.isEmpty()) {
        PseudoHighlighter highlighter(option.font, lexer, txt);

        QTextLayout * tl = highlighter.block(0);
        QRect clip_rect(option.rect);

//        if (tl -> boundingRect().width() > clip_rect.width()) {

//        }

        painter -> setClipRect(clip_rect);
        tl -> draw(painter, option.rect.topLeft(), QVector<QTextLayout::FormatRange>());
    }
}

QWidget * TreeViewItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QWidget * res = QStyledItemDelegate::createEditor(parent, option, index);

    res -> setStyleSheet(QLatin1Literal("border: none;"));
    res -> setMinimumWidth(12);
    res -> setFocus();

    return res;
}
