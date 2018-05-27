#include "project.h"

#include "projects.h"
#include "file.h"

#include <qdiriterator.h>
//#include "qfont.h"

Project::Project(QObject * parent, const QUrl & uri) : QObject(parent) {
    if (uri.isEmpty()) {
//      TODO: create empty project
    } else {
        if (uri.isLocalFile()) {
//            QDirIterator dir_it(uri.toLocalFile(), QDir::AllDirs | QDir::NoDotAndDotDot);

//            while(dir_it.hasNext()) {
//                QString path = dir_it.next();
//                QString name = dir_it.fileName();

//                if (!unproc_files.contains(path)) {
//                    if (name.endsWith(Extensions::dot_cue_ext, Qt::CaseInsensitive))
//                        res += proceedCue(path, name, node, pos, unproc_files, items);
//                    else {
//                        res++;
//                        items.insert(path, new IItem(node, LOCAL_ITEM_ATTRS(path, name), pos));
//                    }

//                    if (pos >= 0) // do not increment if we append items to the end of the list = -1
//                        pos++;
//                }
//            }
        } else {
            qDebug() << "Remote links not supported yet";
        }
    }
}

Project::~Project() {
    qDeleteAll(_files);
}

void Project::rename(const QString & new_name) {
    // TODO: write me
}

bool Project::addFile(const QUrl & uri, const bool & open) {
    bool new_file = false;
    File * file;

    if (!_files.contains(uri)) {
        new_file = true;
        file = new File(uri, this);

        if (file -> isOpened())
            _files.insert(uri, file);
        else {
            delete file;
            return false;
        }
    }
    else file = _files[uri];

    Projects * projects = reinterpret_cast<Projects *>(parent());

    if (open) {
        switch(file -> formatType()) {
            case ft_text:
            case ft_image:
            case ft_binary: {
                emit projects -> fileAdded(file); break;
            }
            default:
                delete file;
                return false;
        };
    }
    else if (new_file)
        emit projects -> fileAdded(file);

    return true;
}

void Project::renameFile(const QUrl & uri, const QUrl & new_uri) {
    // TODO: write me
}

void Project::removeFile(const QUrl & uri) {
    // TODO: write me

//    emit fileRemoved(project_uri, uri);
}

inline IDocument * Project::document(const QUrl & url) {
    File * file = _files.value(url, 0);
    return file ? file -> document() : 0;
}
