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
class QPen;

class TextDocument;
class ExtraArea;
class File;

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

    void openDocument(File * file);
protected:
    bool event(QEvent * event);
    void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;

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
    void highlightCurrentLine();

    void updateExtraAreaWidth(int newBlockCount);
    void updateExtraArea(const QRect &, int);
};

#endif // CODE_EDITOR
