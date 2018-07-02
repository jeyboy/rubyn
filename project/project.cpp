#include "project.h"

#include "projects.h"
#include "recursive_folder.h"

Project::Project(const QUrl & uri) {
    root = new RecursiveFolder(uri.toLocalFile());
}

Project::~Project() {
    delete root;
}

void Project::rename(const QString & /*new_name*/) {
    // TODO: write me
}

File * Project::findFile(const QString & inner_path) {
    QStringList parts = inner_path.split('/', QString::SkipEmptyParts);
    return root -> findFile(parts);
}

//bool Project::addFile(const QUrl & uri, const bool & open) {
//    bool new_file = false;
//    File * file;

//    if (!_files.contains(uri)) {
//        new_file = true;
//        file = new File(uri, this);

//        if (file -> isOpened())
//            _files.insert(uri, file);
//        else {
//            delete file;
//            return false;
//        }
//    }
//    else file = _files[uri];

//    Projects * projects = reinterpret_cast<Projects *>(parent());

//    if (open || new_file) {
//        emit projects -> fileAdded(file);
//    }

//    return true;
//}
