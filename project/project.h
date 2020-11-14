#ifndef PROJECT_H
#define PROJECT_H

#include "misc/defines.h"
#include "misc/version.h"
#include "code_formats.h"

#include <qurl.h>

class IFolder;
class File;

class Project {
    QUrl _project_uri;
    PROJECT_FORMAT_TYPE _project_format;

    IFolder * _root;
    QHash<FormatType, Version> _versions;
public:
    Project(const QUrl & uri = QUrl());
    ~Project();

    uint id();

    inline PROJECT_FORMAT_TYPE projectFormat() { return _project_format; }

    void rename(const QString & new_name);

    File * findFile(const QString & inner_path);

    void initVersions();

//    bool addFile(const QUrl & uri = QUrl(), const bool & open = true);
};

#endif // PROJECT_H
