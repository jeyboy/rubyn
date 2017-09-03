#ifndef CODE_EDITOR
#define CODE_EDITOR

#include <qapplication.h>
#include <qplaintextedit.h>
#include <qevent.h>
#include <qmimedata.h>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class ExtraArea;
class IDocument;
class QPen;

#define HPADDING 3
#define FOLDING_WIDTH 16
#define NO_FOLDING -100

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT
    QWidget * extra_area;

    int folding_y;
    bool folding_click;
public:
    CodeEditor(QWidget * parent = 0);
    ~CodeEditor() {}

    void extraAreaMouseEvent(QMouseEvent * event);
    void extraAreaLeaveEvent(QEvent * event);
    void extraAreaPaintEvent(QPaintEvent * event);
    int extraAreaWidth();
    int foldingOffset();

    void openDocument(IDocument * doc);
protected:
    bool event(QEvent * event);
    void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;

    void drawFolding(QPainter & p, const int & x, const int & y, const bool & open, const bool & hover);

private slots:
    void highlightCurrentLine();

    void updateExtraAreaWidth(int newBlockCount);
    void updateExtraArea(const QRect &, int);
};

#endif // CODE_EDITOR
