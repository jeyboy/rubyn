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

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT
    QWidget * extraArea;
public:
    CodeEditor(QWidget * parent = 0);
    ~CodeEditor() {}

    void extraAreaPaintEvent(QPaintEvent * event);
    int extraAreaWidth();

    void openDocument(IDocument * doc);
protected:
    void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;

private slots:
    void highlightCurrentLine();

    void updateExtraAreaWidth(int newBlockCount);
    void updateExtraArea(const QRect &, int);
};

#endif // CODE_EDITOR
