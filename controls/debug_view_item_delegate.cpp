#include "debug_view_item_delegate.h"

#include "lexer/lexers_factory.h"
#include "lexer/ilexer.h"

DebugViewItemDelegate::DebugViewItemDelegate(QObject * parent) : QStyledItemDelegate(parent) {

}

void DebugViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    if (index.column() != 1)
        QStyledItemDelegate::paint(painter, option, index);

    ILexer * lexer = LexersFactory::obj().lexerFor(ft_file_rb);

    QString txt = index.data().toString();

    if (txt.isEmpty())
        QStyledItemDelegate::paint(painter, option, index);
    else {
        PseudoHighlighter highlighter(option.font, lexer, txt);

        QTextLayout * tl = highlighter.block(0);
        tl -> draw(painter, option.rect.topLeft(), QVector<QTextLayout::FormatRange>(), option.rect);
    }
}

QWidget * DebugViewItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QWidget * res = QStyledItemDelegate::createEditor(parent, option, index);

    res -> setStyleSheet(QLatin1Literal("border: none;"));
    res -> setMinimumWidth(12);
    res -> setFocus();

    return res;
}


//void ModelItemDelegate::drawCheckbox(bool is_container, QVariant & checkable, QPainter * painter, const QStyleOptionViewItem& option) const {
//    QStyleOptionButton checkboxstyle;
//    QRect rect = option.rect;
//    rect.setLeft(rect.left() + (is_container ? 4 : -3));
//    checkboxstyle.rect = rect;
//    checkboxstyle.state = option.state;
//    checkboxstyle.state |= checkable.toBool() ? QStyle::State_On : QStyle::State_Off;

//    QApplication::style() -> drawControl(QStyle::CE_CheckBox, &checkboxstyle, painter, &templateCheckbox);
//}
