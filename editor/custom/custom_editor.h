#ifndef CUSTOMEDITOR_H
#define CUSTOMEDITOR_H

#include <qwidget.h>

#include "editor/ieditor.h"
#include "editor/completer_info.h"
#include "custom_editor_searcher.h"
#include "custom_cursor.h"

class QEvent;
class QPaintEvent;
class QResizeEvent;
class QKeyEvent;
class QWheelEvent;
class QFocusEvent;
class QTimer;

class Completer;

namespace Custom {
    class Document;
    class DrawContext;
    class IBlock;

    class Editor : public QWidget, public IEditor {
        Q_OBJECT

//        CompleterInfo _completer_info;
        EditorSearcher searcher;

        QTimer * _back_timer;
        Completer * _completer;
        Document * _document;
        DrawContext * _context;

        QScrollBar * _vscroll;
        QScrollBar * _hscroll;

        void blickCursor();
        void nonBlickCursor();

        void drawDocument(QPainter & painter);

        void recalcScrolls();
        void ensureVisibleCurrentBlock(const qint64 & char_in_line = 0);
    public:
        void intialize();

        explicit Editor(QWidget * parent = nullptr);
        ~Editor() Q_DECL_OVERRIDE;

        void openDocument(Document * doc = nullptr);
        void openDocument(File * file) Q_DECL_OVERRIDE;

        void setCompleter(Completer * new_completer);

        void setTextCursorWidth(const qreal & new_width);

        void setTextCursor(const Cursor & cursor);
        Cursor & textCursor();
        Cursor textCursorForPos(const QPointF & pos);

        void clear() { openDocument(); }

        void hideBlock(IBlock * block);
        void showBlock(IBlock * block);

        void ensureVisibleBlock(const qint64 & block_num, const qint64 & char_in_line = 0) Q_DECL_OVERRIDE;
        void ensureVisibleBlock(IBlock * block, const qint64 & char_in_line = 0);

        QScrollBar * verticalScrollBar() Q_DECL_OVERRIDE;

        void setVerticalScrollFactor(uint factor = 5);
        void setHorizontalScrollFactor(uint factor = 5);
        void setLeftMargin(const qint32 & margin = 0);

        int tabFactor();
        void setTabFactor(const int & new_tab_factor = 5);

//        void setColor(const QPalette::ColorRole & acr, const QColor & acolor);

        void setVisible(bool visible) Q_DECL_OVERRIDE;
        bool blockIsVisible(IBlock * block);

        void ensureVisible(IBlock * block);
        void ensureVisible(const qint64 & block_num);

    //  void searchIsShow(const bool & show) = 0;
        void searchInitiated(const QRegularExpression & pattern, const bool & scroll = true) Q_DECL_OVERRIDE;
        void searchNextResult(QString * replace = nullptr) Q_DECL_OVERRIDE;
        void searchPrevResult(QString * replace = nullptr) Q_DECL_OVERRIDE;
        void searchRepaceAll(const QString & replace) Q_DECL_OVERRIDE;
        void searchClosed() Q_DECL_OVERRIDE;

    protected:
        bool event(QEvent * e) Q_DECL_OVERRIDE;
        void paintEvent(QPaintEvent * e) Q_DECL_OVERRIDE;
        void resizeEvent(QResizeEvent * e) Q_DECL_OVERRIDE;
        void customKeyPressEvent(QKeyEvent * e);
        void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
        void keyReleaseEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
        void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;
        void focusInEvent(QFocusEvent * e) Q_DECL_OVERRIDE;
//        void focusOutEvent(QFocusEvent * e) Q_DECL_OVERRIDE;

        void mousePressEvent(QMouseEvent * e) Q_DECL_OVERRIDE;
        void mouseDoubleClickEvent(QMouseEvent * e) Q_DECL_OVERRIDE;

//        virtual void mouseReleaseEvent(QMouseEvent *event);
//        virtual void mouseMoveEvent(QMouseEvent *event);
//        virtual void enterEvent(QEvent *event);
//        virtual void leaveEvent(QEvent *event);
//        virtual void moveEvent(QMoveEvent *event);
//        virtual void closeEvent(QCloseEvent *event);
//        virtual void contextMenuEvent(QContextMenuEvent *event);

//        virtual void tabletEvent(QTabletEvent *event);
//        virtual void actionEvent(QActionEvent *event);

//        virtual void dragEnterEvent(QDragEnterEvent *event);
//        virtual void dragMoveEvent(QDragMoveEvent *event);
//        virtual void dragLeaveEvent(QDragLeaveEvent *event);
//        virtual void dropEvent(QDropEvent *event);

//        virtual void showEvent(QShowEvent *event);
//        virtual void hideEvent(QHideEvent *event);

        bool focusNextPrevChild(bool next) Q_DECL_OVERRIDE;

    signals:
        void lineChooseModalRequired();

        void searchRequired(const bool & show = true);
        void searchRequestRequired(const QString & pattern);
        void searchResultsFinded(const int & count);


    public slots:


    private slots:
        void applyCompletion(const QString & completion);
    };
}


#endif // CUSTOMEDITOR_H
