#include "tree_view_item_delegate.h"

#include "lexer/lexers_factory.h"
#include "lexer/ilexer.h"

#include <qpainter.h>

QLatin1String TreeViewItemDelegate::default_text = QLatin1Literal("Evaluate...");

TreeViewItemDelegate::TreeViewItemDelegate(QObject * parent) : QStyledItemDelegate(parent) {

}

void TreeViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
//    int column_index = index.column();

    if (option.state & QStyle::State_MouseOver || option.state & QStyle::State_HasFocus || option.state & QStyle::State_Selected) {
        painter -> save();

        QPalette::ColorGroup cg = (option.state & QStyle::State_Enabled) ? QPalette::Normal : QPalette::Disabled;
        QColor color = option.palette.color(cg, (option.state & QStyle::State_Selected) ? QPalette::Highlight : QPalette::Window);
        color.setAlpha(32);
        painter -> setBrush(color);

        painter -> drawRoundedRect(option.rect.adjusted(0, 1, 0, -2), 3, 3);

        painter -> restore();
    }

    QString txt = index.data().toString();

    ILexer * lexer = LexersFactory::obj().lexerFor(ft_file_rb);

    if (!txt.isEmpty()) {
        painter -> save();

        PseudoHighlighter highlighter(option.font, lexer, txt);

        QTextLayout * tl = highlighter.block(0);
        QRect clip_rect(option.rect.adjusted(1, 2, 1, -4));
        painter -> setClipRect(clip_rect);
        tl -> draw(painter, option.rect.topLeft() + QPoint(2, 0), QVector<QTextLayout::FormatRange>());
        painter -> restore();
    }
}

QWidget * TreeViewItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QWidget * res = QStyledItemDelegate::createEditor(parent, option, index);

    res -> setStyleSheet(QLatin1Literal("border: none;"));
    res -> setMinimumWidth(12);
    res -> setFocus();

    return res;
}
