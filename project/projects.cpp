#include "projects.h"
#include "project.h"

Projects::Projects(QObject * parent) : QObject(parent) {
    Project * project = new Project(this);
    _projects.insert(QUrl(), project);

    project -> addFile();
}

bool Projects::open(const QUrl & uri) {
    Project * project = new Project(this, uri);

   _projects.insert(uri, project);

    emit projectAdded(project);

    return true;
}
