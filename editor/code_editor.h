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


// replace text witout undo/redo clearing
//QTextDocument *doc = plainTextEdit->document();
//QTextCursor curs (doc);
//curs.select (QTextCursor::Document);
//curs.insertText (newText);



//TODO: get changed text
//void TextEdit::slotCheckRange(int pos, int removed, int added){
//    if(removed > 0){
//        undo();
//        QTextCursor c(textCursor());
//        c.setPosition(pos);
//        c.setPosition(pos + removed, QTextCursor::KeepAnchor);
//        qDebug() << "Removed: " << removed << " (" << c.selectedText() << ")";
//        redo();
//    }
//    if(added > 0){
//        QTextCursor c(textCursor());
//        c.setPosition(pos);
//        c.setPosition(pos + added, QTextCursor::KeepAnchor);
//        qDebug() << "Added: " << added << " (" << c.selectedText() << ")";
//    }
//}






// draw on additional things // need to use timer for redrawing of additional carets and other things

// http://doc.qt.io/qt-5/qobject.html#startTimer


// print doc

//QTextDocument *document = editor->document();
//QPrinter printer;

//QPrintDialog *dlg = new QPrintDialog(&printer, this);
//if (dlg->exec() != QDialog::Accepted)
//    return;

//document->print(&printer);



// vertical selection

//#include <QApplication>
//#include <QMouseEvent>
//#include <QWheelEvent>
//#include <QTextEdit>

//class TextEdit : public QTextEdit
//{
//public:
//    TextEdit(QWidget* parent = nullptr) : QTextEdit(parent),
//        startPos(0), endPos(0), absCursorStart(0), absCursorEnd(0) {}

//    void mouseMoveEvent(QMouseEvent* evt) {
//        if(!(evt->buttons() & Qt::LeftButton))
//            return;

//        auto cfp = cursorForPosition(evt->pos());
//        absCursorEnd = cfp.position() + startPos * 11;

//        if(evt->pos().y() < 0 && startPos > 0)
//            --startPos;
//        if(evt->pos().y() >= height() && endPos < textData.size())
//            ++startPos;

//        adjust();
//    }

//    void wheelEvent(QWheelEvent* evt) {
//        auto lines = evt->delta() / 100;
//        startPos = qBound(0, startPos - lines, textData.size());
//        adjust();
//    }

//    void mousePressEvent(QMouseEvent* evt) {
//        auto cfp = cursorForPosition(evt->pos());
//        setTextCursor(cfp);
//        absCursorStart = absCursorEnd = cfp.position() + startPos * 11;
//    }
//    void adjust() {
//        auto numLines = height() / fontMetrics().height() - 1;
//        auto size = qMin(textData.size(), numLines);
//        auto subText = QStringList(textData.mid(startPos, size)).join("\n");
//        setText(subText);
//        endPos = startPos + numLines;

//        auto numVisibleChars = (endPos - startPos) * 11 - 1;

//        auto localCursorStart = qBound(0, absCursorStart - startPos * 11, numVisibleChars);
//        auto localCursorEnd   = qBound(0, absCursorEnd - startPos * 11, numVisibleChars);

//        auto tc = textCursor();
//        tc.setPosition(localCursorEnd);
//        tc.setPosition(localCursorStart, QTextCursor::KeepAnchor);
//        setTextCursor(tc);
//    }

//    void resizeEvent(QResizeEvent* evt) {
//        QTextEdit::resizeEvent(evt);
//        adjust();
//    }

//    QStringList textData;
//    int startPos;
//    int endPos;
//    int absCursorStart;
//    int absCursorEnd;
//};

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    QStringList stuff;
//    for(int i = 0; i < 100; ++i)
//        stuff << QString(10, QChar('a' + (i % 30)));

//    TextEdit te;
//    te.textData = stuff;
//    te.show();

//    return a.exec();
//}



#define HPADDING 3
#define FOLDING_WIDTH 12
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

    ExtraArea * extra_area;
    QCompleter * completer;
    TextDocument * wrapper;
    OverlayInfo * overlay;

    EDITOR_POS_TYPE tooplip_block_num;
    EDITOR_POS_TYPE tooplip_block_pos;

    EDITOR_POS_TYPE extra_overlay_block_num;

    bool can_show_folding_popup;
    bool folding_click;
    int folding_y;
    int folding_overlay_y;

    QPoint curr_folding_limits;

    int curr_block_number;
    int screen_top_block_number;
    int screen_bottom_block_number;

    int extra_zone_width;

    int folding_offset_x;
    int folding_width;
    EDITOR_POS_TYPE folding_lines_coverage_min;
    EDITOR_POS_TYPE folding_lines_coverage_max;

    qreal symbol_width;
    uint chars_limit_line;

    int line_number_height;
    int line_number_width;

    QFont curr_line_font;

    QColor folding_content_color;
    QColor folding_border_color;
    QColor chars_limit_color;

    QHash<DATA_FLAGS_TYPE, QPixmap> icons;

    friend class ExtraArea;
public:
    CodeEditor(QWidget * parent = nullptr);
    ~CodeEditor() Q_DECL_OVERRIDE;

    void setCompleter(QCompleter * new_completer);

    void openDocument(File * file);

    void setFont(const QFont & font);
