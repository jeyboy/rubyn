#include "tabs_block.h"

#include "tab_bar.h"
#include "logger.h"
#include "tab_bar_no_focus_style.h"

#include "project/file.h"

#include "controls/logger.h"
#include "controls/universal_editor.h"

#include <qlabel.h>
#include <qboxlayout.h>
#include <qtoolbutton.h>
#include <qmenu.h>

void TabsBlock::activate(const bool & act) {
    _active_btn -> setVisible(act);
}

void TabsBlock::setupLayout() {
    QVBoxLayout * col_layout = new QVBoxLayout(this);

    col_layout -> setContentsMargins(1,1,1,1);
    col_layout -> setSpacing(1);

    QWidget * row = new QWidget(this);
    QHBoxLayout * row_layout = new QHBoxLayout(row);

    row_layout -> setContentsMargins(1,1,1,1);
    row_layout -> setSpacing(1);

    _bar = new TabBar(this);
    _bar -> setStyle(new TabBarNoFocusStyle());
    _bar -> setMovement(QListView::Free);
    _bar -> setContextMenuPolicy(Qt::CustomContextMenu);


    _active_btn = new QToolButton(this);
    _active_btn -> setIcon(QIcon(":/tools/help"));
    _active_btn -> setFixedHeight(_bar -> height());
    _active_btn -> setStyleSheet("background: qlineargradient(x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 255, 255, 255), stop:1 rgba(0, 204, 255, 255)); border-radius: 3px; border: 1px solid black;");
    _active_btn -> hide();

//    connect(_active_btn, SIGNAL(clicked()), this, SLOT(updateEditor()));

    row_layout -> addWidget(_active_btn, 0);

    row_layout -> addWidget(_bar, 1);


    _scroll_left_btn = new QToolButton(this);
    _scroll_left_btn -> setIcon(QIcon(":/row_left"));
    _scroll_left_btn -> setFixedHeight(_bar -> height());
    _scroll_left_btn -> hide();
    row_layout -> addWidget(_scroll_left_btn, 0);


    _scroll_right_btn = new QToolButton(this);
    _scroll_right_btn -> setIcon(QIcon(":/row_right"));
    _scroll_right_btn -> setFixedHeight(_bar -> height());
    _scroll_right_btn -> hide();
    row_layout -> addWidget(_scroll_right_btn, 0);


    _files_list = new QMenu(QLatin1Literal("Files"), this);

    _list_btn = new QToolButton(this);
    _list_btn -> setText(QLatin1Literal("0"));
    _list_btn -> setIcon(QIcon(QLatin1Literal(":/list")));
    _list_btn -> setFixedHeight(_bar -> height());
    _list_btn -> setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    _list_btn -> setPopupMode(QToolButton::InstantPopup);
    _list_btn -> setMenu(_files_list);

    row_layout -> addWidget(_list_btn, 0);


    col_layout -> addWidget(row, 0);

    _editor = new UniversalEditor(this);

    col_layout -> addWidget(_editor, 1);
}

TabsBlock::TabsBlock(QWidget * parent) : QWidget(parent), _bar(nullptr), _active_btn(nullptr), _list_btn(nullptr), _scroll_left_btn(nullptr), _scroll_right_btn(nullptr), _files_list(nullptr) {
//    setStyleSheet("QWidget:focus {background-color: #FFFFCC;}");

    setupLayout();

    connect(_bar, SIGNAL(currentRowChanged(int)), this, SLOT(currentTabIndexChanged(int)));
    connect(_bar, SIGNAL(tabCloseRequested(QListWidgetItem*)), this, SLOT(closeTab(QListWidgetItem*)));
    connect(_bar, SIGNAL(itemsCountChanged(int)), this, SLOT(tabsCountChanged(int)));
    connect(_bar, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showTabsContextMenu(const QPoint &)));
    connect(_bar, SIGNAL(scrollsRequired(bool)), this, SLOT(scrollsVisiabilityChange(bool)));

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

    if (_bar -> _tabs_linkages.contains(file_uid)) {
        QListWidgetItem * item = _bar -> _tabs_linkages[file_uid];
        currentTabChanged(item);

        return true;
    } else {
        //TODO: this block ruin normal logic: we should call openFileInEditor after _bar -> setCurrentItem
        if (!_editor -> openFile(file)) {
            if (is_external)
                delete file;

            return false;
        }
        /////////////////


        QListWidgetItem * item = _bar -> addTab(file -> ico(), file -> name());
        item -> setData(Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(file)));

        file -> document() -> registerStateChangedCallback(_bar, SLOT(markAsChanged(QString, bool)));

        _bar -> _tabs_linkages.insert(file_uid, item);

        if (is_external) {
            _external_files.insert(file_uid, file);
            item -> setBackgroundColor(QColor(255, 0, 0, 92));
        }

        _bar -> blockSignals(true);
        _bar -> setCurrentItem(item);
        _bar -> blockSignals(false);

        if (isHidden())
            show();
    }

    return true;
}

