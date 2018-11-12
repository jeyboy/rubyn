#include "project_tree.h"

#include <qjsonobject.h>
#include "tools/json/json.h"
#include "tools/json/json_obj.h"
#include "project_tree_item_delegate.h"

ProjectTree::ProjectTree(QWidget * parent) : QTreeWidget(parent) {
    setHeaderHidden(true);
    setAutoScroll(false);

    QFont f(font());
    f.setPointSize(11);
    setFont(f);

    //TODO: need to set double font size
    setIconSize(QSize(22, 22));

    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));

//    setSortingEnabled(true);
//    sortByColumn(0, Qt::AscendingOrder);

    item_delegate = new ProjectTreeItemDelegate();
    setItemDelegate(item_delegate);
}

ProjectTree::~ProjectTree() {
    delete item_delegate;
}

void ProjectTree::saveStateHelper(QTreeWidgetItem * item, QJsonObject & obj) {
    QJsonObject sub;

    for(int i = 0; i < item -> childCount(); i++) {
        QTreeWidgetItem * sub_item = item -> child(i);

        if (sub_item -> isExpanded()) {
            QJsonObject subsub;

            saveStateHelper(sub_item, subsub);

            sub.insert(sub_item -> text(0), subsub);
        }
    }

    if (!sub.isEmpty()) {
        obj.insert(item -> text(0), sub);
    }
}

void ProjectTree::loadStateHelper(QTreeWidgetItem * item, JsonObj & obj) {
    JsonObj sub = obj.obj(item -> text(0));

    if (sub.isEmpty()) return;

    for(int i = 0; i < item -> childCount(); i++) {
        QTreeWidgetItem * sub_item = item -> child(i);

        if (sub.contains(sub_item -> text(0))) {
            JsonObj subsub = sub.obj(sub_item -> text(0));

            sub_item -> setExpanded(true);

            loadStateHelper(sub_item, subsub);
        }
    }
}

QByteArray ProjectTree::saveState() {
    QJsonObject obj;

    saveStateHelper(invisibleRootItem(), obj);

    return Json(obj).toJsonStr();
}

void ProjectTree::restoreState(const QByteArray & state) {
    setUpdatesEnabled(false);

    JsonObj obj(JsonObj::fromJsonStr(state));

    loadStateHelper(invisibleRootItem(), obj);

    setUpdatesEnabled(true);
}

void ProjectTree::selectItem(const QString & path, const bool & ensure_visible) {
    int items_count = topLevelItemCount();

    for(int i = 0; i < items_count; i++) {
        QTreeWidgetItem * item = topLevelItem(i);

        QString project_path = item -> data(0, Qt::UserRole + 2).toString();

        if (path.startsWith(project_path, Qt::CaseInsensitive)) {
            QString inner_path = path.mid(project_path.length());

            QStringList parts = inner_path.split('/', QString::SkipEmptyParts);
            bool satisfy = true;

            while(satisfy && !parts.isEmpty()) {
                QString part = parts.takeFirst();

                int child_count = item -> childCount();
                satisfy = false;

                for(int y = 0; y < child_count; y++) {
                    if (item -> child(y) -> text(0) == part) {
                        item = item -> child(y);
                        satisfy = true;
                        break;
                    }
                }
            }

            if (satisfy && item) {
                setCurrentItem(item);

                if (ensure_visible)
                    scrollToItem(item, PositionAtCenter);
            }

            break;
        }
    }
}


bool ProjectTree::search(const QString & pattern, QTreeWidgetItem * item) {
    bool empty = pattern.isEmpty();
    bool has_item = false;
    int items_count = item -> childCount();

    for(int i = 0; i < items_count; i++) {
        QTreeWidgetItem * child = item -> child(i);
        bool valid = false;

        if (child -> childCount() > 0) {
            valid = search(pattern, child);

            int pos = empty ? -1 : child -> text(0).indexOf(pattern, 0, Qt::CaseInsensitive);

            if (pos != -1)
                child -> setData(0, Qt::UserRole + 10, pos);

            has_item |= valid || pos != -1;
        } else {
            int pos = empty ? -1 : child -> text(0).indexOf(pattern, 0, Qt::CaseInsensitive);

            valid = pos != -1;
            has_item |= valid;

            if (valid)
                child -> setData(0, Qt::UserRole + 10, pos);
        }

        child -> setHidden(!valid);
    }

    return has_item;
}

void ProjectTree::clearSearch(QTreeWidgetItem * item) {
    int items_count = item -> childCount();

    for(int i = 0; i < items_count; i++) {
        QTreeWidgetItem * child = item -> child(i);

//        child -> setData(0, Qt::UserRole + 10, -1);

        clearSearch(child);
        child -> setHidden(false);
    }
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
