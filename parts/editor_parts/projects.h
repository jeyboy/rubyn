#ifndef PROJECTS_H
#define PROJECTS_H

#include <qhash.h>

#include "misc/singleton.h"

class Project;

class Projects : public QObject, public Singleton<Projects> {
    Q_OBJECT

    QHash<QUrl, Project *> _projects;
public:
    Projects(QObject * parent = 0);
    ~Projects() {
        _projects.clear();
    }

    bool open(const QUrl & uri);

    inline Project * project(const QUrl & uri) { return _projects.value(uri, 0); }
signals:
    void projectAdded(const QUrl & project_uri, const QString & name);
    void projectRemoved(const QUrl & project_uri, const QString & name);
    void projectRenamed(const QUrl & project_uri, const QString & from_name, const QString & to_name);

    void textAdded(const QUrl & project_uri, const QUrl & file_uri);
    void imageAdded(const QUrl & project_uri, const QUrl & file_uri);
    void binaryAdded(const QUrl & project_uri, const QUrl & file_uri);

    void fileAdded(const QUrl & project_uri, const QUrl & file_uri);
    void fileRemoved(const QUrl & project_uri, const QUrl & file_uri);
    void fileRenamed(const QUrl & project_uri, const QUrl & from_uri, const QUrl & to_uri);
};

#endif // PROJECTS_H