protected:
//    void _q_adjustScrollbars() {
//        QTextDocument * doc = document();
//        QPlainTextDocumentLayout * documentLayout = qobject_cast<QPlainTextDocumentLayout*>(doc -> documentLayout());

//        qreal margin = doc->documentMargin();

//        int vmax = 0;

//        int vSliderLength = 0;
//        if (!centerOnScroll() && isVisible()) {
//            QTextBlock block = doc->lastBlock();
//            const qreal visible = viewport->rect().height() - margin - 1;
//            qreal y = 0;
//            int visibleFromBottom = 0;

//            while (block.isValid()) {
//                if (!block.isVisible()) {
//                    block = block.previous();
//                    continue;
//                }
//                y += documentLayout->blockBoundingRect(block).height();

//                QTextLayout *layout = block.layout();
//                int layoutLineCount = layout->lineCount();
//                if (y > visible) {
//                    int lineNumber = 0;
//                    while (lineNumber < layoutLineCount) {
//                        QTextLine line = layout->lineAt(lineNumber);
//                        const QRectF lr = line.naturalTextRect();
//                        if (lr.top() >= y - visible)
//                            break;
//                        ++lineNumber;
//                    }
//                    if (lineNumber < layoutLineCount)
//                        visibleFromBottom += (layoutLineCount - lineNumber);
//                    break;

//                }
//                visibleFromBottom += layoutLineCount;
//                block = block.previous();
//            }
//            vmax = qMax(0, doc->lineCount() - visibleFromBottom);
//            vSliderLength = visibleFromBottom;

//        } else {
//            vmax = qMax(0, doc->lineCount() - 1);
//            int lineSpacing = q->fontMetrics().lineSpacing();
//            vSliderLength = lineSpacing != 0 ? viewport->height() / lineSpacing : 0;
//        }



//        QSizeF documentSize = documentLayout->documentSize();
//        vbar->setRange(0, qMax(0, vmax));
//        vbar->setPageStep(vSliderLength);
//        int visualTopLine = vmax;
//        QTextBlock firstVisibleBlock = q->firstVisibleBlock();
//        if (firstVisibleBlock.isValid())
//            visualTopLine = firstVisibleBlock.firstLineNumber() + topLine;

//        {
//            const QSignalBlocker blocker(vbar);
//            vbar->setValue(visualTopLine);
//        }

//        hbar->setRange(0, (int)documentSize.width() - viewport->width());
//        hbar->setPageStep(viewport->width());

//        setTopLine(vbar->value());
//    }

    static void fillBackground(QPainter * p, const QRectF & rect, QBrush brush, const QRectF & gradientRect = QRectF());

    void prepareIcons(const int & size = FOLDING_WIDTH);

    int widthWithoutScroll();
    int extraAreaWidth();
    int foldingOffset();

    void paintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom);
    void extraAreaPaintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom, const EDITOR_POS_TYPE & block_num);

    void drawFoldingOverlays(QPainter & painter, const QRect & target_rect);
    void drawCharsLimiter(QPainter & painter);
    void drawAdditionalCarets(QPainter & painter);

    void drawTextOverlay(QPainter & painter, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length);
    void drawFoldingOverlay(QPainter & painter, const QRect & fold_rect);

    void showFoldingContentPopup(const QTextBlock & block);
    void showOverlay(const QRect & rect, const QPixmap & overlay_img, const qint32 & subuid = -1);
    void showOverlay(const QTextBlock & block);
    void hideOverlay();
    void hideOverlayIfNoNeed();

    bool rectOnScreen(const QRect & r);
    bool blockOnScreen(const QTextBlock & block);

//    QString blockText(const EDITOR_POS_TYPE & block_num, const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length = -1);
    QRect textRect(const QTextBlock & block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length = 1);

    QString wordUnderCursor(QTextCursor & tc, const WordUnderCursorOps & flags = wuco_full);
    void procSelectionIndent(const bool & right = true);

    void extraAreaMouseEvent(QMouseEvent * event);
    void extraAreaLeaveEvent(QEvent * event);
    void extraAreaPaintEvent(QPaintEvent * event);

    void customPaintEvent(QPainter & painter, QPaintEvent * e);

    bool event(QEvent * event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent * e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent * e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent * e) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent * e) Q_DECL_OVERRIDE;

    bool canInsertFromMimeData(const QMimeData * source) const Q_DECL_OVERRIDE {
        return source -> hasUrls() || QPlainTextEdit::canInsertFromMimeData(source);
    }
    void insertFromMimeData(const QMimeData * source) Q_DECL_OVERRIDE {
        if (source -> hasUrls()) {
            QList<QUrl> urls = source -> urls();
//            bool multiple(urls.count() > 1);

            for(QList<QUrl>::Iterator url = urls.begin(); url != urls.end(); url++)
                emit fileDropped(
                    (*url).adjusted(QUrl::NormalizePathSegments)/*,*/ // KDE may give a double slash
//                    multiple
                );
        }
        else QPlainTextEdit::insertFromMimeData(source);
}

signals:
    void inFocus();
    void fileDropped(const QUrl & uri/*, bool multiple*/); // Multiple files are dropped?
    void cursorPosChanged(const QString & pos_coords);

private slots:
    void applyCompletion(const QString & completion);

    void highlightCurrentLine();

    void updateExtraAreaWidth(int newBlockCount);
    void updateExtraArea(const QRect &, int);
};

#endif // CODE_EDITOR
