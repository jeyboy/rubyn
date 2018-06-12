#ifndef TABS_BLOCK_H
#define TABS_BLOCK_H

#include <qwidget.h>

class TabBar;
class QPushButton;
class CodeEditor;
class File;
class QLabel;

class TabsBlock : public QWidget {
    Q_OBJECT

    TabBar * bar;

    QPushButton * list_btn;
    CodeEditor * editor;

    void setupLayout();
    bool openFileInEditor(File * file);
public:
    TabsBlock(QWidget * parent = 0);
    ~TabsBlock();

    void registerCursorPosOutput(QLabel * output);

    bool openFile(File * file);

protected slots:
    void showTabsList();
    void tabsLayoutChanged();
    void currentTabChanged(int);
    void tabRemoved(int);
};

#endif // TABS_BLOCK_H
