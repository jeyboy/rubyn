#include "debug_view_item_delegate.h"

#include "lexer/lexers_factory.h"
#include "lexer/ilexer.h"

#include <qpainter.h>

QLatin1String DebugViewItemDelegate::default_text = QLatin1Literal("Evaluate...");

DebugViewItemDelegate::DebugViewItemDelegate(QObject * parent) : QStyledItemDelegate(parent) {

}

void DebugViewItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    if ((option.state & QStyle::State_Editing) == 0 && (option.state & QStyle::State_MouseOver || option.state & QStyle::State_HasFocus || option.state & QStyle::State_Selected || option.state & QStyle::State_HasFocus)) {
        painter -> save();

        QPalette::ColorGroup cg = (option.state & QStyle::State_Enabled) ? QPalette::Normal : QPalette::Disabled;
        QColor color = option.palette.color(cg, (option.state & QStyle::State_Selected) ? QPalette::Highlight : QPalette::Window);
        color.setAlpha(48);
        painter -> setBrush(color);

        painter -> drawRoundedRect(option.rect.adjusted(0, 1, 0, -2), 3, 3);

        painter -> restore();
    }


    int column_index = index.column();

    QString txt = index.data().toString();

    bool skipable = column_index == 2 && txt == default_text;

//    if (!(column_index == 1 || !skipable))
//        QStyledItemDelegate::paint(painter, option, index);

    if (column_index == 0) {
        if (skipable)
            return;
    }

    ILexer * lexer = LexersFactory::obj().lexerFor(ft_file_rb);

    if (!txt.isEmpty()) {
        painter -> save();
        PseudoHighlighter highlighter(option.font, lexer, txt);

        QTextLayout * tl = highlighter.block(0);
        QRect clip_rect(option.rect.adjusted(0, 1, 0, -2));
        painter -> setClipRect(clip_rect);
        tl -> draw(painter, option.rect.topLeft() + QPoint(2, 0), QVector<QTextLayout::FormatRange>());
        painter -> restore();
    }
}

QWidget * DebugViewItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QWidget * res = QStyledItemDelegate::createEditor(parent, option, index);

    res -> setStyleSheet(QLatin1Literal("border: none;"));
    res -> setMinimumWidth(12);
    res -> setBaseSize(-1, -1);
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
