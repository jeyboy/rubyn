#ifndef CODE_EDITOR
#define CODE_EDITOR

#include <qapplication.h>
#include <qplaintextedit.h>
#include <qevent.h>
#include <qmimedata.h>

#include "misc/defines.h"

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class QPen;
class QCompleter;

class TextDocument;
class ExtraArea;
class File;
class OverlayInfo;

#define HPADDING 3
#define FOLDING_WIDTH 16
#define NO_FOLDING -100

#define PREPARE_PIXMAP(name, size) QPixmap(name).scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation)


//static QColor blendColors(const QColor &a, const QColor &b, int alpha)
//{
//    return QColor((a.red()   * (256 - alpha) + b.red()   * alpha) / 256,
//                  (a.green() * (256 - alpha) + b.green() * alpha) / 256,
//                  (a.blue()  * (256 - alpha) + b.blue()  * alpha) / 256);
//}

//static QColor calcBlendColor(const QColor &baseColor, int level, int count)
//{
//    QColor color80;
//    QColor color90;

//    if (baseColor.value() > 128) {
//        const int f90 = 15;
//        const int f80 = 30;
//        color80.setRgb(qMax(0, baseColor.red() - f80),
//                       qMax(0, baseColor.green() - f80),
//                       qMax(0, baseColor.blue() - f80));
//        color90.setRgb(qMax(0, baseColor.red() - f90),
//                       qMax(0, baseColor.green() - f90),
//                       qMax(0, baseColor.blue() - f90));
//    } else {
//        const int f90 = 20;
//        const int f80 = 40;
//        color80.setRgb(qMin(255, baseColor.red() + f80),
//                       qMin(255, baseColor.green() + f80),
//                       qMin(255, baseColor.blue() + f80));
//        color90.setRgb(qMin(255, baseColor.red() + f90),
//                       qMin(255, baseColor.green() + f90),
//                       qMin(255, baseColor.blue() + f90));
//    }

//    if (level == count)
//        return baseColor;
//    if (level == 0)
//        return color80;
//    if (level == count - 1)
//        return color90;

//    const int blendFactor = level * (256 / (count - 2));

//    return blendColors(color80, color90, blendFactor);
//}



class CodeEditor : public QPlainTextEdit {
    Q_OBJECT

    enum WordUnderCursorOps {
        wuco_full = 0,
        wuco_before_caret_part = 1,
        wuco_remove = 2,
        wuco_select = 4,

        wuco_remove_full = wuco_full | wuco_remove,
        wuco_remove_before_caret = wuco_before_caret_part | wuco_remove,
        wuco_select_full = wuco_full | wuco_select,
    };

    static QString word_boundary;

    ExtraArea * extra_area;
    QCompleter * completer;
    TextDocument * wrapper;
    OverlayInfo * overlay;

    EDITOR_POS_TYPE tooplip_block_num;
    EDITOR_POS_TYPE tooplip_block_pos;

    int folding_y;
//    bool folding_click;

    int curr_block_number;

    int extra_zone_width;

    int folding_offset_x;

    qreal symbol_width;

    int line_number_height;
    int line_number_width;
    QFont curr_line_font;

    QHash<DATA_FLAGS_TYPE, QPixmap> icons;
public:
    CodeEditor(QWidget * parent = 0);
    ~CodeEditor();

    void setCompleter(QCompleter * new_completer);

    void extraAreaMouseEvent(QMouseEvent * event);
    void extraAreaLeaveEvent(QEvent * event);
    void extraAreaPaintEvent(QPaintEvent * event);
    int extraAreaWidth();
    int foldingOffset();

    void openDocument(File * file);

    inline void setFont(const QFont & font) {
        curr_line_font = QFont(font.family(), font.pointSize());
        curr_line_font.setUnderline(true);
        curr_line_font.setBold(true);

        QPlainTextEdit::setFont(font);

        line_number_height = fontMetrics().height();

        symbol_width = QFontMetricsF(font).averageCharWidth();
    }
protected:
    void prepareIcons(const uint & size = FOLDING_WIDTH);

    void extraAreaPaintBlock(QPainter & painter,  const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom, const bool & is_current, const int & block_num);

    void showOverlay(const QTextBlock & block);
    void hideOverlay();

    bool blockOnScreen(const QTextBlock & block);

    QString wordUnderCursor(QTextCursor & tc, const WordUnderCursorOps & flags = wuco_full);
    void procSelectionIndent(const bool & right = true);

    inline QColor currentLineColor(const int & transparency = 16) { return QColor::fromRgb(128, 128, 128, transparency); } // QColor lineColor = QColor(Qt::yellow).lighter(160);

    bool event(QEvent * event);
    void paintEvent(QPaintEvent * e);
    void resizeEvent(QResizeEvent * e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent * e);

    bool canInsertFromMimeData(const QMimeData * source) const {
        return source -> hasUrls() || QPlainTextEdit::canInsertFromMimeData(source);
    }
    void insertFromMimeData(const QMimeData* source) {
        if (source -> hasUrls()) {
            QList<QUrl> urls = source -> urls();
            bool multiple(urls.count() > 1);

            for(QList<QUrl>::Iterator url = urls.begin(); url != urls.end(); url++)
                emit fileDropped(
                    (*url).adjusted(QUrl::NormalizePathSegments), // KDE may give a double slash
                    multiple
                );
        }
        else QPlainTextEdit::insertFromMimeData(source);
}

signals:
    void fileDropped(const QUrl & uri, bool multiple); // Multiple files are dropped?

private slots:
    void applyCompletion(const QString & completion);

    void highlightCurrentLine();

    void updateExtraAreaWidth(int newBlockCount);
    void updateExtraArea(const QRect &, int);
};

#endif // CODE_EDITOR
