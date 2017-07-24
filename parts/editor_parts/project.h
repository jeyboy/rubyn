#ifndef PROJECT_H
#define PROJECT_H

#include <qobject.h>
#include <qurl.h>
#include <qhash.h>

class File;

class Project : public QObject {
    Q_OBJECT

    QUrl project_uri;
    QHash<QUrl, File *> files;
public:
    Project(const QUrl & uri = QUrl());
    ~Project();

    void rename(const QString & new_name);

    void addFile(const QUrl & uri = QUrl());
    void renameFile(const QUrl & uri, const QUrl & new_uri);
    void removeFile(const QUrl & uri);

signals:
    void fileAdded(const QUrl & project_uri, const QUrl & file_uri);
    void fileRemoved(const QUrl & project_uri, const QUrl & file_uri);
};

#endif // PROJECT_H
