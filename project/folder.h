#ifndef FOLDER_H
#define FOLDER_H

#include <qstring.h>
#include <qhash.h>

class QDir;
class File;
class Folder;
class QTreeWidgetItem;

typedef QHash<QString, File *> FileList;
typedef QHash<QString, Folder *> FolderList;

class Folder {
    bool _valid;
    Folder * _parent;

    QString _name;

    FileList files;
    FolderList folders;

    void proc(QTreeWidgetItem * view_parent,const QString & path);
public:
    Folder(QString & path, bool create = true);
    Folder(Folder * parent, QTreeWidgetItem * view_parent, QString & name, bool create = true);

    ~Folder();

    QString name();
    QString fullPath();
};

#endif // FOLDER_H
