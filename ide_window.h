#ifndef IDE_WINDOW_H
#define IDE_WINDOW_H

#include <qmainwindow.h>
#include <qlist.h>

class QSplitter;

#include "parts/code_editor.h"

namespace Ui { class IDEWindow; }

class IDEWindow : public QMainWindow {
    Q_OBJECT

    Ui::IDEWindow * ui;
    CodeEditor * activeEditor;
    QSplitter * editorsSpliter;
    QList<CodeEditor *> editors;

    void setupEditor();
    void setupFileMenu();
    void setupHelpMenu();
    void setupSplitter();
public:
    explicit IDEWindow(QWidget * parent = 0);
    ~IDEWindow();

protected slots:
    void textDocumentAdded(QString path);
public slots:
    void about();
    void newFile();
    void openFile(const QString & path = QString());
};

#endif // IDE_WINDOW_H
