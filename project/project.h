#ifndef PROJECT_H
#define PROJECT_H

#include "misc/defines.h"

#include <qurl.h>

class File;
class Folder;
class IDocument;

class Project : public QObject {
    Q_OBJECT

    QUrl _project_uri;
    PROJECT_FORMAT_TYPE _project_format;

    Folder * root;
public:
    Project(QObject * parent, const QUrl & uri = QUrl());
    ~Project();

    inline PROJECT_FORMAT_TYPE projectFormat() { return _project_format; }

    void rename(const QString & new_name);

//    bool addFile(const QUrl & uri = QUrl(), const bool & open = true);

//    inline File * file(const QUrl & url) { return _files.value(url, 0); }
//    IDocument * document(const QUrl & url);

//signals:
//    void fileAdded(File *);
//    void fileRenamed(File *);
//    void fileRemoved(File *);
};

#endif // PROJECT_H
