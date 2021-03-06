#ifndef RECURSIVE_FOLDER_H
#define RECURSIVE_FOLDER_H

#include "ifolder.h"

class ProjectTreeEntry;

class RecursiveFolder : public IFolder {
    void proc(const uint & project_uid, ProjectTreeEntry * view_parent, const QString & path, QColor * color = nullptr, const uint & level = 0);
public:
    RecursiveFolder(const QString & path, QColor * color = nullptr);
    RecursiveFolder(const uint & project_uid, IFolder * parent, ProjectTreeEntry * view_parent, const QString & name, const uint & level, QColor * color = nullptr);
};

#endif // RECURSIVE_FOLDER_H
