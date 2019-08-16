#include "projects.h"
#include "project.h"

#include "project/ifolder.h"
#include "project/file.h"

#include <qfileinfo.h>
#include <qpixmap.h>
#include <qdebug.h>

QIcon & Projects::getIco(const FormatType & format_type, const FormatType & add_format_type, const int & size) {
    FormatType wt = format_type;

    if (add_format_type) {
        wt = FormatType(wt + add_format_type & 7);
    }

    if (!_icons.contains(wt)) {
        QIcon ico;
        QPixmap pix = PREPARE_PIXMAP(CodeFormats::formatIcoPath(format_type, add_format_type), size);

        if (pix.isNull()) {
            qDebug() << "UNKNOW ICO FORMAT: " << format_type;
//            pix = PREPARE_PIXMAP(CodeFormats::formatIcoPath(ft_unknown), size);
            return getIco(ft_unknown, ft_unknown, size);
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

bool Projects::identificate(const QString & name, void * folder, File *& file, bool & is_external) {
    is_external = false;

    if (folder) {
        IFolder * _folder = reinterpret_cast<IFolder *>(folder);

        if (_folder == nullptr) {
            return false;
        }

        file = _folder -> getFile(name);
    } else {
        file = obj().findFile(QUrl::fromLocalFile(name));

        if (!file) {
            QFileInfo finfo(name);
            file = new File(0, finfo.baseName(), name);

            is_external = true;
        }
    }

    return true;
}

Projects::Projects(QObject * parent) : QObject(parent) {
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
