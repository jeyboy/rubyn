#include "project_search_item_delegate.h"

#include <qpainter.h>
#include <qmath.h>
//#include <qapplication.h>

#include "misc/defines.h"

ProjectSearchItemDelegate::ProjectSearchItemDelegate(QObject * parent) : BaseItemDelegate(parent), ignore_back_fill(false) {
    wave = generateWavyPixmap(2, QPen(Qt::red, 2));
}

void ProjectSearchItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    if (!ignore_back_fill) {
        QVariant brush_var = index.data(TREE_COLOR_UID);

        if (brush_var.isValid()) {
            QBrush brush = qvariant_cast<QBrush>(brush_var);
            //TODO: wrong width if has horizontal scroll
            painter -> fillRect(option.rect.adjusted(-option.rect.left(), 0, option.widget -> width() - option.rect.width(), 0), brush);
        }
    }

    QStyledItemDelegate::paint(painter, option, index);

    int column_index = index.column();

    if (column_index == 1) {
        QVariant substr_start = index.data(PROJECT_SEARCH_MATCH_POS_UID);

        if (substr_start.isValid()) {
            QVariant substr_len = index.data(PROJECT_SEARCH_MATCH_LEN_UID);
            //    QRect r = QApplication::style() -> subElementRect(QStyle::SE_ItemViewItemDecoration, &option);

            QString item_text = index.data(Qt::DisplayRole).toString();
            int start_pos = substr_start.toInt();

            int highlight_offset = option.fontMetrics.boundingRect(item_text.mid(0, start_pos)).width();
            int highlight_width = option.fontMetrics.boundingRect(item_text.mid(start_pos, substr_len.toInt())).width();

            int text_height = option.fontMetrics.height();
            int voffset = qMax((option.rect.height() - text_height) / 2, 0);

            qreal xoffset = option.rect.left() + highlight_offset + 10 + option.decorationSize.width() - .5;
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

//    QVariant has_error_subline = index.data(TREE_HAS_ERROR_UID);
//    if (has_error_subline.isValid() && has_error_subline.toBool()) {
//        int sx = option.rect.left() + option.decorationSize.width() + 10;
//        int wy = 5;
//        int sy = option.rect.bottom() - wy;
//        int wx = option.rect.right() - sx;

//        painter -> setBrushOrigin(sx, sy);
//        painter -> setClipRect(sx, sy, wx, wave.height());
//        painter -> fillRect(sx, sy, wx, wy, wave);
//    }
}
