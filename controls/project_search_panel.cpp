#include "project_search_panel.h"

#include "styles/click_fix_style.h"
#include "delegates/project_search_item_delegate.h"

#include "tools/dir_search.h"
#include "tools/file_search_result.h"

#include "controls/logger.h"
#include "project_tree.h"

#include <qtreewidget.h>
#include <qheaderview.h>
//#include <qscrollbar.h>

#include <qmenu.h>
#include <qwidgetaction.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qfileinfo.h>
//#include <qshortcut.h>

QTreeWidgetItem * ProjectSearchPanel::pathToTreeLevel(const QString & path, QString & name) {
    //    QDir::separator()
    QFileInfo info(path);
    QString target_path = info.path();

    name = info.fileName();

    if (!search_roots.contains(target_path)) {
        QTreeWidgetItem * pitm = new QTreeWidgetItem(QStringList() << target_path);
        search_roots[target_path] = pitm;
        results_itm -> addChild(pitm);
        pitm -> setExpanded(true);
    }

    return search_roots[target_path];
}

QRegularExpression ProjectSearchPanel::buildRegex(const QString & pattern) {
//    if (pattern.isEmpty()) {
//        emit clearRequires();
//        return QRegularExpression();
//    }

    QString val = pattern;
    bool is_multiline = false;

    QRegularExpression::PatternOptions options = QRegularExpression::DotMatchesEverythingOption;

    if (!flag_case_sensitive -> isChecked())
        options |= QRegularExpression::CaseInsensitiveOption;

    if (flag_unicode -> isChecked())
        options |= QRegularExpression::UseUnicodePropertiesOption;

    val = val.replace(QRegularExpression(QLatin1String("\r|\n")), QLatin1String("|"));

    is_multiline = val != pattern;

    if (!flag_reg_exp -> isChecked() && !is_multiline)
        val = QRegularExpression::escape(val);

    if (flag_whole_word_only -> isChecked())
        val = QLatin1String("\\b") % val % QLatin1String("\\b");

    QRegularExpression res(val, options);
    res.optimize();

//    if (res.isValid())
//        predicateIsCorrect();
//    else
//        predicateHasError(res.errorString());

    return res;
}

void ProjectSearchPanel::prepareResultsWidget() {
//    search_results -> setHeaderHidden(true);
    search_results -> setAutoScroll(false);
//    search_results -> setContextMenuPolicy(Qt::CustomContextMenu);

    search_results -> setHeaderLabels(QStringList() << "Path" << "Match");
    search_results -> setColumnCount(2);
    search_results -> header() -> setSectionResizeMode(0, QHeaderView::Interactive);
    search_results -> header() -> setStretchLastSection(true);

    QFont f(font());
    f.setPointSize(11);
//    f.setLetterSpacing(QFont::AbsoluteSpacing, 0.6);
    setFont(f);

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

    item_delegate = new ProjectSearchItemDelegate(search_results);
    search_results -> setItemDelegate(item_delegate);


//    void itemClicked(QTreeWidgetItem *item, int column);
//    void itemDoubleClicked(QTreeWidgetItem *item, int column);
//    void itemActivated(QTreeWidgetItem *item, int column);

    connect(search_results, &QTreeWidget::itemActivated, [=](QTreeWidgetItem * item, int /*column*/) {
        emit resultClicked(
            item -> data(0, PROJECT_SEARCH_PATH_UID).toString(),
            item -> data(0, PROJECT_SEARCH_PATH_POS_UID).toUInt(),
            regex
        );
    });
}

