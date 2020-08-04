#ifndef PROJECT_TREE_ENTRY_H
#define PROJECT_TREE_ENTRY_H

#include <qtreewidget.h>

#include "misc/defines.h"

class ProjectTreeEntry : public QTreeWidgetItem {
public:
    ProjectTreeEntry(const QTreeWidgetItem & itm) : QTreeWidgetItem(itm) {}

    ProjectTreeEntry(const QStringList & strings, int type = Type) : QTreeWidgetItem(strings, type) {}

    ProjectTreeEntry(ProjectTreeEntry * parent, const QStringList & strings, int type = Type) : QTreeWidgetItem(parent, strings, type) {}

    virtual bool operator < (const QTreeWidgetItem & other) const {
        return sortKey().compare(((const ProjectTreeEntry)(other)).sortKey(), Qt::CaseInsensitive) < 0;
    }

    inline QString sortKey() const {
        return (data(0, TREE_FOLDER_UID).isValid() ? "0" : "1") +
            data(0, Qt::DisplayRole).toString();
    }
};


#endif // PROJECT_TREE_ENTRY_H
