#ifndef IDE_WINDOW_H
#define IDE_WINDOW_H

#include <qmainwindow.h>
#include <qlist.h>
#include <qurl.h>

//https://www.youtube.com/watch?v=GwgF8GcynV0
//http://rusrails.ru/debugging-rails-applications
//http://guides.rubyonrails.org/debugging_rails_applications.html
//https://github.com/deivid-rodriguez/byebug/blob/master/GUIDE.md

class QSplitter;
class ProjectTree;
class TabsBlock;
class QLabel;
class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;
class File;

namespace Ui { class IDEWindow; }

class IDEWindow : public QMainWindow {
    Q_OBJECT

    Ui::IDEWindow * ui;

    TabsBlock * active_editor;
    QSplitter * widgets_list;

    ProjectTree * tree;

    QLabel * pos_status;

    void setupPosOutput();
    void setupEditor();
    void setupFileMenu();
    void setupHelpMenu();
    void setupSplitter();
protected:
    void setupToolWindows();

    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);
public:
    explicit IDEWindow(QWidget * parent = 0);
    ~IDEWindow();

protected slots:
    void fileOpenRequired(const QString & name, void * folder);
    void newEditorRequired(File * file);
    void editorActivated(TabsBlock *);
    void editorIsEmpty(TabsBlock *);

public slots:
    void about();
    void newFile();
    void openFile(const QUrl & url = QUrl());
    void openFolder(const QUrl & url = QUrl());
};

#endif // IDE_WINDOW_H
