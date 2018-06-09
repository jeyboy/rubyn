#ifndef RECURSIVE_FOLDER_H
#define RECURSIVE_FOLDER_H

#include "ifolder.h"

class QTreeWidgetItem;

class RecursiveFolder : public IFolder {
    void proc(QTreeWidgetItem * view_parent,const QString & path);
public:
    RecursiveFolder(const QString & path);
    RecursiveFolder(IFolder * parent, QTreeWidgetItem * view_parent, const QString & name);
};

#endif // RECURSIVE_FOLDER_H
