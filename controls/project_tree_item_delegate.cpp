#include "project_tree_item_delegate.h"

#include <qpainter.h>
#include <qapplication.h>
#include <qdebug.h>

ProjectTreeItemDelegate::ProjectTreeItemDelegate() {}

void ProjectTreeItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QStyledItemDelegate::paint(painter, option, index);

    if (option.widget -> property("in_search").toBool()) {
        QVariant substr_start = index.data(Qt::UserRole + 10);

        if (substr_start.isValid()) {
            //    QRect r = QApplication::style() -> subElementRect(QStyle::SE_ItemViewItemDecoration, &option);

            QString item_text = index.data(Qt::DisplayRole).toString();
            int start_pos = substr_start.toInt();
            int highlight_len = option.widget -> property("search_len").toInt();

            int highlight_offset = option.fontMetrics.boundingRect(item_text.mid(0, start_pos)).width();
            int highlight_width = option.fontMetrics.boundingRect(item_text.mid(start_pos, highlight_len)).width();

            int text_height = option.fontMetrics.height();
            int voffset = qMax((option.rect.height() - text_height) / 2, 0);

            QRectF r = QRectF(
                option.rect.left() + highlight_offset + 10 + option.decorationSize.width() + .5,
                option.rect.top() + voffset,
                highlight_width,
                text_height
            );

            painter -> save();
            painter -> setCompositionMode(QPainter::CompositionMode_Multiply);
            painter -> setRenderHint(QPainter::Antialiasing);

            painter -> setPen(QColor(128, 128, 128, 128));
            painter -> setBrush(QColor(0, 255, 0, 48));

            painter -> drawRoundedRect(r, 3, 3);
            painter -> restore();


    //    QStyleOptionViewItem optionV4 = option;
    //    initStyleOption(&optionV4, index);

    //    QStyle *style = optionV4.widget? optionV4.widget->style() : QApplication::style();

    //    QTextDocument doc;
    //    doc.setHtml(optionV4.text);

    //    /// Painting item without text
    //    optionV4.text = QString();
    //    style->drawControl(QStyle::CE_ItemViewItem, &optionV4, painter);

    //    QAbstractTextDocumentLayout::PaintContext ctx;

    //    // Highlighting text if item is selected
    //    if (optionV4.state & QStyle::State_Selected)
    //        ctx.palette.setColor(QPalette::Text, optionV4.palette.color(QPalette::Active, QPalette::HighlightedText));

    //    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &optionV4);
    //    painter->save();
    //    painter->translate(textRect.topLeft());
    //    painter->setClipRect(textRect.translated(-textRect.topLeft()));
    //    doc.documentLayout()->draw(painter, ctx);
    //    painter->restore();
        }
    }
}

QSize ProjectTreeItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const {
//    QStyleOptionViewItem optionV4 = option;
//    initStyleOption(&optionV4, index);


//    QTextDocument doc;
//    doc.setHtml(optionV4.text);
//    doc.setTextWidth(optionV4.rect.width());
//    return QSize(doc.idealWidth(), doc.size().height());

    return QStyledItemDelegate::sizeHint(option, index);
}


