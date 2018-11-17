#include "project_tree.h"

#include <qevent.h>
#include <qmenu.h>
#include <qjsonobject.h>

#include "tools/json/json.h"
#include "tools/json/json_obj.h"
#include "project_tree_item_delegate.h"

ProjectTree::ProjectTree(QWidget * parent) : QTreeWidget(parent) {
    setHeaderHidden(true);
    setAutoScroll(false);
    setContextMenuPolicy(Qt::CustomContextMenu);

    QFont f(font());
    f.setPointSize(11);
    setFont(f);

    //TODO: need to set double font size
    setIconSize(QSize(22, 22));

    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));

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

        child -> setData(0, Qt::UserRole + 10, property_dropper);

        if (child -> childCount() > 0) {
            if (child -> data(0, Qt::UserRole + 11).isNull())
                child -> setData(0, Qt::UserRole + 11, child -> isExpanded());

            valid = search(pattern, child);

            if (valid && !child -> isExpanded())
                child -> setExpanded(true);
        }

        if (!empty) {
            QString child_text = child -> text(0);

            int pos = child_text.indexOf(pattern, 0, Qt::CaseInsensitive);

            if (pos != -1) {
                valid = true;
                child -> setData(0, Qt::UserRole + 10, pos);
            }
        }

        has_item |= empty || valid;
        child -> setHidden(!(valid || empty));
    }

    return has_item;
}

void ProjectTree::clearSearch(QTreeWidgetItem * item) {
    int items_count = item -> childCount();

    for(int i = 0; i < items_count; i++) {
        QTreeWidgetItem * child = item -> child(i);

//        child -> setData(0, Qt::UserRole + 10, QVariant(QVariant::Invalid));

        if (child -> childCount() > 0)
            clearSearch(child);

        child -> setHidden(false);

        QVariant expand_val = child -> data(0, Qt::UserRole + 11);
        if (!expand_val.isNull()) {
            child -> setExpanded(expand_val.toBool());
            child -> setData(0, Qt::UserRole + 11, property_dropper);
        }
    }
}

void ProjectTree::keyPressEvent(QKeyEvent * e) {
    int key_code = e -> key();

    if (key_code == Qt::Key_Escape) {
        emit closeSearch();
        e -> accept();
        return;
    } else {
        if (e -> modifiers() == Qt::NoModifier || e -> modifiers() == Qt::ShiftModifier) {
            QChar ch(key_code);

            if (ch.isLetterOrNumber() || ch.isPunct()) {
                emit searchRequired(e -> text());
                e -> accept();
                return;
            }
        }
        else {
            if (e -> modifiers() == Qt::ControlModifier && key_code == Qt::Key_F) {
                emit searchRequired(QLatin1Literal());
                e -> accept();
                return;
            }

            if (e -> modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && key_code == Qt::Key_F) {
                //TODO: need to start search in files
//                emit searchRequired(QLatin1Literal());
//                e -> accept();
//                return;
            }
        }
    }

    QTreeWidget::keyPressEvent(e);
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

bool ProjectTree::search(const QString & pattern) {
    setProperty("in_search", !pattern.isEmpty());
    setProperty("search_len", pattern.length());

    //        return search(pattern, invisibleRootItem());

    bool has_item = false;
    int items_count = topLevelItemCount();

    for(int i = 0; i < items_count; i++) {
        QTreeWidgetItem * child = topLevelItem(i);

        if (child -> childCount() > 0) {
            has_item |= search(pattern, child);
        }
    }

    return has_item;
}

void ProjectTree::clearSearch() {
    setProperty("in_search", false);
    setProperty("search_len", QVariant());
    clearSearch(invisibleRootItem());

    scrollToItem(currentItem(), PositionAtCenter);
}

void ProjectTree::showContextMenu(const QPoint & point) {
    QMenu menu(this);

    QTreeWidgetItem * curr_item = itemAt(point);
//    [=]() { color_picker_widget -> setVisible(!color_picker_widget -> isVisible()); }

    QAction action1(QIcon(QLatin1Literal(":/menu/collapse_all")), "Collapse All", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(collapseAll()));
    menu.addAction(&action1);

    QAction action2(QIcon(QLatin1Literal(":/menu/expand_all")), "Expand All", this);
    connect(&action2, SIGNAL(triggered()), this, SLOT(expandAll()));
    menu.addAction(&action2);

    if (curr_item && curr_item -> childCount() > 0) {
        QAction * action3 = new QAction(QIcon(QLatin1Literal(":/menu/collapse")), "Collapse children", &menu);
        connect(action3, SIGNAL(triggered()), this, SLOT(collapseChildren()));
        menu.addAction(action3);

        QAction * action4 = new QAction(QIcon(QLatin1Literal(":/menu/expand")), "Expand children", &menu);
        connect(action4, SIGNAL(triggered()), this, SLOT(expandChildren()));
        menu.addAction(action4);
    }

    menu.addSeparator();

    menu.exec(mapToGlobal(point));
}

void ProjectTree::collapseChildren(QTreeWidgetItem * curr_item) {
    if (!curr_item)
        curr_item = currentItem();

    if (!curr_item) return;

    int child_count = curr_item -> childCount();

    for(int i = 0; i < child_count; i++) {
        QTreeWidgetItem * child = curr_item -> child(i);

        child -> setExpanded(false);
        collapseChildren(child);
    }
}

void ProjectTree::expandChildren(QTreeWidgetItem * curr_item) {
    if (!curr_item)
        curr_item = currentItem();

    if (!curr_item) return;

    int child_count = curr_item -> childCount();

    for(int i = 0; i < child_count; i++) {
        QTreeWidgetItem * child = curr_item -> child(i);

        child -> setExpanded(true);
        expandChildren(child);
    }
}
