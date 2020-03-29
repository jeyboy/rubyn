#include "project_search_panel.h"

//#include "project/file.h"

#include <qtreewidget.h>
#include <qheaderview.h>
//#include <qscrollbar.h>

#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtoolbar.h>
//#include <qtoolbutton.h>
//#include <qshortcut.h>

#include "styles/click_fix_style.h"

void ProjectSearchPanel::process() {

}

void ProjectSearchPanel::prepareResultsWidget() {
    search_results -> setHeaderHidden(true);
    search_results -> setAutoScroll(false);
//    search_results -> setContextMenuPolicy(Qt::CustomContextMenu);

    search_results -> setColumnCount(2);
    search_results -> header() -> setSectionResizeMode(0, QHeaderView::ResizeToContents);
    search_results -> header() -> setStretchLastSection(false);

    QFont f(font());
    f.setPointSize(11);
//    f.setLetterSpacing(QFont::AbsoluteSpacing, 0.6);
    setFont(f);

    //TODO: need to set double font size
    search_results -> setIconSize(QSize(22, 22));

    search_results -> setStyle(new ClickFixStyle());

//    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));
//    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));

//    connect(this, &QTreeWidget::itemClicked, [](QTreeWidgetItem * item, int column) {
//        item -> setExpanded(!item -> isExpanded());
//    });

//    search_results -> setSortingEnabled(true);
//    search_results -> sortByColumn(0, Qt::AscendingOrder);

    search_results -> setEditTriggers(QAbstractItemView::NoEditTriggers);
//    setExpandsOnDoubleClick(false);

//    item_delegate = new ProjectTreeItemDelegate();
//    setItemDelegate(item_delegate);
}

ProjectSearchPanel::ProjectSearchPanel(QWidget * parent) : QWidget(parent), search_results(nullptr), predicate(nullptr), target_paths(nullptr) {
    QVBoxLayout * l = new QVBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    l -> setSpacing(0);

    QToolBar * control_panel = new QToolBar(this);
    control_panel -> setOrientation(Qt::Horizontal);
    control_panel -> setIconSize(QSize(18, 18));

    predicate = new QLineEdit(this);
    control_panel -> addWidget(new QLabel("Search:", control_panel));
    control_panel -> addWidget(predicate);

    target_paths = new QLineEdit(this);
    control_panel -> addWidget(new QLabel(" in ", control_panel));
    control_panel -> addWidget(target_paths);

//    QToolButton * btn0 = new QToolButton(control_panel);
//    btn0 -> setIconSize(QSize(16, 16));
//    btn0 -> setIcon(QIcon(QLatin1Literal(":/breakpoint_disabled")));
//    btn0 -> setToolTip(QLatin1Literal("Disable selected"));
//    control_panel -> addWidget(btn0);


//    QToolButton * btn1 = new QToolButton(control_panel);
//    QIcon ico;

//    ico.addPixmap(QPixmap(QLatin1Literal(":/breakpoint_disable_all")), QIcon::Normal, QIcon::Off);
//    ico.addPixmap(QPixmap(QLatin1Literal(":/breakpoint_enable_all")), QIcon::Normal, QIcon::On);

//    btn1 -> setIcon(ico);
//    btn1 -> setToolTip(QLatin1Literal("Disable all"));
//    btn1 -> setCheckable(true);
//    control_panel -> addWidget(btn1);


//    QToolButton * btn2 = new QToolButton(control_panel);
//    btn2 -> setIcon(QIcon(QLatin1Literal(":/breakpoint_delete_all")));
//    btn2 -> setToolTip(QLatin1Literal("Remove all"));
//    control_panel -> addWidget(btn2);

    search_results = new QTreeWidget(this);
    prepareResultsWidget();

//    search_results -> show

//    connect(breakpoints, &QListWidget::itemDoubleClicked, this, &BreakpointsPanel::breakpointDoubleClicked);

//    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), breakpoints);
//    shortcut -> setContext(Qt::WidgetShortcut);
//    connect(shortcut, SIGNAL(activated()), this, SLOT(deleteBreakpointItem()));

    l -> addWidget(control_panel, 0);
    l -> addWidget(search_results, 1);
}


