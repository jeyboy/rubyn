#ifndef PROJECTS_H
#define PROJECTS_H

#include <qhash.h>
#include <qurl.h>

#include "misc/singleton.h"

class Project;
class File;

class Projects : public QObject, public Singleton<Projects> {
    Q_OBJECT

    QHash<QUrl, Project *> _projects;
public:
    Projects(QObject * parent = 0);
    inline ~Projects() { _projects.clear(); }

    bool open(const QUrl & uri);

    inline Project * defaultProject() { return _projects.value(QUrl(), 0); }
    inline Project * project(const QUrl & uri) { return _projects.value(uri, 0); }
signals:
    void projectAdded(QObject * project);
    void projectRemoved(QObject * project);
    void projectRenamed(QObject * project, const QString & prev_name);

    void fileAdded(File *);
    void fileRemoved(File *);
    void fileRenamed(File *, const QString & from, const QString & to);
};

#endif // PROJECTS_H
