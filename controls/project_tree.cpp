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

void ProjectTree::itemDoubleClicked(QTreeWidgetItem * item, int /*column*/) {
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
