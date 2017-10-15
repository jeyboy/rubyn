#include "project.h"

#include "file.h"

Project::Project(QObject * parent, const QUrl & uri) : QObject(parent) {
    if (uri.isEmpty()) {
//      TODO: create empty project
    } else {
//      TODO: init tree for project
    }
}

Project::~Project() {
    qDeleteAll(files);
}

void Project::rename(const QString & new_name) {
    // TODO: write me
}

bool Project::addFile(const QUrl & uri, const bool & open) {
    bool new_file = false;
    File * file;

    if (!files.contains(url)) {
        new_file = true;
        file = new File(url, project);

        if (file -> isOpened())
            _files.insert(url, file);
        else {
            delete file;
            return false;
        }
    }
    else file = _files[url];

    if (open) {
        switch(file -> formatType()) {
            case ft_text: { emit textAdded(url); break;}
            case ft_image: { emit imageAdded(url); break;}
            case ft_binary: { emit binaryAdded(url); break;}
            default:
                delete file;
                return false;
        };
    }
    else if (new_file)
        emit parent() -> fileAdded(url);

    return true;
}

void Project::renameFile(const QUrl & uri, const QUrl & new_uri) {
    // TODO: write me
}

void Project::removeFile(const QUrl & uri) {
    // TODO: write me

//    emit fileRemoved(project_uri, uri);
}
