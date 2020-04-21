#include "dir.h"

#include <qapplication.h>
#include <qdir.h>
//#include <qfile.h>

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

bool Dir::removePath(const QString & path) {
    QFileInfo f(path);

    if (f.isFile()) {
        return QFile::remove(path);
    }

    QDir dir(path);
    return dir.removeRecursively();
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
