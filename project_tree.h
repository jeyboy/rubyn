#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <qtreewidget.h>

class ProjectTree : public QTreeWidget {
    Q_OBJECT
public:
    explicit ProjectTree(QWidget * parent = nullptr);

public slots:
    void branchAdded(QTreeWidgetItem * item);
    void folderAdded(const QString & name);
    void fileAdded(const QString & name, void *);

    void itemDoubleClicked(QTreeWidgetItem * item, int column);
};

#endif // PROJECT_TREE_H
