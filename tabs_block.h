#ifndef TABS_BLOCK_H
#define TABS_BLOCK_H

#include <qwidget.h>

class QTabBar;
class QPushButton;
class CodeEditor;
class File;
class QLabel;

class TabsBlock : public QWidget {
    Q_OBJECT

    QTabBar * bar;

    QPushButton * list_btn;
    CodeEditor * editor;

    void setupLayout();
public:
    TabsBlock(QWidget * parent = 0);
    ~TabsBlock();

    void registerCursorPosOutput(QLabel * output);

    bool openFile(File * file);
};

#endif // TABS_BLOCK_H
