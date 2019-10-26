#ifndef CUSTOMEDITOR_H
#define CUSTOMEDITOR_H

#include <QWidget>
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

//        QScrollArea * _scrollarea;
//        QWidget * _viewport;
        IBlock * _curr_block;

        Document * _document;
        DrawContext * _context;

        QScrollBar * vscroll;
        QScrollBar * hscroll;

        void drawDocument(QPainter & painter);
        void recalcScrolls();
    public:
        void intialize();

        explicit Editor(QWidget * parent = nullptr);
        ~Editor() Q_DECL_OVERRIDE;

        void setDocument(Document * doc);
        void clear();

        QScrollBar * verticalScrollBar() Q_DECL_OVERRIDE;

        void setVisible(bool visible) Q_DECL_OVERRIDE;

        void openDocument(File * file) Q_DECL_OVERRIDE;

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

    signals:

    public slots:
    };
}


#endif // CUSTOMEDITOR_H
