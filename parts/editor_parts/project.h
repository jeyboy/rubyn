#ifndef PROJECT_H
#define PROJECT_H

#include <qobject.h>
#include <qurl.h>
#include <qhash.h>

class File;
class IDocument;

class Project : public QObject {
    Q_OBJECT

    QUrl _project_uri;
    QHash<QUrl, File *> _files;
public:
    Project(QObject * parent, const QUrl & uri = QUrl());
    ~Project();

    void rename(const QString & new_name);

    bool addFile(const QUrl & uri = QUrl(), const bool & open = true);
    void renameFile(const QUrl & uri, const QUrl & new_uri);
    void removeFile(const QUrl & uri);

    inline File * file(const QUrl & url) { return _files.value(url, 0); }
    IDocument * document(const QUrl & url);
};

#endif // PROJECT_H
