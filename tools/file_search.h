#ifndef FILESEARCH_H
#define FILESEARCH_H

#include "misc/defines.h"

#include <qobject.h>
#include <qthread.h>
#include <qregularexpression.h>

class File;

class FileSearch : public QObject {
    Q_OBJECT

    File * _file;
    QRegularExpression regex;
public:
    static FileSearch * asyncSearchInFile(const QRegularExpression & regex, File * file);

    FileSearch(const QRegularExpression & regex, File * file, QObject * parent = nullptr);

    void initiate();

signals:
    void finded(const QString & path, const EDITOR_POS_TYPE & pos, const EDITOR_LEN_TYPE & length, const QString & result, const EDITOR_POS_TYPE & result_pos);
};

#endif // FILESEARCH_H
