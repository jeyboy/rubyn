#ifndef FILESEARCH_H
#define FILESEARCH_H

#include "misc/defines.h"

#include <qobject.h>
#include <qthread.h>
#include <qregularexpression.h>

class File;
class FileSearchResult;

class FileSearch : public QObject {
    Q_OBJECT

    File * _file;
    QRegularExpression regex;
public:
    FileSearch(const QRegularExpression & regex, File * file, QObject * parent = nullptr);

    void initiate();
    void initiateAsync();

signals:
    void finded(FileSearchResult *);
};

#endif // FILESEARCH_H