int TabsBlock::tabsCount() { return _bar -> count(); }

QString TabsBlock::tabFilePath(const int & index) {
    File * file = _bar -> tabFile(index);

    return file ? file -> path() : QString();
}

QString TabsBlock::currentTabFilePath() {
    QListWidgetItem * item = _bar -> currentItem();

    File * file = item ? _bar -> tabFile(item) : nullptr;

    return file ? file -> path() : QString();
}

bool TabsBlock::tabDumpState(const int & index, QVariant & data) {
    File * file = _bar -> tabFile(index);
    return file ? file -> dumpState(data) : false;
}

bool TabsBlock::tabRestoreState(const int & index, QVariant & data) {
    File * file = _bar -> tabFile(index);
    return file ? file -> restoreState(data) : false;
}

int TabsBlock::currentTabVerticalScrollPos() { return tabVerticalScrollPos(_bar -> currentRow()); }
int TabsBlock::tabVerticalScrollPos(const int & index) {
    if (_bar -> currentRow() == index) {
        return _editor -> verticalScrollBar();
    }

    File * file = _bar -> tabFile(index);
    return file ? file -> verticalScrollState(false) : 0;
}
void TabsBlock::setTabVerticalScrollPos(const int & index, const int & pos) {    
    File * file = _bar -> tabFile(index);

    if (file)
        file -> setVerticalScrollState(pos);
}

void TabsBlock::buildFilesList() {
    _files_list -> clear();

    QListWidgetItem * current_tab = _bar -> currentItem();

    QHash<QString, QListWidgetItem *> & tabs_links = _bar -> _tabs_linkages;

    for(QHash<QString, QListWidgetItem *>::Iterator it = tabs_links.begin(); it != tabs_links.end(); it++) {
        QListWidgetItem * tab = it.value();

        QAction * action =
            _files_list -> addAction(tab -> icon(), tab -> text(), this, SLOT(fileListClicked()));

        action -> setDisabled(current_tab == tab);
        action -> setProperty("uid", it.key());
    }
}

void TabsBlock::fileListClicked() {
    QObject * obj = sender();

    QListWidgetItem * tab = _bar -> _tabs_linkages[obj -> property("uid").toString()];

    currentTabChanged(tab);
}

void TabsBlock::scrollsVisiabilityChange(const bool & show) {
    _scroll_left_btn -> setVisible(show);
    _scroll_right_btn -> setVisible(show);

    // Monkeypatch - toolbuttons not drawn after maximize and return to normal view
    if (show) {
        resize(size() + QSize(1, 0));

        _bar -> scrollToItem(_bar -> currentItem());
    }
    ///////////////////////
}

void TabsBlock::tabsCountChanged(const int & correction) {
    int new_amount = _bar -> count() + correction;

    _list_btn -> setText(QString::number(new_amount));

    if (new_amount == 0) {
        emit moveToBlankState(this);
        hide();
    }
}

void TabsBlock::saveFiles() {
    QHash<QString, QListWidgetItem *>::Iterator it = _bar -> _tabs_linkages.begin();

    for(; it != _bar -> _tabs_linkages.end(); it++) {
        File * f = _bar -> tabFile(it.value());

        if (f && f -> isChanged()) {
            f -> save();
        }
    }
}

