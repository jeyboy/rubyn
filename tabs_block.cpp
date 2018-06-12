#include "tabs_block.h"

#include "tab_bar.h"
#include "logger.h"
#include "editor/code_editor.h"
#include "project/file.h"

#include <qlabel.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qcompleter.h>
#include <qdebug.h>

void TabsBlock::setupLayout() {
    QVBoxLayout * col_layout = new QVBoxLayout(this);

    col_layout -> setContentsMargins(1,1,1,1);

    QWidget * row = new QWidget(this);
    QHBoxLayout * row_layout = new QHBoxLayout(row);

    row_layout -> setContentsMargins(1,1,1,1);

    list_btn = new QPushButton(QLatin1Literal("0"), this);

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
    bar = new TabBar(this);
    bar -> setTabsClosable(true);
    bar -> setExpanding(false);
    bar -> setMovable(true);
    bar -> setChangeCurrentOnDrag(true);

    setupLayout();

    connect(bar, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
    connect(bar, SIGNAL(tabCloseRequested(int)), this, SLOT(tabRemoved(int)));
    connect(bar, SIGNAL(layoutChanged()), this, SLOT(tabsLayoutChanged()));
//    void tabMoved(int from, int to);
}

TabsBlock::~TabsBlock() {
    delete bar;
}

void TabsBlock::registerCursorPosOutput(QLabel * output) {
    connect(editor, SIGNAL(cursorPosChanged(QString)), output, SLOT(setText(QString)));
}

bool TabsBlock::openFile(File * file) {
    if (tab_links.contains(file -> uid())) {
        int new_index = tab_links[file -> uid()];
        currentTabChanged(new_index);
        bar -> setCurrentIndex(new_index);

        return true;
    } else {
        if (!openFileInEditor(file))
            return false;

        int index = bar -> addTab(file -> ico(), file -> name());
        bar -> setTabData(index, QVariant::fromValue<void *>(file));
        bar -> setCurrentIndex(index);

        tab_links.insert(file -> uid(), index);

        if (isHidden())
            show();
    }

    return true;
}

bool TabsBlock::openFileInEditor(File * file) {
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

    return true;
}

void TabsBlock::rebuildIndexes(const int & rindex) {
    QMutableHashIterator<QString, int> i(tab_links);

    while (i.hasNext()) {
        i.next();

        if (i.value() == rindex)
            i.remove();
        else {
            if (i.value() > rindex)
                --i.value();
        }
    }
}

void TabsBlock::showTabsList() {
    //TODO: implement me
}

void TabsBlock::tabsLayoutChanged() {
    list_btn -> setText(QString::number(bar -> count()));
}

void TabsBlock::currentTabChanged(int index) {
    QVariant tab_data = bar -> tabData(index);

    if (!tab_data.isNull()) {
        File * file = (File *)tab_data.value<void *>();

        if (!openFileInEditor(file)) {
            // notify user
        }
    } else {
        // notify user
    }
}

void TabsBlock::tabRemoved(int index) {
    rebuildIndexes(index);

    bar -> removeTab(index);

    if (bar -> count() == 0)
        hide();
}
