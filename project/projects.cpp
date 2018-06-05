#include "projects.h"
#include "project.h"

Projects::Projects(QObject * parent) : QObject(parent) {

}

bool Projects::open(const QUrl & uri) {
    Project * project = new Project(this, uri);

   _projects.insert(uri, project);

    emit projectAdded(project);

    return true;
}