void TabsBlock::currentTabIndexChanged(const int & index) {
    QListWidgetItem * tab = _bar -> item(index);

    if (tab)
       currentTabChanged(tab);
}

void TabsBlock::currentTabChanged(QListWidgetItem * tab) {
    if (!tab) return;

    File * file = _bar -> tabFile(tab);

    if (!file) {
        Logger::error(QLatin1Literal("Editor"), QLatin1Literal("Internal error: can't find file: ") % file -> name());
        return;
    }

    if (_editor -> documentUid() != file -> uid()) {
        if (!_editor -> openFile(file)) {
            Logger::error(QLatin1Literal("Editor"), QLatin1Literal("Can't open file: ") % file -> name());
            return;
        }
    }

    if (_bar -> currentItem() != tab)
        _bar -> setCurrentItem(tab);
}

void TabsBlock::clear() {
    int tabs_count = _bar -> count();

    for(int i = tabs_count - 1; i >= 0; --i)
        closeTab(_bar -> item(i));
}

void TabsBlock::closeTab(QListWidgetItem * tab) {
    File * file = _bar -> tabFile(tab);

    if (file) {
        file -> close();

        QString file_uid = file -> uid();
        if (_external_files.contains(file_uid)) {
            if (_bar -> currentItem() == tab) {
                _editor -> openFile(nullptr);
            }

            delete _external_files.take(file_uid);
        }

        _bar -> _tabs_linkages.remove(file_uid);
    }

    _bar -> removeTab(tab);
}

void TabsBlock::closeCurrentTab() {
    QListWidgetItem * itm = _bar -> currentItem();

    if (itm)
        closeTab(itm);
}
void TabsBlock::closeExceptCurrentTab() {
    int tabs_count = _bar -> count();

    QListWidgetItem * curr_itm = _bar -> currentItem();

    for(int i = tabs_count - 1; i >= 0; --i) {
        QListWidgetItem * itm = _bar -> item(i);

        if (itm != curr_itm)
            closeTab(itm);
    }
}

void TabsBlock::showTabsContextMenu(const QPoint & point) {
    if (point.isNull())
        return;

    emit activated(this);

    QListWidgetItem * tab = _bar -> itemAt(point);

    if (tab) {
        QMenu menu(this);

        File * file = _bar -> tabFile(tab);

        QAction * action = menu.addAction(QIcon(QLatin1Literal(":/menu/break_horizontal")), tr("Close"), this, SLOT(closeCurrentTab()));
        action -> setProperty("uid", file -> uid());

        action = menu.addAction(QIcon(QLatin1Literal(":/menu/break_horizontal")), tr("Close other"), this, SLOT(closeExceptCurrentTab()));
        action -> setProperty("uid", file -> uid());

        action = menu.addAction(QIcon(QLatin1Literal(":/menu/break_horizontal")), tr("Close all"), this, SLOT(clear()));

        menu.addSeparator();

        action = menu.addAction(QIcon(QLatin1Literal(":/menu/break_horizontal")), tr("Split"), this, SLOT(newTabsBlockRequest()));
        action -> setProperty("uid", file -> uid());
        action -> setProperty("vertical", false);

        action = menu.addAction(QIcon(QLatin1Literal(":/menu/break_vertical")), tr("Split"), this, SLOT(newTabsBlockRequest()));
        action -> setProperty("uid", file -> uid());
        action -> setProperty("vertical", true);

        menu.exec(_bar -> mapToGlobal(point));
    }
}

void TabsBlock::newTabsBlockRequest() {
    QObject * obj = sender();

    QListWidgetItem * tab = _bar -> _tabs_linkages[obj -> property("uid").toString()];

    if (tab) {
        File * file = _bar -> tabFile(tab);

        if (file) {
            emit newTabsBlockRequested(file, obj -> property("vertical").toBool());
        }
    } else {
        qDebug() << "JOPA";
    }
}
