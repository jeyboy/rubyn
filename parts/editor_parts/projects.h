#ifndef PROJECTS_H
#define PROJECTS_H

#include <qhash.h>
#include <qurl.h>

#include "misc/singleton.h"

class Project;

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

    void textAdded(QObject * project, const QUrl & file_uri);
    void imageAdded(QObject * project, const QUrl & file_uri);
    void binaryAdded(QObject * project, const QUrl & file_uri);

    void fileAdded(QObject * project, const QUrl & file_uri);
    void fileRemoved(QObject * project, const QUrl & file_uri);
    void fileRenamed(QObject * project, const QUrl & from_uri, const QUrl & to_uri);
};

#endif // PROJECTS_H
