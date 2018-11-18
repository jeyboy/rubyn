#include "ifolder.h"

#include "file.h"
#include "misc/dir.h"
#include "highlighter/highlight_format_factory.h"

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
    Identifier uid = hid_none;

    switch(ico_type) {
        case ft_folder_public: { uid = hid_project_tree_public_range; break;}
        case ft_folder_log: { uid = hid_project_tree_log_range; break;}
        case ft_folder_temp: { uid = hid_project_tree_tmp_range; break;}
        case ft_folder_test: { uid = hid_project_tree_spec_range; break;}
        case ft_folder_db: { uid = hid_project_tree_db_range; break;}
        case ft_folder_config: { uid = hid_project_tree_config_range; break;}
        case ft_folder_app: { uid = hid_project_tree_app_range; break;}

        default:;
    }

    if (uid)
        return new QColor(HighlightFormatFactory::obj().getFormatFor(uid).background().color());
    else
        return nullptr;
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
