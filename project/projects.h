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
    QHash<QString, FormatType> _special_files_formats;
    QHash<QString, File *> _external_files;
public:
    static bool identificate(const QString & name, void * folder, File *& file);

    Projects(QObject * parent = nullptr);
    ~Projects();

    bool open(const QUrl & uri);
    File * findFile(const QUrl & uri);

    inline Project * project(const QUrl & uri) { return _projects.value(uri, nullptr); }

    //TODO: need sync size with project tree
    QIcon & getIco(const FormatType & format_type, const FormatType & add_format_type = ft_unknown, const int & size = 22);
    FormatType identificateName(const QString & name);

    void fileUsabilityChanged(File * file);

public slots:
    void closeProject(const QString & path);

signals:
    void errorOccurred(QString & source, QString & info);
    void fileIconChanged(const QString & name, const QIcon & ico);

    void projectAdded(void * project);
    void projectRemoved(const QString & path);
    void projectRenamed(void * project, const QString & prev_name);

    void projectInitiated(QTreeWidgetItem *);

//    void fileAdded(File *);
//    void fileRemoved(File *);
    void fileRemoved(const QString & uid);
//    void fileRenamed(File *, const QString & from, const QString & to);
};

#endif // PROJECTS_H
