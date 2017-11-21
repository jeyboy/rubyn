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

    QWidget * extra_area;
    QCompleter * completer;
    TextDocument * wrapper;
    OverlayInfo * overlay;

    EDITOR_POS_TYPE tooplip_block_num;
    EDITOR_POS_TYPE tooplip_block_pos;

    int folding_y;
    bool folding_click;

    int curr_block_number;

    int extra_zone_width;

    int line_number_height;
    int line_number_width;
    QFont curr_line_font;
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
    }
protected:
    void extraAreaPaintBlock(QPainter & painter,  const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom, const bool & is_current, const int & block_num);

    void showOverlay(const QTextBlock & block);
    void hideOverlay();

    bool blockOnScreen(const QTextBlock & block);

    QString wordUnderCursor(QTextCursor & tc, const WordUnderCursorOps & flags = wuco_full);
    void procSelectionIndent(const bool & right = true);

    inline QColor currentLineColor(const int & transparency = 16) { return QColor::fromRgb(128, 128, 128, transparency); } // QColor lineColor = QColor(Qt::yellow).lighter(160);

    bool event(QEvent * event);
    void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent * e);

    void drawFolding(QPainter & p, const int & x, const int & y, const bool & open, const bool & hover);

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
