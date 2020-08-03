#include "tabs_block.h"

#include "tab_bar.h"
#include "logger.h"
#include "styles/tab_bar_no_focus_style.h"

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
    _bar -> setAttribute(Qt::WA_ShowWithoutActivating);
    _bar -> setFocusPolicy(Qt::NoFocus);


    _active_btn = new QToolButton(this);
    _active_btn -> setIcon(QIcon(":/tools/help"));
    _active_btn -> setFixedHeight(_bar -> height());
    _active_btn -> setStyleSheet("background: qlineargradient(x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 255, 255, 255), stop:1 rgba(0, 204, 255, 255)); border-radius: 3px; border: 1px solid black;");
    _active_btn -> hide();

    connect(_active_btn, SIGNAL(clicked()), this, SLOT(showHelpBtnContextMenu()));

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


    _files_list = new QMenu(QLatin1String("Files"), this);

    _list_btn = new QToolButton(this);
    _list_btn -> setText(QLatin1String("0"));
    _list_btn -> setIcon(QIcon(QLatin1String(":/list")));
    _list_btn -> setFixedHeight(_bar -> height());
    _list_btn -> setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    _list_btn -> setPopupMode(QToolButton::InstantPopup);
    _list_btn -> setMenu(_files_list);

    row_layout -> addWidget(_list_btn, 0);


    col_layout -> addWidget(row, 0);

    _editor = new UniversalEditor(this);

    col_layout -> addWidget(_editor, 1);
}

TabsBlock::TabsBlock(QWidget * parent) : QWidget(parent), _bar(nullptr), _active_btn(nullptr), _list_btn(nullptr), _scroll_left_btn(nullptr),
    _scroll_right_btn(nullptr), _editor(nullptr), _breakpoints(nullptr), _files_list(nullptr), _lock_saving(true)
{
//    setStyleSheet("QWidget:focus {background-color: #FFFFCC;}");

    setupLayout();

    connect(_bar, SIGNAL(currentRowChanged(int)), this, SLOT(currentTabIndexChanged(int)));
    connect(_bar, SIGNAL(tabCloseRequested(QListWidgetItem*)), this, SLOT(closeTab(QListWidgetItem*)));
    connect(_bar, SIGNAL(itemsCountChanged(int)), this, SLOT(tabsCountChanged(int)));
    connect(_bar, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showTabsContextMenu(const QPoint &)));
    connect(_bar, SIGNAL(scrollsRequired(bool)), this, SLOT(scrollsVisiabilityChange(bool)));

    connect(_scroll_left_btn, SIGNAL(clicked()), _bar, SLOT(scrollBackward()));
    connect(_scroll_right_btn, SIGNAL(clicked()), _bar, SLOT(scrollForward()));

    connect(_editor, &UniversalEditor::inFocus, [=]() { emit activated(this); });
    connect(_editor, &UniversalEditor::fileDropped, [=](const QUrl & url) { emit resourceDropped(this, url); });

    connect(_files_list, SIGNAL(aboutToShow()), this, SLOT(buildFilesList()));
}

TabsBlock::~TabsBlock() {
    delete _bar;
}

void TabsBlock::registerCursorPosOutput(QLabel * output) {
    connect(_editor, &UniversalEditor::cursorPosChanged, output, &QLabel::setText);
}

