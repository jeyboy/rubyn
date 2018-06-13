#include "tabs_block.h"

#include "tab_bar.h"
#include "logger.h"
#include "editor/code_editor.h"
#include "project/file.h"

#include <qlabel.h>
#include <qboxlayout.h>
#include <qtoolbutton.h>
#include <qcompleter.h>
#include <qmenu.h>
#include <qdebug.h>

void TabsBlock::setupLayout() {
    QVBoxLayout * col_layout = new QVBoxLayout(this);

    col_layout -> setContentsMargins(1,1,1,1);

    QWidget * row = new QWidget(this);
    QHBoxLayout * row_layout = new QHBoxLayout(row);

    row_layout -> setContentsMargins(1,1,1,1);

    bar = new TabBar(this);
    bar -> setTabsClosable(true);
    bar -> setExpanding(false);
    bar -> setMovable(true);
    bar -> setChangeCurrentOnDrag(true);
    bar -> setContextMenuPolicy(Qt::CustomContextMenu);

    row_layout -> addWidget(bar, 1);

    list_btn = new QToolButton(this);
    list_btn -> setText(QLatin1Literal("0"));
    list_btn -> setIcon(QIcon(QLatin1Literal(":/list")));
    list_btn -> setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

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

TabsBlock::TabsBlock(QWidget * parent) : QWidget(parent), bar(0), list_btn(0), menu_target_index(-1) {
//    setStyleSheet("QWidget:focus {background-color: #FFFFCC;}");

    setupLayout();

    connect(bar, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
    connect(bar, SIGNAL(tabCloseRequested(int)), this, SLOT(tabRemoved(int)));
    connect(bar, SIGNAL(layoutChanged()), this, SLOT(tabsLayoutChanged()));
    connect(bar, SIGNAL(tabMoved(int,int)), this, SLOT(tabMoved(int,int)));
    connect(bar, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showTabsContextMenu(const QPoint &)));

    connect(editor, SIGNAL(inFocus()), this, SLOT(inFocus()));

//    connect(editor, SIGNAL(fileDropped(QUrl)), this, SLOT(openFile(QUrl)));
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

void TabsBlock::currentTabChanged(const int & index) {
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

void TabsBlock::tabRemoved(const int & index) {
    rebuildIndexes(index);

    bar -> removeTab(index);

    if (bar -> count() == 0) {
        emit moveToBlankState(this);
        hide();
    }
}

void TabsBlock::tabMoved(const int & from, const int & to) {
//    int direction = from > to ? -1 : 1;

//    qDebug() << "MOVE" << from << to;

//    QMutableHashIterator<QString, int> i(tab_links);

//    while (i.hasNext()) {
//        i.next();

//        int pos = i.value();

//        qDebug() << "!!!" << pos << from << to;

//        if (direction < 0) {
//            if (pos > from && pos <= to)
//                --i.value();
//        } else {
//            if (pos <= from && pos > to)
//                ++i.value();
//        }
//    }


    QVariant from_tab_data = bar -> tabData(from);
    File * from_file = (File *)from_tab_data.value<void *>();

    QVariant to_tab_data = bar -> tabData(to);
    File * to_file = (File *)to_tab_data.value<void *>();

    tab_links[from_file -> uid()] = from;
    tab_links[to_file -> uid()] = to;
}

void TabsBlock::showTabsContextMenu(const QPoint & point) {
    if (point.isNull())
        return;

    menu_target_index = bar -> tabAt(point);

    QMenu menu(this);

    if (menu_target_index >= 0) {
        qDebug() << "CONT MENU : SHOW";

        menu.addAction(tr("In separate editor"), this, SLOT(newTabsBlockRequest()));
        menu.exec(bar -> mapToGlobal(point));
    }
}

void TabsBlock::newTabsBlockRequest() {
    QVariant tab_data = bar -> tabData(menu_target_index);
    File * file = (File *)tab_data.value<void *>();

    emit newTabsBlockRequested(file);
}
