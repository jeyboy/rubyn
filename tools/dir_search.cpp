#include "dir_search.h"

#include "controls/logger.h"
#include "controls/project_tree.h"

#include "project/file.h"
#include "project/projects.h"
#include "project/ifolder.h"

#include "tools/file_search.h"
#include "tools/file_search_result.h"

#include <qthreadpool.h>

void DirSearch::searchInFile(File * file) {
    ++files_in_proc;

    FileSearch * file_search = new FileSearch(regex, file);
    connect(file_search, &FileSearch::finded, [=](FileSearchResult * result) { emit finded(result); });
    connect(file_search, &FileSearch::finished, [=](const QString & /*path*/, const bool & /*status*/) {
        if (--files_in_proc == 0 && !in_proc) {
            emit searchFinished();
        }
    });

    QThreadPool::globalInstance() -> start(file_search);
//    file_search -> runAsync();
}

void DirSearch::processItem(QTreeWidgetItem * item, const QString & path) {
    if (ProjectTree::isFolder(item)) {
        int items_count = item -> childCount();

        for(int i = 0; i < items_count; i++) {
            QTreeWidgetItem * child = item -> child(i);
            processItem(child, path % '/' % ProjectTree::name(child));
        }
    } else {
        File * file;
        void * folder;
        QString name;

        if (ProjectTree::getFileData(item, name, folder)) {
            if (Projects::identificate(name, folder, file)) {
                if (file -> isSearchable()) {
                    searchInFile(file);
                }
            } else {
                Logger::obj().info("ProjectSearchPanel", "Cant identificate: " + path);
            }
        } else {
            Logger::obj().info("ProjectSearchPanel", "Cant find the data: " + path);
        }
    }
}

DirSearch::DirSearch(QObject *parent) : QObject(parent) {

}


//ImageProcessor* worker = new ImageProcessor();
//connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
//QtConcurrent::run(worker, &ImageProcessor::process);
// TODO: make async
void DirSearch::search(const QRegularExpression & pattern, const QString & paths_value, ProjectTree * tree) {
    files_in_proc = 0;
    in_proc = true;

    regex = pattern;
    QStringList paths = paths_value.split(LSTR(";"));

    QStringList::Iterator it = paths.begin();

    for(; it != paths.end(); it++) {
        if (tree) {
            QTreeWidgetItem * tree_item = tree -> findByPath(*it);

            if (tree_item) {
                processItem(tree_item, *it);
            } else {
                Logger::obj().info("ProjectSearchPanel", "Search in non project files do not support yet");
            }
        } else {
            // TODO: implement me
            Logger::obj().info("ProjectSearchPanel", "No project tree set");
        }
    }

    in_proc = false;

    if (--files_in_proc == 0) {
        emit searchFinished();
    }
}