//void BreakpointsPanel::activateBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num) {
//    if (active_breakpoint) {
//        active_breakpoint -> setData(Qt::BackgroundRole, QVariant());
////        active_breakpoint -> setData(Qt::ForegroundRole, QVariant());
//    }

//    if (!records.contains(path))
//        return;

//    active_breakpoint = records[path][line_num];
//    active_breakpoint -> setData(Qt::BackgroundRole, QColor(0, 212, 212));
////    active_breakpoint -> setData(Qt::ForegroundRole, QColor(255, 255, 255));
//}

//void BreakpointsPanel::addBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num) {
////    emit breakpointAdded(path, line_num);

//    QListWidgetItem * itm = new QListWidgetItem(QIcon(QLatin1Literal(":/breakpoint")), buildName(path, line_num));
//    itm -> setData(Qt::UserRole + 1, path);
//    itm -> setData(Qt::UserRole + 2, line_num);

//    if (!records.contains(path))
//        records.insert(path, QHash<EDITOR_POS_TYPE, QListWidgetItem * >());

//    records[path].insert(line_num, itm);

//    breakpoints -> addItem(itm);
//}
//void BreakpointsPanel::moveBreakpoint(const QString & path, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num) {
//    if (!records.contains(path))
//        return;

//    QHash<EDITOR_POS_TYPE, QListWidgetItem * > & lines = records[path];

//    QList<EDITOR_POS_TYPE> nums = lines.keys();

//    EDITOR_POS_TYPE diff = new_line_num - old_line_num;

//    for(QList<EDITOR_POS_TYPE>::Iterator it = nums.begin(); it != nums.end(); it++) {
//        if (*it > old_line_num) {
//            EDITOR_POS_TYPE new_pos = *it + diff;

//            QListWidgetItem * itm = lines.take(*it);
//            itm -> setText(buildName(path, new_pos));
//            itm -> setData(Qt::UserRole + 2, new_pos);
//            lines[new_pos] = itm;
//        }
//    }
//}
//void BreakpointsPanel::removeBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num) {
//    if (!records.contains(path))
//        return;

//    if (line_num == NO_INFO) {
//        if (active_breakpoint) {
//            QString active_path = active_breakpoint -> data(Qt::UserRole + 1).toString();

//            if (path == active_path)
//                active_breakpoint = nullptr;
//        }

//        qDeleteAll(records.take(path));
//    }

//    QHash<EDITOR_POS_TYPE, QListWidgetItem * > & lines = records[path];

//    if (!lines.contains(line_num))
//        return;

//    QListWidgetItem * item = lines.take(line_num);

//    if (item == active_breakpoint)
//        active_breakpoint = nullptr;

//    delete item;
//    emit breakpointRemoved(path, line_num);
//}

//void BreakpointsPanel::deleteBreakpointItem() {
//    qDebug() << "deleteBreakpointItem";

//    QListWidgetItem * item = breakpoints -> currentItem();

//    QString path = item -> data(Qt::UserRole + 1).toString();
//    EDITOR_POS_TYPE line_num = item -> data(Qt::UserRole + 2).toInt();

//    removeBreakpoint(path, line_num);
//}

//void BreakpointsPanel::breakpointDoubleClicked(QListWidgetItem * item) {
//    qDebug() << "breakpointDoubleClicked";

//    QString path = item -> data(Qt::UserRole + 1).toString();
//    EDITOR_POS_TYPE line_num = item -> data(Qt::UserRole + 2).toInt();

//    activateBreakpoint(path, line_num);
//}

void ProjectSearchPanel::initiateSearch(const QString & pathes, const QString & search_predicate) {
    predicate -> setText(search_predicate);
    target_paths -> setText(pathes);

    process();
}
