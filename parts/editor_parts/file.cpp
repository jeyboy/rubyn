#include "file.h"

File::File(const QString & name, const QString & path, Project * project)
    : project(project), _path(path), _name(name)
{

}