bool TabsBlock::openFile(File * file) {
    QString file_uid = file -> uid();

    if (_bar -> _tabs_linkages.contains(file_uid)) {
        QListWidgetItem * item = _bar -> _tabs_linkages[file_uid];
        currentTabChanged(item);

        return true;
    } else {
        //TODO: this block ruin normal logic: we should call openFileInEditor after _bar -> setCurrentItem
        if (!_editor -> openFile(file)) {
            if (file -> isExternal())
                delete file;

            return false;
        }
        /////////////////


        QListWidgetItem * item = _bar -> addTab(file -> ico(), file -> name());
        item -> setData(Qt::UserRole, QVariant::fromValue(reinterpret_cast<quintptr>(file)));

        file -> document() -> registerStateChangedCallback(_bar, SLOT(markAsChanged(QString, bool)));

        _bar -> _tabs_linkages.insert(file_uid, item);

        if (file -> isExternal()) {
            item -> setBackgroundColor(_bar -> remote_file_color);
        }

        file -> incOpened();

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

QPoint TabsBlock::currentTabScrollPos() { return tabScrollPos(_bar -> currentRow()); }
QPoint TabsBlock::tabScrollPos(const int & index) {
    if (_bar -> currentRow() == index) {
        return QPoint(_editor -> horizontalScrollBarPos(), _editor -> verticalScrollBarPos());
    }

    File * file = _bar -> tabFile(index);
    return file ? file -> scrollState(false) : QPoint(0, 0);
}
void TabsBlock::setTabScrollPos(const int & index, const QPoint & pos) {
    File * file = _bar -> tabFile(index);

    if (file)
        file -> setScrollState(pos);
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
        hide();
        emit moveToBlankState(this);
    }
}

void TabsBlock::fileClosed(const QString & uid) {
    QListWidgetItem * item = _bar -> _tabs_linkages[uid];
    if (item) {
        closeTab(item);
    }
}

void TabsBlock::saveFiles() {
    if (!_lock_saving) {
        QHash<QString, QListWidgetItem *>::Iterator it = _bar -> _tabs_linkages.begin();

        for(; it != _bar -> _tabs_linkages.end(); it++) {
            File * f = _bar -> tabFile(it.value());

            if (f && f -> isChanged()) {
                f -> save();
            }
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
        Logger::error(QLatin1String("Editor"), QLatin1String("Internal error: can't find file: ") % file -> name());
        return;
    }

    if (_editor -> documentUid() != file -> uid()) {
        if (!_editor -> openFile(file)) {
            Logger::error(QLatin1String("Editor"), QLatin1String("Can't open file: ") % file -> name());
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
        if (file -> isExternal()) {
            if (_bar -> currentItem() == tab) {
                _editor -> openFile(nullptr);
            }
        }

        _bar -> _tabs_linkages.remove(file -> uid());
        file -> decOpened();
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

        QAction * action = menu.addAction(QIcon(QLatin1String(":/menu/close")), tr("Close"), this, SLOT(closeCurrentTab()));
        action -> setProperty("uid", file -> uid());

        action = menu.addAction(QIcon(QLatin1String(":/menu/close_other")), tr("Close other"), this, SLOT(closeExceptCurrentTab()));
        action -> setProperty("uid", file -> uid());

        action = menu.addAction(QIcon(QLatin1String(":/menu/close_all")), tr("Close all"), this, SLOT(clear()));

        menu.addSeparator();

        action = menu.addAction(QIcon(QLatin1String(":/menu/break_horizontal")), tr("Split"), this, SLOT(newTabsBlockRequest()));
        action -> setProperty("uid", file -> uid());
        action -> setProperty("vertical", false);

        action = menu.addAction(QIcon(QLatin1String(":/menu/break_vertical")), tr("Split"), this, SLOT(newTabsBlockRequest()));
        action -> setProperty("uid", file -> uid());
        action -> setProperty("vertical", true);

        menu.exec(_bar -> mapToGlobal(point));
    }
}

void TabsBlock::showHelpBtnContextMenu() {
    emit activated(this);

    QMenu menu(this);

    QAction * action = menu.addAction(tr("Lock save"), this, [=]() {
        _lock_saving = !_lock_saving;
    });
    action -> setCheckable(true);
    action -> setChecked(_lock_saving);

    menu.addSeparator();

    File * file = _bar -> currentTabFile();
    if (file) {
        action = menu.addAction(tr("Word wrap"), this, [=]() {
            File * file = _bar -> currentTabFile();

            if (file) {
                file -> setWordWrap(!file -> isWordWrap());
            }
        });

        action -> setCheckable(true);
        action -> setChecked(file -> isWordWrap());
    }


    menu.exec(_bar -> mapToGlobal(_active_btn -> pos()));
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
