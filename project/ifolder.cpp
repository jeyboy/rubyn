#include "ifolder.h"

#include "file.h"
#include "misc/dir.h"

FormatType IFolder::icoType(const QString & name, const uint & level) {
    if (level == 1) {
        if (name == QLatin1Literal("tmp")) {
            return FormatType::ft_folder_temp;
        } else if (name == QLatin1Literal("test") || name == QLatin1Literal("spec")) {
            return FormatType::ft_folder_test;
        } else if (name == QLatin1Literal("log")) {
            return FormatType::ft_folder_log;
        } else if (name == QLatin1Literal("public")) {
            return FormatType::ft_folder_public;
        } else if (name == QLatin1Literal("db")) {
            return FormatType::ft_folder_db;
        } else if (name == QLatin1Literal("config")) {
            return FormatType::ft_folder_config;
        } else if (name == QLatin1Literal("app")) {
            return FormatType::ft_folder_app;
        }
    }

    return FormatType::ft_folder;
}

QColor * IFolder::identifyColor(const FormatType & ico_type) {
    switch(ico_type) {
        case ft_folder_public: return new QColor(0, 255, 255, 24);
        case ft_folder_log: return new QColor(255, 39, 220, 24);
        case ft_folder_temp: return new QColor(255, 215, 0, 24);
        case ft_folder_test: return new QColor(75, 255, 0, 24);
//        case ft_folder_db: return new QColor(255, 0, 0, 16);
        case ft_folder_db: return new QColor(220, 220, 220, 108);
        case ft_folder_config: return new QColor(74, 90, 185, 24);
        case ft_folder_app: return new QColor(192, 127, 92, 24);


        default: return nullptr;
    }
}

IFolder::IFolder(const QString & path, const bool & create) : _valid(true), _parent(nullptr), _name(path) {
    if (create) {
        _valid = Dir::createPath(path, _name);
    }
}

IFolder::IFolder(IFolder * parent, const QString & folder_name, const bool & create) : _valid(true), _parent(parent), _name(folder_name) {
    if (create) {
        _valid = Dir::createFolder(parent -> fullPath(), _name);
    }
}

IFolder::~IFolder() {
    qDeleteAll(_folders);
    qDeleteAll(_files);
}

QString IFolder::name() {
    if (_parent) {
        return _name;
    }
    else {
        return _name.section('/', -1, -1);
    }
}

QString IFolder::fullPath() {
    //        #ifdef Q_OS_LINUX
    //            '/' %
    //        #endif

    if (_parent) {
        return _parent -> fullPath() % '/' % _name;
    }
    else return _name;
}

File * IFolder::findFile(QStringList & path_parts) {
    QString part = path_parts.takeFirst();

    if (path_parts.isEmpty()) {
        if (_files.contains(part)) {
            return _files[part];
        }
    } else {
        if (_folders.contains(part)) {
            return _folders[part] -> findFile(path_parts);
        }
    }

    return nullptr;
}
