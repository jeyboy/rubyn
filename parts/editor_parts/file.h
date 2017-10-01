#ifndef FILE_H
#define FILE_H

#include <qurl.h>
#include <qfile>
#include <qhash.h>

#include "parts/formats/format_types.h"

class Project;

class File {
protected:
    FormatType main_format;
    Project * project;

    QString _path;
    QString _name;
public:
    File(const QString & name, const QString & path = QString(), Project * project = 0);

    inline QString name() const { return _name; }
    inline QString path() const { return _path; }
};

#endif // FILE_H
