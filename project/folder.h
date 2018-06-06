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

    FileList _files;
    FolderList _folders;

    void proc(QTreeWidgetItem * view_parent,const QString & path);
public:
    Folder(const QString & path, bool create = true);
    Folder(Folder * parent, QTreeWidgetItem * view_parent, const QString & name, bool create = true);

    ~Folder();

    QString name();
    QString fullPath();

    File * getFile(const QString & name) {
        if (_files.contains(name))
            return _files[name];
        else
            return 0;
    }
};

#endif // FOLDER_H
