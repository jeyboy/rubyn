#include "project_search_item_delegate.h"

#include <qpainter.h>
#include <qmath.h>
//#include <qapplication.h>

#include "misc/defines.h"

ProjectSearchItemDelegate::ProjectSearchItemDelegate(QObject * parent) : BaseItemDelegate(parent), ignore_back_fill(false) {
    wave = generateWavyPixmap(2, QPen(Qt::red, 2));
}

void ProjectSearchItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
//    if (!ignore_back_fill) {
//        QVariant brush_var = index.data(TREE_COLOR_UID);

//        if (brush_var.isValid()) {
//            QBrush brush = qvariant_cast<QBrush>(brush_var);
//            //TODO: wrong width if has horizontal scroll
//            painter -> fillRect(option.rect.adjusted(-option.rect.left(), 0, option.widget -> width() - option.rect.width(), 0), brush);
//        }
//    }

    QStyleOptionViewItem opt = option;
    opt.rect.adjust(0, 0, 0, -4);

    QStyledItemDelegate::paint(painter, opt, index);

    int column_index = index.column();

    if (column_index == 1) {
        int reverse_offset = -(option.widget -> rect().width() - 25/* - 100*/ - opt.rect.width());
        QVariant substr_start = index.data(PROJECT_SEARCH_MATCH_POS_UID);

        if (substr_start.isValid()) {
            //////////////
            painter -> save();
            painter -> setCompositionMode(QPainter::CompositionMode_Multiply);
            painter -> setRenderHint(QPainter::Antialiasing);

            painter -> setPen(QColor(0, 0, 0, 8));
            painter -> setBrush(QColor(128, 128, 128, 12));

            painter -> drawRoundedRect(opt.rect.adjusted(reverse_offset, 1, -1, -1), 3, 3);
            painter -> restore();
            //////////////


            QVariant substr_len = index.data(PROJECT_SEARCH_MATCH_LEN_UID);
            //    QRect r = QApplication::style() -> subElementRect(QStyle::SE_ItemViewItemDecoration, &opt);

            QString item_text = index.data(Qt::DisplayRole).toString();
            int start_pos = substr_start.toInt();

            int highlight_offset = opt.fontMetrics.boundingRect(item_text.mid(0, start_pos)).width();
            int highlight_width = opt.fontMetrics.boundingRect(item_text.mid(start_pos, substr_len.toInt())).width();

            int text_height = opt.fontMetrics.height();
            int voffset = qMax((opt.rect.height() - text_height) / 2, 0);

            qreal xoffset = opt.rect.left() + highlight_offset + 6/* + opt.decorationSize.width()*/ - .5;
            xoffset = qMin(opt.rect.right() - 16.0, xoffset);

            QRectF r = QRectF(
                xoffset,
                opt.rect.top() + voffset,
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

//    if (opt.state & QStyle::State_Selected) {
//        painter -> save();
//        painter -> setCompositionMode(QPainter::CompositionMode_Multiply);
//        painter -> setRenderHint(QPainter::Antialiasing);

//        painter -> setPen(QColor(0, 0, 0, 128));
//        painter -> setBrush(QColor(0, 0, 255, 8));

//        painter -> drawRoundedRect(opt.rect.adjusted(1, 1, -1, -1), 3, 3);
//        painter -> restore();
//    }

//    QVariant has_error_subline = index.data(TREE_HAS_ERROR_UID);
//    if (has_error_subline.isValid() && has_error_subline.toBool()) {
//        int sx = opt.rect.left() + opt.decorationSize.width() + 10;
//        int wy = 5;
//        int sy = opt.rect.bottom() - wy;
//        int wx = opt.rect.right() - sx;

//        painter -> setBrushOrigin(sx, sy);
//        painter -> setClipRect(sx, sy, wx, wave.height());
//        painter -> fillRect(sx, sy, wx, wy, wave);
//    }
}

QSize ProjectSearchItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const {
   QSize sz = BaseItemDelegate::sizeHint(option, index);
   sz.setHeight(sz.height() + 8);
   return sz;
}
