#include "dir.h"

#include <qapplication.h>
#include <qdir.h>

bool Dir::hasEntry(const QString & path, const QString & name, const bool & is_folder) {
    if (is_folder) {
        QDir dir(concatPaths(path, name));
        return dir.exists();
    } else {
        QDir dir(path);
        return dir.exists(name);
    }
}

bool Dir::createFolder(const QString & path, const QString & name) {
    QDir dir(path);

    return dir.mkdir(name);
}
bool Dir::createPath(const QString & path, const QString & name) {
    QDir dir(path);

    return dir.mkpath(name);
}

QString Dir::appPath(const QString & name, const bool & invalidate) {
    QString res = qApp -> applicationDirPath();

    if (!name.isEmpty()) {
        if (invalidate)
            createPath(res, name);

        res = res % '/' % name;
    }

    return res;
}

QString Dir::concatPaths(const QString & path, const QString & name) {
    return path % '/' % name;
}
