#include "tabs_block.h"

#include "logger.h"
#include "editor/code_editor.h"
#include "project/file.h"

#include <qlabel.h>
#include <qtabbar.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qcompleter.h>

void TabsBlock::setupLayout() {
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

    editor = new CodeEditor(this);
    editor -> setFont(font);

    col_layout -> addWidget(editor, 1);
}

TabsBlock::TabsBlock(QWidget * parent) : QWidget(parent), bar(0), list_btn(0) {
    bar = new QTabBar(this);
    bar -> setTabsClosable(true);

    setupLayout();
}

TabsBlock::~TabsBlock() {
    delete bar;
}

void TabsBlock::registerCursorPosOutput(QLabel * output) {
    connect(editor, SIGNAL(cursorPosChanged(QString)), output, SLOT(setText(QString)));
}

bool TabsBlock::openFile(File * file) {
    switch(file -> baseFormatType()) {
        case ft_text: {
            editor -> openDocument(file);

            QStringList wordList;
            wordList << "alpha" << "omega" << "omicron" << "zeta";
            QCompleter * completer = new QCompleter(wordList, this);
            editor -> setCompleter(completer);
        break;}
        case ft_image: //{ emit parent() -> imageAdded(url); break;}
        case ft_binary: //{ emit parent() -> binaryAdded(url); break;}
        default: {
            Logger::obj().write(QLatin1Literal("IDE"), QLatin1Literal("Undefined format of file: '") % QString::number(file -> formatType()) % '\'',  Logger::log_error);
            return false;
        }
    };

    int index = bar -> addTab(file -> ico(), file -> name());
    bar -> setTabData(index, QVariant::fromValue<void *>(file));
    bar -> setCurrentIndex(index);

    if (isHidden())
        show();

    return true;
}
