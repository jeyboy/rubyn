#ifndef DIRSEARCH_H
#define DIRSEARCH_H

#include "misc/defines.h"

#include <qobject.h>
#include <qregularexpression.h>

class ProjectTree;
class File;
class QTreeWidgetItem;
class FileSearchResult;

class DirSearch : public QObject {
    Q_OBJECT

    QRegularExpression regex;
    int files_in_proc;
    bool in_proc;
protected:
    void searchInFile(File * file);
    void processItem(QTreeWidgetItem * item, const QString & path);
    void process(const QString & paths_value, ProjectTree * tree);
public:
    explicit DirSearch(QObject * parent = nullptr);

    void search(const QRegularExpression & pattern, const QString & paths_value, ProjectTree * tree = nullptr);
signals:
    void finded(FileSearchResult *);
    void searchFinished();
};

#endif // DIRSEARCH_H
