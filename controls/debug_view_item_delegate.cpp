#include "debug_view_item_delegate.h"

#include "lexer/lexers_factory.h"
#include "lexer/ilexer.h"

#include <qpainter.h>

QLatin1String DebugViewItemDelegate::default_text = QLatin1Literal("Evaluate...");

DebugViewItemDelegate::DebugViewItemDelegate(QObject * parent) : QStyledItemDelegate(parent) {

}

void DebugViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    int column_index = index.column();

    QString txt = index.data().toString();

    bool skipable = column_index == 2 && txt == default_text;

    QStyledItemDelegate::paint(painter, option, column_index == 1 || !skipable ? QModelIndex() : index);

    if (column_index == 0 || skipable)
        return;

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
