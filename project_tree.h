#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <qtreewidget.h>

class ProjectTree : public QTreeWidget {
    Q_OBJECT
public:
    explicit ProjectTree(QWidget * parent = nullptr);

signals:
    void fileActivated(void * file);
//    void fileDeleted(void * folder, const QString & name);

public slots:
    void branchAdded(QTreeWidgetItem * item);
    void folderAdded(const QString & name);
    void fileAdded(const QString & name, void *);

    void itemDoubleClicked(QTreeWidgetItem * item, int /*column*/) {
        void * file = item -> data(0, Qt::UserRole).value<void *>();

        emit fileActivated(file);
    }
};

#endif // PROJECT_TREE_H
