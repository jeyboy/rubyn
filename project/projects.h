#ifndef PROJECTS_H
#define PROJECTS_H

#include <qhash.h>
#include <qurl.h>
#include <qicon.h>

#include "misc/singleton.h"
#include "code_formats.h"

#define PREPARE_PIXMAP(name, size) QPixmap(name).scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation)

class Project;
class File;
class QTreeWidgetItem;

class Projects : public QObject, public Singleton<Projects> {
    Q_OBJECT

    QHash<QUrl, Project *> _projects;
    QHash<FormatType, QIcon> _icons;
public:
    Projects(QObject * parent = 0);
    ~Projects();

    bool open(const QUrl & uri);

    inline Project * project(const QUrl & uri) { return _projects.value(uri, 0); }

    //TODO: need sync size with project tree
    QIcon & getIco(const FormatType & format_type, const uint & size = 22);
signals:
    void errorOccurred(QString & source, QString & info);

    void projectAdded(void * project);
    void projectRemoved(void * project);
    void projectRenamed(void * project, const QString & prev_name);

    void projectInitiated(QTreeWidgetItem *);

//    void fileAdded(File *);
//    void fileRemoved(File *);
//    void fileRenamed(File *, const QString & from, const QString & to);
};

#endif // PROJECTS_H