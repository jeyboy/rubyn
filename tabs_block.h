#ifndef TABS_BLOCK_H
#define TABS_BLOCK_H

#include <qwidget.h>

class QTabBar;
class QPushButton;

class TabsBlock : public QWidget {
    QTabBar * bar;

    QPushButton * list_btn;
public:
    TabsBlock(QWidget * content, QWidget * parent = 0);
    ~TabsBlock();
};

#endif // TABS_BLOCK_H
