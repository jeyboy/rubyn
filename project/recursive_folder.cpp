#include "recursive_folder.h"

#include "file.h"

#include "project/project_tree_entry.h"
#include <qdiriterator.h>
#include <qcolor.h>

void RecursiveFolder::proc(const uint & project_uid, ProjectTreeEntry * view_item, const QString & path, QColor * color, const uint & level) {
    QDirIterator dir_it(path, QDir::AllDirs | QDir::NoDotAndDotDot);

    while(dir_it.hasNext()) {
        QString dir_path = dir_it.next();
        QString dir_name = dir_it.fileName();

        RecursiveFolder * folder = new RecursiveFolder(project_uid, this, view_item, dir_name, level + 1, color);
        if (folder -> _valid) {
            _folders.insert(dir_name, folder);
        } else {
            QString source = dir_path % '/' % dir_name;
            QString msg = QLatin1String("Cant process");

            emit Projects::obj().errorOccurred(source, msg);
            delete folder;
        }
    }

    QDirIterator files_it(path, QDir::Files | QDir::Hidden);

    while(files_it.hasNext()) {
        QString path = files_it.next();
        QString name = files_it.fileName();

        File * file = new File(project_uid, level, name, path);
        _files.insert(name, file);

        ProjectTreeEntry * item = new ProjectTreeEntry(view_item, QStringList() << name);
        item -> setIcon(0, file -> ico());
        item -> setToolTip(0, name);

        if (color) {
            item -> setData(0, TREE_COLOR_UID, *color);
        }
    }
}


RecursiveFolder::RecursiveFolder(const QString & path, QColor * color) : IFolder(path, false) {
    QString obj_name = name();
    FormatType ico_type = icoType(obj_name);
    uint project_uid = File::pathToHash(path);

    ProjectTreeEntry * view_item = new ProjectTreeEntry(QStringList() << obj_name);
    view_item -> setData(0, TREE_FOLDER_UID, QVariant::fromValue<void *>(this));
    view_item -> setData(0, TREE_LEVEL_UID, 0);
    view_item -> setData(0, TREE_PATH_UID, path);
    view_item -> setIcon(0, Projects::obj().getIco(ico_type));
    view_item -> setToolTip(0, obj_name);

    bool color_clearing_required = false;

    if (!color) {
        color = identifyColor(ico_type);
        color_clearing_required = color != nullptr;
    }

    if (color) {
        view_item -> setData(0, TREE_COLOR_UID, *color);
    }

//        (Folder *)view_item -> data(0, TREE_FOLDER_UID).value<void *>() -> name();

    proc(project_uid, view_item, path, color, 0);

    if (color_clearing_required) {
        delete color;
    }

    emit Projects::obj().projectInitiated(project_uid, view_item);
}

RecursiveFolder::RecursiveFolder(const uint & project_uid, IFolder * parent, ProjectTreeEntry * view_parent, const QString & folder_name, const uint & level, QColor * color) : IFolder(parent, folder_name, false) {
    FormatType ico_type = icoType(folder_name, level);

    ProjectTreeEntry * curr_view_item = new ProjectTreeEntry(view_parent, QStringList() << folder_name);
    curr_view_item -> setData(0, TREE_FOLDER_UID, QVariant::fromValue<void *>(this));
    curr_view_item -> setData(0, TREE_LEVEL_UID, level);
    curr_view_item -> setIcon(0, Projects::obj().getIco(ico_type));
    curr_view_item -> setToolTip(0, folder_name);

    bool color_clearing_required = false;

    if (!color) {
        color = identifyColor(ico_type);
        color_clearing_required = color != nullptr;
    }

    if (color) {
        curr_view_item -> setData(0, TREE_COLOR_UID, *color);
    }

    proc(project_uid, curr_view_item, fullPath(), color, level);

    if (color_clearing_required) {
        delete color;
    }
}
