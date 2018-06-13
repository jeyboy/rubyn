#include "projects.h"
#include "project.h"
#include "project_format.h"

#include <qpixmap.h>

QIcon & Projects::getIco(const QString & ico_type, const uint & size) {
    if (!_icons.contains(ico_type)) {
        QIcon ico;
        QPixmap pix = PREPARE_PIXMAP(QLatin1Literal(":/doc_types/") + ico_type, size);
        ico.addPixmap(pix);

        _icons.insert(ico_type, ico);
    }

    return _icons[ico_type];
}

Projects::Projects(QObject * parent) : QObject(parent) {

}

Projects::~Projects() {
    qDeleteAll(_projects);
    _projects.clear();
}

bool Projects::open(const QUrl & uri) {
    PROJECT_FORMAT_TYPE format_type = ProjectIdentificator::proc(uri);

    Project * project = new Project(uri);

   _projects.insert(uri, project);

    emit projectAdded(project);

    return true;
}
