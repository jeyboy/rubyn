#ifndef PROJECT_SEARCH_PANEL_H
#define PROJECT_SEARCH_PANEL_H

#include "misc/defines.h"

#include <qhash.h>
#include <qwidget.h>
#include <qregularexpression.h>
//#include <qhash.h>

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

    QTreeWidget * search_results;
    QLineEdit * predicate;
    QLineEdit * target_paths;
    ProjectTree * project_tree;
    DirSearch * dir_search;
    QHash<QString, QTreeWidgetItem *> search_items;

    QCheckBox * flag_case_sensitive;
    QCheckBox * flag_whole_word_only;
    QCheckBox * flag_reg_exp;
    QCheckBox * flag_unicode;

    QRegularExpression buildRegex(const QString & pattern);
    void prepareResultsWidget();
    void prepareOptionsWidget();

    QRegularExpression regex;
public:
    ProjectSearchPanel(QWidget * parent = nullptr);
    void setProjectTree(ProjectTree * target_tree);

signals:
    void resultClicked(const QString & path, const EDITOR_POS_TYPE & line_num, const EDITOR_POS_TYPE & pos_in_line);

public slots:
    void setPaths(const QString & pathes);
    void initiateSearch(const QString & pathes, const QString & search_predicate);

protected slots:
    void process();
    void addResult(FileSearchResult * result);
};

#endif // PROJECT_SEARCH_PANEL_H
