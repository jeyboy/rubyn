#ifndef IDE_WINDOW_H
#define IDE_WINDOW_H

#include <qmainwindow.h>

#include "parts/code_editor.h"

namespace Ui { class IDEWindow; }

class IDEWindow : public QMainWindow {
    Q_OBJECT

    Ui::IDEWindow * ui;
    CodeEditor * editor;
public:
    explicit IDEWindow(QWidget * parent = 0);
    ~IDEWindow();

public slots:
    void about();
    void newFile();
    void openFile(const QString & path = QString());

private:
    void setupEditor();
    void setupFileMenu();
    void setupHelpMenu();

//    Highlighter *highlighter;
};

#endif // IDE_WINDOW_H
