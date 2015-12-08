#ifndef CODE_EDITOR
#define CODE_EDITOR

#include <qplaintextedit.h>
#include <qwidget.h>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class LineNumberArea;

#define HPADDING 3

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT
    QWidget * lineNumberArea;
    QString currentPath;
    QString currentMime;

    void extractExtension() {
        currentMime = currentPath.section('.', -1, -1);
        if (currentMime != currentPath && currentMime.indexOf(' ') == -1)
            currentPath = currentPath.section('.', 0, -2);
        else currentMime.clear();
    }
public:
    CodeEditor(QWidget * parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent * event);
    int lineNumberAreaWidth();

    void openDocument(const QString & filePath);
protected:
    void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
};

#endif // CODE_EDITOR
