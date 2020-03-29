#ifndef PROJECT_SEARCH_PANEL_H
#define PROJECT_SEARCH_PANEL_H

#include "misc/defines.h"

#include <qwidget.h>
//#include <qhash.h>

class QTreeWidget;
class QLineEdit;

//class QListWidget;
//class QListWidgetItem;
//class File;

class ProjectSearchPanel : public QWidget {
    Q_OBJECT

    QTreeWidget * search_results;
    QLineEdit * predicate;
    QLineEdit * target_paths;

    void process();
    void prepareResultsWidget();
public:
    ProjectSearchPanel(QWidget * parent = nullptr);

signals:
    void resultClicked(const QString & path, const EDITOR_POS_TYPE & line_num, const EDITOR_POS_TYPE & pos_in_line);

public slots:
    void initiateSearch(const QString & pathes, const QString & search_predicate);
};

#endif // PROJECT_SEARCH_PANEL_H
