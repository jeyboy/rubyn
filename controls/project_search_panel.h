#ifndef PROJECT_SEARCH_PANEL_H
#define PROJECT_SEARCH_PANEL_H

#include "misc/defines.h"

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
    void addResult(const QString & path, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length, const QString & result, const EDITOR_POS_TYPE & result_pos);
};

#endif // PROJECT_SEARCH_PANEL_H
