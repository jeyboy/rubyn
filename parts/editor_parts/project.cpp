#include "project.h"

#include "projects.h"
#include "file.h"

Project::Project(QObject * parent, const QUrl & uri) : QObject(parent) {
    if (uri.isEmpty()) {
//      TODO: create empty project
    } else {
//      TODO: init tree for project
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
            case ft_text: { emit projects -> textAdded(this, uri); break; }
            case ft_image: { emit projects -> imageAdded(this, uri); break; }
            case ft_binary: { emit projects -> binaryAdded(this, uri); break; }
            default:
                delete file;
                return false;
        };
    }
    else if (new_file)
        emit projects -> fileAdded(this, uri);

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
