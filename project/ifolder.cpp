#include "ifolder.h"

#include "file.h"
#include <qdir.h>

FormatType IFolder::icoType(const QString & name) {
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
    }

    return FormatType::ft_folder;
}

QColor * IFolder::identifyColor(const FormatType & ico_type) {
    switch(ico_type) {
        case ft_folder_public: return new QColor(0, 255, 255, 16);
        case ft_folder_log: return new QColor(255, 39, 220, 16);
        case ft_folder_temp: return new QColor(255, 215, 0, 16);
        case ft_folder_test: return new QColor(75, 255, 0, 16);
        case ft_folder_db: return new QColor(255, 0, 0, 16);
        default: return 0;
    }
}

IFolder::IFolder(const QString & path, const bool & create) : _valid(true), _parent(0), _name(path) {
    if (create) {
        QDir dir(path);

        _valid = dir.mkpath(_name);
    }
}

IFolder::IFolder(IFolder * parent, const QString & folder_name, const bool & create) : _valid(true), _parent(parent), _name(folder_name) {
    if (create) {
        QDir dir(parent -> fullPath());

        _valid = dir.mkdir(_name);
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
