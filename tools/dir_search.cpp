#include "dir_search.h"

#include "controls/logger.h"
#include "controls/project_tree.h"

#include "project/file.h"
#include "project/projects.h"
#include "project/ifolder.h"

#include "tools/file_search.h"
#include "tools/file_search_result.h"

void DirSearch::searchInFile(File * file) {
    FileSearch * file_search = new FileSearch(regex, file);
    connect(file_search, &FileSearch::finded, [=](FileSearchResult * result) { emit finded(result); });
    file_search -> initiateAsync();
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
                searchInFile(file);
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

void DirSearch::search(const QRegularExpression & pattern, const QString & paths_value, ProjectTree * tree) {
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
}
