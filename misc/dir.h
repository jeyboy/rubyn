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
    static bool createPath(const QString & path, const QString & name = QLatin1Literal("."));
    static QString appPath(const QString & name = QString(), const bool & invalidate = false);
    static QString concatPaths(const QString & path, const QString & name);
};

#endif // DIR_H
