#ifndef PROJECT_H
#define PROJECT_H

#include "misc/defines.h"

#include <qurl.h>

class IFolder;

class Project : public QObject {
    Q_OBJECT

    QUrl _project_uri;
    PROJECT_FORMAT_TYPE _project_format;

    IFolder * root;
public:
    Project(QObject * parent, const QUrl & uri = QUrl());
    ~Project();

    inline PROJECT_FORMAT_TYPE projectFormat() { return _project_format; }

    void rename(const QString & new_name);

//    bool addFile(const QUrl & uri = QUrl(), const bool & open = true);
};

#endif // PROJECT_H
