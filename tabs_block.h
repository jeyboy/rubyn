#ifndef TABS_BLOCK_H
#define TABS_BLOCK_H

#include <qwidget.h>

class QTabBar;
class QPushButton;
class CodeEditor;
class File;

class TabsBlock : public QWidget {
    QTabBar * bar;

    QPushButton * list_btn;
    CodeEditor * editor;
public:
    TabsBlock(QWidget * parent = 0);
    ~TabsBlock();

    void openFile(File * file);
};

#endif // TABS_BLOCK_H
