#include "project_tree_item_delegate.h"

#include <qpainter.h>
#include <qapplication.h>
#include <qdebug.h>

ProjectTreeItemDelegate::ProjectTreeItemDelegate() {}

void ProjectTreeItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QVariant brush_var = index.data(Qt::UserRole + 20);

    if (brush_var.isValid()) {
        QBrush brush = qvariant_cast<QBrush>(brush_var);
        painter -> fillRect(option.rect.adjusted(-option.rect.left(), 0, 0, 0), brush);
    }

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

            qreal xoffset = option.rect.left() + highlight_offset + 10 + option.decorationSize.width() + .5;
            xoffset = qMin(option.rect.right() - 16.0, xoffset);

            QRectF r = QRectF(
                xoffset,
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
        }
    }

    if (option.state & QStyle::State_Selected) {
        painter -> save();
        painter -> setCompositionMode(QPainter::CompositionMode_Multiply);
        painter -> setRenderHint(QPainter::Antialiasing);

        painter -> setPen(QColor(0, 0, 0, 128));
        painter -> setBrush(QColor(0, 0, 255, 8));

        painter -> drawRoundedRect(option.rect.adjusted(1, 1, -1, -1), 3, 3);
        painter -> restore();
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


