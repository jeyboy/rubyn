#include "project.h"

#include "file.h"

Project::Project(const QUrl & uri) {
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

void Project::addFile(const QUrl & uri) {
    if (uri.isEmpty() || uri.isRelative()) {
        // TODO: create new file
    } else {
        // TODO: open file
    }

    emit fileAdded(project_uri, uri);
}

void Project::renameFile(const QUrl & uri, const QUrl & new_uri) {
    // TODO: write me
}

void Project::removeFile(const QUrl & uri) {
    // TODO: write me

    emit fileRemoved(project_uri, uri);
}
