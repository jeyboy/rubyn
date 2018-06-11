#include "tabs_block.h"

#include <qtabbar.h>
#include <qboxlayout.h>
#include <qpushbutton.h>

TabsBlock::TabsBlock(QWidget * content, QWidget * parent) : QWidget(parent), bar(0), list_btn(0) {
    bar = new QTabBar(this);

    QVBoxLayout * col_layout = new QVBoxLayout(this);

    col_layout -> setContentsMargins(1,1,1,1);

    QWidget * row = new QWidget(this);
    QHBoxLayout * row_layout = new QHBoxLayout(row);

    row_layout -> setContentsMargins(1,1,1,1);

    list_btn = new QPushButton(QLatin1Literal("10"), this);

    row_layout -> addWidget(bar, 1);
    row_layout -> addWidget(list_btn, 0);

    col_layout -> addWidget(row, 0);
    col_layout -> addWidget(content, 1);
}

TabsBlock::~TabsBlock() {
    delete bar;
}
