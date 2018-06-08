#include "project_tree.h"

ProjectTree::ProjectTree(QWidget * parent) : QTreeWidget(parent) {
    setHeaderHidden(true);

    setIconSize(QSize(22, 22));

    QFont f(font());
    f.setPointSize(11);
    setFont(f);

    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));

//    setSortingEnabled(true);
//    sortByColumn(0, Qt::AscendingOrder);
}

void ProjectTree::branchAdded(QTreeWidgetItem * item) {
    addTopLevelItem(item);
    item -> setExpanded(true);
}

void ProjectTree::folderAdded(const QString & /*name*/) {

}

void ProjectTree::fileAdded(const QString & /*name*/, void * ) {

}
