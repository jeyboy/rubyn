#ifndef RECURSIVE_FOLDER_H
#define RECURSIVE_FOLDER_H

#include "ifolder.h"

class QTreeWidgetItem;

class RecursiveFolder : public IFolder {
    void proc(QTreeWidgetItem * view_parent, const QString & path, QColor * color = nullptr, const uint & level = 0);
public:
    RecursiveFolder(const QString & path, QColor * color = nullptr);
    RecursiveFolder(IFolder * parent, QTreeWidgetItem * view_parent, const QString & name, const uint & level, QColor * color = 0);
};

#endif // RECURSIVE_FOLDER_H
