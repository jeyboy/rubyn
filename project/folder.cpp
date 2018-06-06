#include "folder.h"

#include "projects.h"
#include "file.h"

#include <qstringbuilder.h>
#include <qtreewidget.h>
#include <qdir.h>
#include <qdiriterator.h>

//Folder::Folder(QUrl & path) {

//}

void Folder::proc(QTreeWidgetItem * view_item, const QString & path) {
    QDirIterator dir_it(path, QDir::AllDirs | QDir::NoDotAndDotDot);

    while(dir_it.hasNext()) {
        QString dir_path = dir_it.next();
        QString dir_name = dir_it.fileName();

        Folder * folder = new Folder(this, view_item, dir_name, false);
        if (folder -> _valid) {
            _folders.insert(dir_name, folder);
        } else {
            QString source = dir_path % '/' % dir_name;
            QString msg = QLatin1Literal("Cant process");

            emit Projects::obj().errorOccurred(source, msg);
            delete folder;
        }
    }

    QDirIterator files_it(path, QDir::Files | QDir::Hidden);

    while(files_it.hasNext()) {
        QString path = files_it.next();
        QString name = files_it.fileName();

        File * file = new File(name, path);
        _files.insert(name, file);

        new QTreeWidgetItem(view_item, QStringList() << name);
    }
}

Folder::Folder(const QString & path, bool create) : _valid(true), _parent(0), _name(path) {
    if (create) {
        QDir dir(path);

        _valid = dir.mkpath(_name);
        create = !_valid;
    }

    if (!create) {
        QTreeWidgetItem * view_item = new QTreeWidgetItem(QStringList() << name());
        view_item -> setData(0, Qt::UserRole, QVariant::fromValue<void *>(this));

//        (Folder *)view_item -> data(0, Qt::UserRole).value<void *>() -> name();

        proc(view_item, path);

        emit Projects::obj().projectInitiated(view_item);
    }
}

Folder::Folder(Folder * parent, QTreeWidgetItem * view_parent, const QString & folder_name, bool create) : _valid(true), _parent(parent), _name(folder_name) {
    if (create) {
        QDir dir(parent -> fullPath());

        _valid = dir.mkdir(_name);
        create = !_valid;
    }

    if (!create) {
        QTreeWidgetItem * curr_view_item = new QTreeWidgetItem(view_parent, QStringList() << name());
        curr_view_item -> setData(0, Qt::UserRole, QVariant::fromValue<void *>(this));

        proc(curr_view_item, fullPath());
    }
}

Folder::~Folder() {
    qDeleteAll(_folders);
    qDeleteAll(_files);
}

QString Folder::name() {
    if (_parent) {
        return _name;
    }
    else {
        return _name.section('/', -1, -1);
    }
}

QString Folder::fullPath() {
    //        #ifdef Q_OS_LINUX
    //            '/' %
    //        #endif

    if (_parent) {
        return _parent -> fullPath() % '/' % _name;
    }
    else return _name;
}
