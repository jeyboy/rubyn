#include "projects.h"
#include "project.h"

#include "controls/logger.h"
#include "project/ifolder.h"
#include "project/file.h"

#include <qfileinfo.h>
#include <qpixmap.h>
#include <qdebug.h>

QIcon & Projects::getIco(const FormatType & format_type, const FormatType & add_format_type) {
    FormatType wt = format_type;

    if (add_format_type) {
        wt = FormatType(wt + (add_format_type & 7));
    }

    if (!_icons.contains(wt)) {
        QIcon ico;
        QPixmap pix = PREPARE_PIXMAP(CodeFormats::formatIcoPath(format_type, add_format_type), icon_size);

        if (pix.isNull()) {
            qDebug() << "UNKNOW ICO FORMAT: " << format_type;
//            pix = PREPARE_PIXMAP(CodeFormats::formatIcoPath(ft_unknown), size);
            return getIco(ft_unknown, ft_unknown);
        }

        ico.addPixmap(pix);

        _icons.insert(wt, ico);
    }

    return _icons[wt];
}

FormatType Projects::identificateName(const QString & name) {
    if (_special_files_formats.contains(name))
        return _special_files_formats[name];
    else
        return ft_unknown;
}

void Projects::fileUsabilityChanged(File * file) {
    if (file -> openedAmount() == 0 && file -> isExternal()) {
        blockSignals(true);
        qDebug() << "Projects::fileUsabilityChanged remove file";
        QString uid = file -> uid();
        if (_external_files.contains(uid)) {
            delete _external_files.take(uid);
        } else {
            Logger::obj().error(LStr("Projects"), LStr("External file UID is not found while deleting"));
        }

        blockSignals(false);
    }
}

void Projects::closeProject(const QString & path) {
    Project * project = _projects.take(QUrl::fromLocalFile(path));

    delete project;

    emit projectRemoved(path);
}

bool Projects::identificate(const QString & name, void * folder, File *& file) {
    if (folder) {
        IFolder * _folder = reinterpret_cast<IFolder *>(folder);

        if (_folder == nullptr) {
            return false;
        }

        file = _folder -> getFile(name);
    } else {
        file = obj().findFile(QUrl::fromLocalFile(name));

        if (!file) {
            QHash<QString, File *> & external_files = obj()._external_files;
            QHash<QString, File *>::Iterator it = external_files.begin();

            for(; it != external_files.end(); it++) {
                if (it.value() -> path() == name) {
                   file = it.value();
                   break;
                }
            }
        }

        if (!file) {
            if (!QFileInfo::exists(name))
                return false;

            QFileInfo finfo(name);
            file = new File(0, finfo.fileName(), name, File::fo_open);
            file -> setExternal(true);
            obj()._external_files.insert(file -> uid(), file);
        }
    }

    return true;
}

Projects::Projects(QObject * parent) : QObject(parent), icon_size(22) {
    _special_files_formats.insert(QLatin1Literal("gemfile"), ft_file_gemfile);
    _special_files_formats.insert(QLatin1Literal("rakefile"), ft_file_rb);
    _special_files_formats.insert(QLatin1Literal("capfile"), ft_file_rb);
    _special_files_formats.insert(QLatin1Literal("config.ru"), ft_file_rb);
    _special_files_formats.insert(QLatin1Literal("procfile"), ft_file_yml);
}

Projects::~Projects() {
    qDeleteAll(_projects);
    _projects.clear();
}

bool Projects::open(const QUrl & uri) {   
    Project * project = new Project(uri);

   _projects.insert(uri, project);

    emit projectAdded(project);

    return true;
}

File * Projects::findFile(const QUrl & uri) {
    QString file_path = uri.toLocalFile();

    for(QHash<QUrl, Project *>::ConstIterator pro = _projects.cbegin(); pro != _projects.cend(); pro++) {
        QString pro_path = pro.key().toLocalFile();

        if (file_path.startsWith(pro_path, Qt::CaseInsensitive)) {
            Project * project = pro.value();
            return project -> findFile(file_path.mid(pro_path.length()));
        }
    }

    return nullptr;
}
