#include "project.h"

#include "projects.h"
#include "recursive_folder.h"
#include "project_format.h"

Project::Project(const QUrl & uri) {
    _project_format = ProjectIdentificator::proc(uri.toLocalFile());

    _root = new RecursiveFolder(uri.toLocalFile());
}

Project::~Project() {
    delete _root;
}

uint Project::id() {
    return _root -> id();
}

void Project::rename(const QString & /*new_name*/) {
    // TODO: write me
}

File * Project::findFile(const QString & inner_path) {
    QStringList parts = inner_path.split('/', Qt::SkipEmptyParts);
    return _root -> findFile(parts);
}

void Project::initVersions() {

}

//bool Project::addFile(const QUrl & uri, const bool & open) {
//    bool new_file = false;
//    File * file;

//    if (!_files.contains(uri)) {
//        new_file = true;
//        file = new File(File::pathToHash(uri.toLocal()), uri, this);

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
