#include "recursive_folder.h"

#include "file.h"

#include <qtreewidget.h>
#include <qdiriterator.h>
#include <qcolor.h>

void RecursiveFolder::proc(QTreeWidgetItem * view_item, const QString & path, QColor * color, const uint & level) {
    QDirIterator dir_it(path, QDir::AllDirs | QDir::NoDotAndDotDot);

    while(dir_it.hasNext()) {
        QString dir_path = dir_it.next();
        QString dir_name = dir_it.fileName();

        RecursiveFolder * folder = new RecursiveFolder(this, view_item, dir_name, level + 1, color);
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

        File * file = new File(level, name, path);
        _files.insert(name, file);

        QTreeWidgetItem * item = new QTreeWidgetItem(view_item, QStringList() << name);
        item -> setIcon(0, file -> ico());

        if (color) {
            item -> setBackgroundColor(0, *color);
        }
    }
}

RecursiveFolder::RecursiveFolder(const QString & path, QColor * color) : IFolder(path, false) {
    QString obj_name = name();
    FormatType ico_type = icoType(obj_name);

    QTreeWidgetItem * view_item = new QTreeWidgetItem(QStringList() << obj_name);
    view_item -> setData(0, Qt::UserRole, QVariant::fromValue<void *>(this));
    view_item -> setData(0, Qt::UserRole + 1, 0);
    view_item -> setIcon(0, Projects::obj().getIco(ico_type));

    bool color_clearing_required = false;

    if (!color) {
        color = identifyColor(ico_type);
        color_clearing_required = color != 0;
    }

    if (color) {
        view_item -> setBackgroundColor(0, *color);
    }

//        (Folder *)view_item -> data(0, Qt::UserRole).value<void *>() -> name();

    proc(view_item, path, color, 0);

    if (color_clearing_required) {
        delete color;
    }

    emit Projects::obj().projectInitiated(view_item);
}

RecursiveFolder::RecursiveFolder(IFolder * parent, QTreeWidgetItem * view_parent, const QString & folder_name, const uint & level, QColor * color) : IFolder(parent, folder_name, false) {
    FormatType ico_type = icoType(folder_name);

    QTreeWidgetItem * curr_view_item = new QTreeWidgetItem(view_parent, QStringList() << folder_name);
    curr_view_item -> setData(0, Qt::UserRole, QVariant::fromValue<void *>(this));
    curr_view_item -> setData(0, Qt::UserRole + 1, level);
    curr_view_item -> setIcon(0, Projects::obj().getIco(ico_type));

    bool color_clearing_required = false;

    if (!color) {
        color = identifyColor(ico_type);
        color_clearing_required = color != 0;
    }

    if (color) {
        curr_view_item -> setBackgroundColor(0, *color);
    }

    proc(curr_view_item, fullPath(), color, level);

    if (color_clearing_required) {
        delete color;
    }
}
