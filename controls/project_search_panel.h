#ifndef PROJECT_SEARCH_PANEL_H
#define PROJECT_SEARCH_PANEL_H

#include "misc/defines.h"

#include <qhash.h>
#include <qwidget.h>
#include <qregularexpression.h>
#include <qdatetime.h>

class ProjectSearchItemDelegate;
class QTreeWidget;
class QLineEdit;
class QCheckBox;
class QToolBar;
class ProjectTree;
class File;
class QTreeWidgetItem;
class DirSearch;
class FileSearchResult;

//class QListWidget;
//class QListWidgetItem;
//class File;

class ProjectSearchPanel : public QWidget {
    Q_OBJECT

    QDateTime search_time;
    int items_found;
    QHash<QString, QTreeWidgetItem *> search_roots;

    ProjectSearchItemDelegate * item_delegate;

    QTreeWidgetItem * pattern_itm;
    QTreeWidgetItem * results_itm;

    QTreeWidget * search_results;
    QLineEdit * predicate;
    QLineEdit * target_paths;
    ProjectTree * project_tree;
    DirSearch * dir_search;

    QCheckBox * flag_case_sensitive;
    QCheckBox * flag_whole_word_only;
    QCheckBox * flag_reg_exp;
    QCheckBox * flag_unicode;

    QTreeWidgetItem * pathToTreeLevel(const QString & path, QString & name);

    QRegularExpression buildRegex(const QString & pattern);
    void prepareResultsWidget();
    void prepareOptionsWidget();

    QRegularExpression regex;
public:
    ProjectSearchPanel(QWidget * parent = nullptr);
    void setProjectTree(ProjectTree * target_tree);

signals:
    void resultClicked(const QString & path, const EDITOR_POS_TYPE & pos, const QRegularExpression & regex);

public slots:
    void activate(const QString & pathes);
    void initiateSearch(const QString & pathes, const QString & search_predicate);

protected slots:
    void process();
    void addResult(FileSearchResult * result);
    void searchFinished();
};

#endif // PROJECT_SEARCH_PANEL_H