void ProjectSearchPanel::prepareOptionsWidget() {
    QMenu * menu = new QMenu(predicate);
    QWidgetAction * options_btn = new QWidgetAction(predicate);
    QToolButton * btn = new QToolButton(predicate);

    btn -> setIcon(QPixmap(":/search_btn").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setMenu(menu);
    btn -> setPopupMode(QToolButton::InstantPopup);
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    options_btn -> setDefaultWidget(btn);

    predicate -> addAction(options_btn, QLineEdit::LeadingPosition);

    flag_case_sensitive = new QCheckBox(QLatin1String("Match Case"), menu);
    QWidgetAction * flag_case_sensitive_action = new QWidgetAction(menu);
    flag_case_sensitive_action -> setDefaultWidget(flag_case_sensitive);
    menu -> addAction(flag_case_sensitive_action);
    connect(flag_case_sensitive, &QCheckBox::clicked, [=](bool) {
        regex = buildRegex(predicate -> text());

//        if (regex.isValid()) {
//            process();
//        }
    });

    flag_whole_word_only = new QCheckBox(QLatin1String("Words"), menu);
    QWidgetAction * flag_whole_word_only_action = new QWidgetAction(menu);
    flag_whole_word_only_action -> setDefaultWidget(flag_whole_word_only);
    menu -> addAction(flag_whole_word_only_action);
    connect(flag_whole_word_only, &QCheckBox::clicked, [=](bool) {
        regex = buildRegex(predicate -> text());

//        if (regex.isValid()) {
//            process();
//        }
    });

    flag_reg_exp = new QCheckBox(QLatin1String("Regex"), menu);
    QWidgetAction * flag_reg_exp_action = new QWidgetAction(menu);
    flag_reg_exp_action -> setDefaultWidget(flag_reg_exp);
    menu -> addAction(flag_reg_exp_action);
    connect(flag_reg_exp, &QCheckBox::clicked, [=](bool) {
        regex = buildRegex(predicate -> text());

//        if (regex.isValid()) {
//            process();
//        }
    });

    flag_unicode = new QCheckBox(QLatin1String("Unicode"), menu);
    QWidgetAction * flag_unicode_action = new QWidgetAction(menu);
    flag_unicode_action -> setDefaultWidget(flag_unicode);
    menu -> addAction(flag_unicode_action);
    connect(flag_unicode, &QCheckBox::clicked, [=](bool) {
        regex = buildRegex(predicate -> text());

//        if (regex.isValid()) {
//            process();
//        }
    });
}


ProjectSearchPanel::ProjectSearchPanel(QWidget * parent) : QWidget(parent), pattern_itm(nullptr), results_itm(nullptr), search_results(nullptr), predicate(nullptr), target_paths(nullptr), project_tree(nullptr), dir_search(nullptr) {
    QVBoxLayout * l = new QVBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    l -> setSpacing(0);

    QToolBar * control_panel = new QToolBar(this);
    control_panel -> setOrientation(Qt::Horizontal);
    control_panel -> setIconSize(QSize(18, 18));

    predicate = new QLineEdit(this);
    connect(predicate, &QLineEdit::returnPressed, this, &ProjectSearchPanel::process);
    control_panel -> addWidget(predicate);
    prepareOptionsWidget();

    QToolButton * search_btn = new QToolButton(control_panel);
    search_btn -> setText("Search");
    control_panel -> addWidget(search_btn);

    connect(search_btn, &QToolButton::pressed, this, &ProjectSearchPanel::process);


    target_paths = new QLineEdit("*", this);
    control_panel -> addWidget(new QLabel(" in ", control_panel));
    control_panel -> addWidget(target_paths);

//    QToolButton * btn0 = new QToolButton(control_panel);
//    btn0 -> setIconSize(QSize(16, 16));
//    btn0 -> setIcon(QIcon(QLatin1String(":/breakpoint_disabled")));
//    btn0 -> setToolTip(QLatin1String("Disable selected"));
//    control_panel -> addWidget(btn0);


//    QToolButton * btn1 = new QToolButton(control_panel);
//    QIcon ico;

//    ico.addPixmap(QPixmap(QLatin1String(":/breakpoint_disable_all")), QIcon::Normal, QIcon::Off);
//    ico.addPixmap(QPixmap(QLatin1String(":/breakpoint_enable_all")), QIcon::Normal, QIcon::On);

//    btn1 -> setIcon(ico);
//    btn1 -> setToolTip(QLatin1String("Disable all"));
//    btn1 -> setCheckable(true);
//    control_panel -> addWidget(btn1);


//    QToolButton * btn2 = new QToolButton(control_panel);
//    btn2 -> setIcon(QIcon(QLatin1String(":/breakpoint_delete_all")));
//    btn2 -> setToolTip(QLatin1String("Remove all"));
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

    dir_search = new DirSearch(this);
    connect(dir_search, &DirSearch::finded, this, &ProjectSearchPanel::addResult);
    connect(dir_search, &DirSearch::searchFinished, this, &ProjectSearchPanel::searchFinished);
}

void ProjectSearchPanel::setProjectTree(ProjectTree * target_tree) {
    project_tree = target_tree;
}

void ProjectSearchPanel::activate(const QString & pathes) {
    predicate -> setFocus();
    target_paths -> setText(pathes);
}

void ProjectSearchPanel::initiateSearch(const QString & pathes, const QString & search_predicate) {
    predicate -> setText(search_predicate);
    target_paths -> setText(pathes);

    process();
}

void ProjectSearchPanel::process() {  
    search_results -> clear();

    if (predicate -> text().trimmed().isEmpty()) {
        Logger::obj().warn("ProjectSearchPanel", "Search pattern is not valid");
        return;
    }

    regex = buildRegex(predicate -> text());

    if (!regex.isValid()) {
        Logger::obj().error("ProjectSearchPanel", "Search pattern is not valid");
        return;
    }

    QString paths_value = target_paths -> text().trimmed();
    if (paths_value.isEmpty()) {
        paths_value.append('*');
    }

    search_results -> clear();

    pattern_itm = new QTreeWidgetItem(QStringList() << "Search '" % predicate -> text() % "'" << "No Resuls");
    results_itm = new QTreeWidgetItem(QStringList() << "Found Occurrences:");

    search_results -> header() -> setSectionResizeMode(0, QHeaderView::ResizeToContents);
    search_results -> addTopLevelItem(pattern_itm);
    search_results -> addTopLevelItem(results_itm);

    results_itm -> setExpanded(true);
    search_roots.clear();
    items_found = 0;
//    search_results -> setUpdatesEnabled(false);
//    search_time = QDateTime::currentDateTime();
    dir_search -> search(regex, paths_value, project_tree);
}

void ProjectSearchPanel::addResult(FileSearchResult * result) {
//    QDateTime curr_time = QDateTime::currentDateTime();

//    if (search_time.msecsTo(curr_time) >= 1000) {
//        search_time = curr_time;
//        search_results -> setUpdatesEnabled(true);
//    }

    QString name;

    if (!search_roots.contains(result -> path)) {
        QTreeWidgetItem * parent_itm = pathToTreeLevel(result -> path, name);
        QTreeWidgetItem * itm = new QTreeWidgetItem(QStringList() << name << "0");
        itm -> setData(0, PROJECT_SEARCH_COUNT_UID, 0);

        parent_itm -> addChild(itm);
        search_roots[result -> path] = itm;
        itm -> setExpanded(true);
    }

    QTreeWidgetItem * pitm = search_roots[result -> path];
    int amount = pitm -> data(0, PROJECT_SEARCH_COUNT_UID).toInt() + 1;
    pitm -> setData(0, PROJECT_SEARCH_COUNT_UID, amount);
    pitm -> setText(1, QString::number(amount));

    QTreeWidgetItem * itm = new QTreeWidgetItem(QStringList() << QString() << result -> result);
    itm -> setData(1, PROJECT_SEARCH_MATCH_POS_UID, result -> result_pos);
    itm -> setData(1, PROJECT_SEARCH_MATCH_LEN_UID, result -> match_length);
    itm -> setData(0, PROJECT_SEARCH_PATH_POS_UID, result -> match_pos);
    itm -> setData(0, PROJECT_SEARCH_PATH_UID, result -> path);

    //    itm -> setIcon(0, Projects::obj().getIco(ico_type));
    //    itm -> setToolTip(0, obj_name);

    pattern_itm -> setText(1, QString::number(++items_found));

//    search_results -> setFirstItemColumnSpanned(itm, true);
    pitm -> addChild(itm);

    delete result;

//    search_results -> setUpdatesEnabled(false);
}

void ProjectSearchPanel::searchFinished() {
//    search_results -> setUpdatesEnabled(true);
    search_roots.clear();
    search_results -> header() -> setSectionResizeMode(0, QHeaderView::Interactive);
}
