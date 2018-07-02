#include "projects.h"
#include "project.h"
#include "project_format.h"

#include <qpixmap.h>
#include <qdebug.h>

QIcon & Projects::getIco(const FormatType & format_type, const uint & size) {
    if (!_icons.contains(format_type)) {
        QIcon ico;
        QPixmap pix = PREPARE_PIXMAP(CodeFormats::formatIcoPath(format_type), size);

        if (pix.isNull()) {
            qDebug() << "UNKNOW ICO FORMAT: " << format_type;
            pix = PREPARE_PIXMAP(CodeFormats::formatIcoPath(ft_unknown), size);
        }

        ico.addPixmap(pix);

        _icons.insert(format_type, ico);
    }

    return _icons[format_type];
}

FormatType Projects::identificateName(const QString & name) {
    if (_special_files_formats.contains(name))
        return _special_files_formats[name];
    else
        return ft_unknown;
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
    PROJECT_FORMAT_TYPE format_type = ProjectIdentificator::proc(uri.toLocalFile());

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

    return 0;
}
