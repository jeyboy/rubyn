#ifndef DIR_H
#define DIR_H

#include <qstring.h>
#include <qstringbuilder.h>
//#include <qhash.h>

class Dir {
//    static QHash<QString, >
public:
    static bool hasEntry(const QString & path, const QString & name, const bool & is_folder = false);
    static bool createFolder(const QString & path, const QString & name);
    static bool createPath(const QString & path, const QString & name = QLatin1String("."));
    static bool removePath(const QString & path);
    static QString appPath(const QString & name = QString(), const bool & invalidate = false);
    static QString concatPaths(const QString & path, const QString & name);
    static bool showInGraphicalShell(const QString & path_in);
};

#endif // DIR_H
