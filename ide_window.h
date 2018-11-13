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
class ColorPicker;

class QLabel;
class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;
class File;
class Dumper;
class RunConfiguration;

namespace Ui { class IDEWindow; }

class IDEWindow : public QMainWindow {
    Q_OBJECT

    Ui::IDEWindow * ui;

    TabsBlock * active_editor;
    QSplitter * widgets_list;

    ProjectTree * tree;
    ColorPicker * color_picker;
    Dumper * ui_dumper;

    RunConfiguration * run_config;

    QLabel * pos_status;

    void setupPosOutput();
    void setupEditor();
    void setupFileMenu();
    void setupHelpMenu();
    void setupSplitter();

    void loadSettings();
    void saveSettings();

    friend class Dumper;
protected:
    void setupToolWindows();

    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *);

    void closeEvent(QCloseEvent *);
public:
    explicit IDEWindow(QWidget * parent = nullptr);
    ~IDEWindow();

protected slots:
    void splitterMoved(int pos, int index);
    void fileOpenRequired(const QString & name, void * folder, const bool & in_new = false, const int & scroll_pos_y = 0);
    void newEditorRequired(File * file, const bool & is_external = false);
    void setActiveEditor(TabsBlock *);
    void editorIsEmpty(TabsBlock *);
    void openResource(TabsBlock * target_editor, const QUrl & url);
    void selectCurrentFileInTree();

public slots:
    void about();
    void newFile();
    void newFolder();
    void openFile(const QUrl & url = QUrl());
    void openFolder(const QUrl & url = QUrl());
};

#endif // IDE_WINDOW_H
