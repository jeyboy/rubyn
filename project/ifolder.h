#ifndef IFOLDER_H
#define IFOLDER_H

#include <qstring.h>
#include <qstringbuilder.h>
#include <qhash.h>

#include "code_formats.h"
#include "misc/defines.h"

class File;
class IFolder;
class QColor;

typedef QHash<QString, File *> FileList;
typedef QHash<QString, IFolder *> FolderList;

class IFolder {
protected:
    bool _valid;

    IFolder * _parent;

    QString _name;

    FileList _files;
    FolderList _folders;

    FormatType icoType(const QString & name, const uint & level = 0);
    QColor * identifyColor(const FormatType & ico_type);
public:
    IFolder(const QString & path, const bool & create = true);
    IFolder(IFolder * parent, const QString & folder_name, const bool & create = true);

    virtual ~IFolder();

    QString name();
    QString fullPath();
    uint id();

    File * findFile(QStringList & path_parts);

    File * getFile(const QString & name) {
        if (_files.contains(name))
            return _files[name];
        else
            return nullptr;
    }
};

#endif // IFOLDER_H
