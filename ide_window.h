#ifndef IDE_WINDOW_H
#define IDE_WINDOW_H

#include <qmainwindow.h>
#include <qlist.h>

//https://www.youtube.com/watch?v=GwgF8GcynV0
//http://rusrails.ru/debugging-rails-applications
//http://guides.rubyonrails.org/debugging_rails_applications.html
//https://github.com/deivid-rodriguez/byebug/blob/master/GUIDE.md

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
protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
public:
    explicit IDEWindow(QWidget * parent = 0);
    ~IDEWindow();

protected slots:
    void textDocumentAdded(const QUrl & path);
public slots:
    void about();
    void newFile();
    void openFile(const QUrl & url = QUrl());
};

#endif // IDE_WINDOW_H
