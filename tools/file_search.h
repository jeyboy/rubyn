#ifndef FILESEARCH_H
#define FILESEARCH_H

#include "misc/defines.h"

#include <qobject.h>
#include <qthread.h>
#include <qregularexpression.h>
#include <qrunnable.h>

class File;
class FileSearchResult;

class FileSearch : public QObject, public QRunnable {
    Q_OBJECT

    File * _file;
    QRegularExpression regex;
    int preview_window;
public:
    FileSearch(const QRegularExpression & regex, File * file, QObject * parent = nullptr);

    void setPreviewWindow(const int & new_preview_val) { preview_window = new_preview_val; }

    void run() override;
    void runAsync();

signals:
    void finded(FileSearchResult *);
    void finished(const QString & path, const bool & status);
};

#endif // FILESEARCH_H
