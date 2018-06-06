#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <qtreewidget.h>
#include <qdebug.h>

class ProjectTree : public QTreeWidget {
    Q_OBJECT
public:
    explicit ProjectTree(QWidget * parent = nullptr);

signals:
    void fileActivated(const QString & name, void * folder);
//    void fileDeleted(void * folder, const QString & name);

public slots:
    void branchAdded(QTreeWidgetItem * item);
    void folderAdded(const QString & name);
    void fileAdded(const QString & name, void *);

    void itemDoubleClicked(QTreeWidgetItem * item, int /*column*/) {
        QVariant item_data = item -> data(0, Qt::UserRole);

        if (item_data.isNull()) {
            QTreeWidgetItem * parent = item -> parent();
            QVariant parent_data = parent -> data(0, Qt::UserRole);

            QString name = item -> data(0, Qt::DisplayRole).toString();
            void * folder = parent_data.value<void *>();

            emit fileActivated(name, folder);
        } else {
            // edit folder name
        }
    }
};

#endif // PROJECT_TREE_H
