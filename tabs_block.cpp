#include "tabs_block.h"

#include "editor/code_editor.h"
#include "project/file.h"

#include <qtabbar.h>
#include <qboxlayout.h>
#include <qpushbutton.h>

TabsBlock::TabsBlock(QWidget * parent) : QWidget(parent), bar(0), list_btn(0) {
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


    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(11);

    CodeEditor * editor = new CodeEditor(this);
    editor -> setFont(font);

    col_layout -> addWidget(editor, 1);
}

TabsBlock::~TabsBlock() {
    delete bar;
}

void TabsBlock::openFile(File * file) {

}
