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

void TabsBlock::setupLayout() {
    QVBoxLayout * col_layout = new QVBoxLayout(this);

    col_layout -> setContentsMargins(1,1,1,1);
    col_layout -> setSpacing(1);

    QWidget * row = new QWidget(this);
    QHBoxLayout * row_layout = new QHBoxLayout(row);

    row_layout -> setContentsMargins(1,1,1,1);
    row_layout -> setSpacing(1);

    _bar = new TabBar(this);
//    bar -> setTabsClosable(true);
    _bar -> setMovement(QListView::Free);
    _bar -> setContextMenuPolicy(Qt::CustomContextMenu);

    row_layout -> addWidget(_bar, 1);


    _scroll_left_btn = new QToolButton(this);
    _scroll_left_btn -> setText(QLatin1Literal("<"));
    row_layout -> addWidget(_scroll_left_btn, 0);


    _scroll_right_btn = new QToolButton(this);
    _scroll_right_btn -> setText(QLatin1Literal(">"));
    row_layout -> addWidget(_scroll_right_btn, 0);


    _files_list = new QMenu(QLatin1Literal("Files"), this);

    _list_btn = new QToolButton(this);
    _list_btn -> setText(QLatin1Literal("0"));
    _list_btn -> setIcon(QIcon(QLatin1Literal(":/list")));
    _list_btn -> setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    _list_btn -> setPopupMode(QToolButton::InstantPopup);
    _list_btn -> setMenu(_files_list);

    row_layout -> addWidget(_list_btn, 0);


    col_layout -> addWidget(row, 0);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(11);

    _editor = new CodeEditor(this);
    _editor -> setFont(font);

    col_layout -> addWidget(_editor, 1);
}

TabsBlock::TabsBlock(QWidget * parent) : QWidget(parent), _bar(0), _list_btn(0), _scroll_left_btn(0), _scroll_right_btn(0), _files_list(0) {
//    setStyleSheet("QWidget:focus {background-color: #FFFFCC;}");

    setupLayout();

    connect(_bar, SIGNAL(currentRowChanged(int)), this, SLOT(currentTabIndexChanged(int)));
    connect(_bar, SIGNAL(tabCloseRequested(QListWidgetItem*)), this, SLOT(tabRemoved(QListWidgetItem*)));
    connect(_bar, SIGNAL(layoutChanged()), this, SLOT(tabsLayoutChanged()));
    connect(_bar, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showTabsContextMenu(const QPoint &)));

    connect(_scroll_left_btn, SIGNAL(clicked()), _bar, SLOT(scrollBackward()));
    connect(_scroll_right_btn, SIGNAL(clicked()), _bar, SLOT(scrollForward()));

    connect(_editor, SIGNAL(inFocus()), this, SLOT(inFocus()));
    connect(_editor, SIGNAL(fileDropped(QUrl)), this, SLOT(resourceDrop(QUrl)));

    connect(_files_list, SIGNAL(aboutToShow()), this, SLOT(buildFilesList()));
}

TabsBlock::~TabsBlock() {
    delete _bar;

    qDeleteAll(_external_files);
}

void TabsBlock::registerCursorPosOutput(QLabel * output) {
    connect(_editor, SIGNAL(cursorPosChanged(QString)), output, SLOT(setText(QString)));
}

bool TabsBlock::openFile(File * file, const bool & is_external) {
    QString file_uid = file -> uid();

    if (_tab_links.contains(file_uid)) {
        QListWidgetItem * item = _tab_links[file_uid];
        currentTabChanged(item);

        return true;
    } else {
        if (!openFileInEditor(file)) {
            if (is_external)
                delete file;

            return false;
        }


        QListWidgetItem * item = _bar -> addTab(file -> ico(), file -> name());
        item -> setData(Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(file)));

        _tab_links.insert(file_uid, item);

        if (is_external) {
            _external_files.insert(file_uid, file);
            item -> setBackgroundColor(QColor(255, 0, 0, 16));
        }

        _bar -> setCurrentItem(item);

        if (isHidden())
            show();
    }

    return true;
}

bool TabsBlock::openFileInEditor(File * file) {
    switch(file -> baseFormatType()) {
        case ft_text: {
            _editor -> openDocument(file);

            QStringList wordList;
            wordList << "alpha" << "omega" << "omicron" << "zeta";
            QCompleter * completer = new QCompleter(wordList, this);
            _editor -> setCompleter(completer);
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

File * TabsBlock::tabFile(QListWidgetItem * tab) {
    QVariant tab_data = tab -> data(Qt::UserRole);

    if (!tab_data.isNull()) {
        return reinterpret_cast<File *>(tab_data.value<quintptr>());
    }

    return 0;
}

void TabsBlock::buildFilesList() {
    _files_list -> clear();

    QListWidgetItem * current_tab = _bar -> currentItem();

    for(QHash<QString, QListWidgetItem *>::Iterator it = _tab_links.begin(); it != _tab_links.end(); it++) {
        QListWidgetItem * tab = it.value();

        QAction * action =
            _files_list -> addAction(tab -> icon(), tab -> text(), this, SLOT(fileListClicked()));

        action -> setDisabled(current_tab == tab);
        action -> setProperty("uid", it.key());
    }
}

void TabsBlock::fileListClicked() {
    QObject * obj = sender();

    QListWidgetItem * tab = _tab_links[obj -> property("uid").toString()];

    currentTabChanged(tab);
}

void TabsBlock::tabsLayoutChanged() {
    _list_btn -> setText(QString::number(_bar -> count()));
}

void TabsBlock::currentTabIndexChanged(const int & index) {
    currentTabChanged(_bar -> item(index));
}

void TabsBlock::currentTabChanged(QListWidgetItem * tab) {
    if (!tab) return;

    File * file = tabFile(tab);

    if (!file || (file && !openFileInEditor(file))) {
        // notify user
        return;
    }

    _bar -> setCurrentItem(tab);
}

void TabsBlock::tabRemoved(QListWidgetItem * tab) {
    File * file = tabFile(tab);

    if (file) {
        QString file_uid = file -> uid();
        if (_external_files.contains(file_uid)) {
            delete _external_files.take(file_uid);
        }

        _tab_links.remove(file_uid);
    }

    _bar -> removeTab(tab);

    if (_bar -> count() == 0) {
        emit moveToBlankState(this);
        hide();
    }
}

void TabsBlock::showTabsContextMenu(const QPoint & point) {
    if (point.isNull())
        return;

    QListWidgetItem * tab = _bar -> itemAt(point);

    if (tab) {
        QMenu menu(this);

        QAction * action = menu.addAction(tr("In separate editor"), this, SLOT(newTabsBlockRequest()));
        File * file = tabFile(tab);
        action -> setProperty("uid", file -> uid());

        menu.exec(_bar -> mapToGlobal(point));
    }
}

void TabsBlock::newTabsBlockRequest() {
    QObject * obj = sender();

    QListWidgetItem * tab = _tab_links[obj -> property("uid").toString()];

    File * file = tabFile(tab);

    if (file) {
        emit newTabsBlockRequested(file);
    }
}
