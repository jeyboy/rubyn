#include "project_tree.h"

ProjectTree::ProjectTree(QWidget * parent) : QTreeWidget(parent) {
    setHeaderHidden(true);

    QFont f(font());
    f.setPointSize(11);
    setFont(f);

    //TODO: need to set double font size
    setIconSize(QSize(22, 22));

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
