#ifndef CODE_EDITOR
#define CODE_EDITOR

#include <qapplication.h>
#include <qplaintextedit.h>
#include <qevent.h>
#include <qmimedata.h>

#include "editor/ieditor.h"
#include "editor/active_para_info.h"
#include "editor/active_folding_info.h"
#include "editor/completer_info.h"
#include "editor/code_editor_searcher.h"


class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class QPen;

class Completer;
class TextDocument;
class ExtraArea;
class File;
class OverlayInfo;
class CodeEditorCache;
class CodeEditorCacheCell;


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



#define HPADDING 2
#define ICO_WIDTH 12
#define FOLDING_SCOPE_WIDTH 3
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



class CodeEditor : public QPlainTextEdit, public IEditor {
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

    CodeEditorCache * display_cacher;
    ExtraArea * extra_area;
    Completer * completer;
    TextDocument * wrapper;

    EDITOR_POS_TYPE tooplip_block_num;
    EDITOR_POS_TYPE tooplip_block_pos;

    bool change_scroll_pos_required;
    bool move_to_char_required;
    bool can_show_folding_popup;
    bool folding_click;
    int folding_y;
    int folding_overlay_y;

    QPoint curr_folding_limits;

    ActiveParaInfo para_info;
    ActiveParaInfo alt_para_info;
    ActiveFoldingInfo active_folding;
    CompleterInfo completer_info;

    int curr_block_number;

    int extra_zone_width;

    int extra_ico_offset_x;
    int extra_ico_width;

    int breakpoint_offset_x;
    int breakpoint_width;

    int folding_scope_offset_x;
    int folding_scope_width;

    int folding_offset_x;
    int folding_width;

    qreal symbol_width;
    uint chars_limit_line;
    int chars_limit_offset_x;

    int pseudo_tab_width;

    int line_number_offset_x;
    int line_number_height;
    int line_number_width;

    QHash<DATA_FLAGS_TYPE, QPixmap> icons;
    QHash<OVERLAY_POS_TYPE, OverlayInfo *> overlays;

    ////////// SETTINGS ////////////
    bool show_folding_scope_lines;
    bool show_folding_content_on_hover_overlay;
    bool unfold_on_click_overlay;
    bool show_foldings_panel;
    bool show_breakpoints_panel;
    bool show_extra_icons;
    ////////// END SETTINGS ////////////

    friend class ExtraArea;
public:
    CodeEditorSearcher searcher;

    CodeEditor(QWidget * parent = nullptr);
    ~CodeEditor() Q_DECL_OVERRIDE;

    void setCompleter(Completer * new_completer);

    inline bool hasDocument() { return document() != nullptr; }
    void openDocument(File * file) Q_DECL_OVERRIDE;
    const QString & documentUid();

    void setVisible(bool visible) Q_DECL_OVERRIDE;
    QScrollBar * verticalScrollBar() Q_DECL_OVERRIDE;
    QScrollBar * horizontalScrollBar() Q_DECL_OVERRIDE;

//    inline const QFont & font() const { return QPlainTextEdit::font(); }
    void setFont(const QFont & font);

    inline uint charsLimiterLineAt() { return chars_limit_line; }
    void setCharsLimiterLineAt(const uint & char_pos);

    void ensureVisibleBlock(const QTextBlock & block, const qint64 & char_in_line = 0);
    void ensureVisibleBlock(const qint64 & block_num, const qint64 & char_in_line = 0) Q_DECL_OVERRIDE;

    inline bool showFoldingScopeLines() { return show_folding_scope_lines; }
    inline void setShowFoldingScopeLines(const bool & show) {
        show_folding_scope_lines = show;
        viewport() -> update();
    }

    inline bool showFoldingContentOnHoverOverlay() { return show_folding_content_on_hover_overlay; }
    inline void setShowFoldingContentOnHoverOverlay(const bool & show) {
        show_folding_content_on_hover_overlay = show;
        viewport() -> update();
    }

    inline bool unfoldOnClickOverlay() { return unfold_on_click_overlay; }
    inline void setUnfoldOnClickOverlay(const bool & show) {
        unfold_on_click_overlay = show;
        viewport() -> update();
    }

    bool showSpacesAndTabs() {
        QTextDocument * doc = document();

        if (doc) {
            QTextOption option = doc -> defaultTextOption();

            return option.flags() & QTextOption::ShowTabsAndSpaces;
        }

        return false;
    }
    void setShowSpacesAndTabs(const bool & show) {
        QTextDocument * doc = document();

        if (doc) {
            QTextOption option = doc -> defaultTextOption();

            if ((option.flags() & QTextOption::ShowTabsAndSpaces) == show)
                return;

            if (show)
                option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
            else
                option.setFlags(option.flags() & ~QTextOption::ShowTabsAndSpaces);

            doc -> setDefaultTextOption(option);

            viewport() -> update();
        }
    }

    bool showLineAndParagraphSeparators() {
        QTextDocument * doc = document();

        if (doc) {
            QTextOption option = doc -> defaultTextOption();

            return option.flags() & QTextOption::ShowLineAndParagraphSeparators;
        }

        return false;
    }
    void setShowLineAndParagraphSeparators(const bool & show) {
        QTextDocument * doc = document();

        if (doc) {
            QTextOption option = doc -> defaultTextOption();

            if (show) {
                option.setFlags(option.flags() | QTextOption::ShowLineAndParagraphSeparators);
                option.setFlags(option.flags() | QTextOption::AddSpaceForLineAndParagraphSeparators);
            } else {
                option.setFlags(option.flags() & ~QTextOption::ShowLineAndParagraphSeparators);
                option.setFlags(option.flags() & ~QTextOption::AddSpaceForLineAndParagraphSeparators);
            }

            doc -> setDefaultTextOption(option);

            viewport() -> update();
        }
    }
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

