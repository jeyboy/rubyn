#ifndef RECURSIVE_FOLDER_H
#define RECURSIVE_FOLDER_H

#include "ifolder.h"

class QTreeWidgetItem;
class QColor;

class RecursiveFolder : public IFolder {
    void proc(QTreeWidgetItem * view_parent, const QString & path, QColor * color = 0);
    QColor * identifyColor(const QString & ico_type);
public:
    RecursiveFolder(const QString & path, QColor * color = 0);
    RecursiveFolder(IFolder * parent, QTreeWidgetItem * view_parent, const QString & name, QColor * color = 0);
};

#endif // RECURSIVE_FOLDER_H
