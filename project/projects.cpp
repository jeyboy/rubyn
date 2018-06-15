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

Projects::Projects(QObject * parent) : QObject(parent) {}

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