    inline void setMouseCursor(const Qt::CursorShape & shape) { viewport() -> setCursor(QCursor(shape)); }
    inline void restoreDefaultMouseCursor() { setMouseCursor(Qt::IBeamCursor); }

    inline QTextBlock blockByNumber(int block_number) {
        return document() -> findBlockByNumber(block_number);
    }

//    void procRevision();
    void imitateClick();
    void prepareIcons(const int & size = ICO_WIDTH);

    int widthWithoutScroll();
    inline int extraAreaWidth() { return extra_zone_width; }
    inline int lineNumsWidth() { return symbol_width * qMax(1, QString::number(blockCount()).length()); }

    void paintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom);
    void extraAreaPaintBlock(QPainter & painter, CodeEditorCacheCell * cache);
    void extraAreaPaintBlock(QPainter & painter, const QTextBlock & block, const int & paint_top, const int & block_top, const int & block_bottom, const EDITOR_POS_TYPE & block_num);

    void drawParaOverlays(QPainter & painter);
    void drawFoldingOverlays(QPainter & painter, const QRect & target_rect);
    void drawSearchOverlays(QPainter & painter);
    void drawCharsLimiter(QPainter & painter);
    void drawAdditionalCarets(QPainter & painter);

    void drawTextOverlay(const UID_TYPE & draw_uid, QPainter & painter, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length);
    void drawTextOverlay(const UID_TYPE & draw_uid, QPainter & painter, const QRectF & fold_rect);

    void showFoldingContentPopup(const QTextBlock & block);

    bool isShowOverlayForBlock(const OVERLAY_POS_TYPE & overlay_type, const EDITOR_POS_TYPE & subuid);

    void showOverlay(const OVERLAY_POS_TYPE & overlay_type, const QRect & rect, const QPixmap & overlay_img, const qint32 & subuid = -1);
    void showOverlay(const OVERLAY_POS_TYPE & overlay_type, const UID_TYPE & draw_uid, const QTextBlock & block);
    void hideOverlay(const OVERLAY_POS_TYPE & overlay_type);
    void hideOverlays();

    void hideActiveParts();

    bool rectOnScreen(const QRect & r);
    inline bool blockOnScreen(const QTextBlock & block) { return rectOnScreen(blockRect(block).toRect()); }
    inline QRectF blockRect(const QTextBlock & block) { return blockBoundingGeometry(block).translated(contentOffset());  }

//    QString blockText(const EDITOR_POS_TYPE & block_num, const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & length = -1);   
    QRectF textRect(const QTextBlock & block, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length = 1);
    QRectF textRect(CodeEditorCacheCell * cache, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length = 1);
    QRectF textRect(QRectF & block_rect, const QTextLine & line, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length = 1);


    QString wordUnderCursor(QTextCursor & tc, const WordUnderCursorOps & flags = wuco_full);
    void procSelectionIndent(const bool & right = true);

    void extraAreaMouseEvent(QMouseEvent * event);
    void extraAreaLeaveEvent(QEvent * event);
    void extraAreaPaintEvent(QPaintEvent * event);

    void customPaintEvent(QPainter & painter, QPaintEvent * e);

    bool event(QEvent * e) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent * e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent * e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent * e) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent * e) Q_DECL_OVERRIDE;
//    virtual void showEvent(QShowEvent *) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent * e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent * e) Q_DECL_OVERRIDE;
//    virtual void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
//    virtual void mouseDoubleClickEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

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

    void procCompleterForCursor(QTextCursor & tc, const bool & initiate_popup = true);
    bool findPara(ActiveParaInfo & info, QTextBlock blk, ParaCell * para, int start_pos);
signals:
    void inFocus();
    void fileDropped(const QUrl & uri/*, bool multiple*/); // Multiple files are dropped?
    void cursorPosChanged(const QString & pos_coords);

    void lineChooseModalRequired();

    void searchRequired(const bool & show = true);
    void searchRequestRequired(const QString & pattern);
    void searchResultsFinded(const int & count);

public slots:
    void wordWrapChanged(const bool & word_wrap);
//    void searchIsShow(const bool & show) Q_DECL_OVERRIDE;
    void searchInitiated(const QRegularExpression & pattern, const bool & scroll = true) Q_DECL_OVERRIDE;
    void searchNextResult(QString * replace = nullptr) Q_DECL_OVERRIDE;
    void searchPrevResult(QString * replace = nullptr) Q_DECL_OVERRIDE;
    void searchRepaceAll(const QString & replace) Q_DECL_OVERRIDE;
    void searchClosed() Q_DECL_OVERRIDE;

private slots:
    void redrawRow(const EDITOR_POS_TYPE & line_num);
    void overlayHidden(const OVERLAY_POS_TYPE & uid);
    void applyCompletion(const QString & completion);

    void highlightCurrentLine();

    void cursorMoved();

    void updateExtraAreaWidth(int newBlockCount);
    void updateExtraArea(const QRect &, int);
};

#endif // CODE_EDITOR
