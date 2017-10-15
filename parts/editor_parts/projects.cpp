#include "projects.h"
#include "project.h"

Projects::Projects(QObject * parent = 0) : QObject(parent) {
    Project * project = new Project(this);
    _projects.insert(QUrl(), project);
}

bool Projects::open(const QUrl & uri) {
    Project * project = new  Project(this, uri);

   _projects.insert(uri, project);

    emit projectAdded(uri, uri.toString());

    return true;
}
