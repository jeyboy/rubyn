#include "project_tree.h"

ProjectTree::ProjectTree(QWidget * parent) : QTreeWidget(parent) {
    setHeaderHidden(true);
}

void ProjectTree::branchAdded(QTreeWidgetItem * item) {
    addTopLevelItem(item);
}

void ProjectTree::folderAdded(const QString & name) {

}

void ProjectTree::fileAdded(const QString & name, void * ) {

}
