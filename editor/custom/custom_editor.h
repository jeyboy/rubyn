#ifndef CUSTOMEDITOR_H
#define CUSTOMEDITOR_H

#include <qwidget.h>
#include "editor/ieditor.h"

class QEvent;
class QPaintEvent;
class QResizeEvent;
class QKeyEvent;
class QWheelEvent;
class QFocusEvent;
class QScrollArea;

namespace Custom {
    class Document;
    class DrawContext;
    class IBlock;

    class Editor : public QWidget, public IEditor {
        Q_OBJECT

        IBlock * _select_block;
        IBlock * _top_block;
        qreal _top_block_offset;
        quint32 _top_block_number;

        QPalette * line_num_section_pal;
        QPalette * content_section_pal;

        Document * _document;
        DrawContext * _context;

        QScrollBar * vscroll;
        uint vscroll_factor;
        QScrollBar * hscroll;
        uint hscroll_factor;

        void drawGrid();
        void drawDocument(QPainter & painter);
        void recalcScrolls();
        void initTopBlock(const bool & recalc = false);
    public:
        void intialize();

        explicit Editor(QWidget * parent = nullptr);
        ~Editor() Q_DECL_OVERRIDE;

        void openDocument(Document * doc = nullptr);
        void openDocument(File * file) Q_DECL_OVERRIDE;
        void clear() { openDocument(); }

        QScrollBar * verticalScrollBar() Q_DECL_OVERRIDE;

        void setVerticalScrollFactor(uint factor = 5) {
            vscroll_factor = factor;
        }
        void setHorizontalScrollFactor(uint factor = 5) {
            hscroll_factor = factor;
        }
        void setLeftMargin(const qint32 & margin = 0);

//        void setColor(const QPalette::ColorRole & acr, const QColor & acolor);

        void setVisible(bool visible) Q_DECL_OVERRIDE;

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
        void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
        void keyReleaseEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
        void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;
        void focusInEvent(QFocusEvent * e) Q_DECL_OVERRIDE;

//        virtual void mousePressEvent(QMouseEvent *event);
//        virtual void mouseReleaseEvent(QMouseEvent *event);
//        virtual void mouseDoubleClickEvent(QMouseEvent *event);
//        virtual void mouseMoveEvent(QMouseEvent *event);
//        virtual void focusOutEvent(QFocusEvent *event);
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


    signals:

    public slots:

    };
}


#endif // CUSTOMEDITOR_H
