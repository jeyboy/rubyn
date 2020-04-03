#ifndef DIRSEARCH_H
#define DIRSEARCH_H

#include "misc/defines.h"

#include <qobject.h>
#include <qregularexpression.h>

class ProjectTree;
class File;
class QTreeWidgetItem;


//ImageProcessor* worker = new ImageProcessor();
//connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
//QtConcurrent::run(worker, &ImageProcessor::process);



class DirSearch : public QObject {
    Q_OBJECT

    QRegularExpression regex;
protected:
    void searchInFile(File * file);
    void processItem(QTreeWidgetItem * item, const QString & path);
public:
    explicit DirSearch(QObject * parent = nullptr);

    void search(const QRegularExpression & pattern, const QString & paths_value, ProjectTree * tree = nullptr);
signals:
    void finded(const QString & path, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length, const QString & result, const EDITOR_POS_TYPE & result_pos);
};

#endif // DIRSEARCH_H
