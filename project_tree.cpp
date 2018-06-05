#include "project_tree.h"

#include <qdebug.h>

ProjectTree::ProjectTree(QWidget * parent) : QTreeWidget(parent) {
    setHeaderHidden(true);

//    setSortingEnabled(true);
//    sortByColumn(0, Qt::AscendingOrder);
}

void ProjectTree::branchAdded(QTreeWidgetItem * item) {
    addTopLevelItem(item);
    item -> setExpanded(true);
}

void ProjectTree::folderAdded(const QString & name) {

}

void ProjectTree::fileAdded(const QString & name, void * ) {

}
