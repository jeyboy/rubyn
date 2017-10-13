#include "file.h"

File::File(const QString & name, const QString & path, Project * project)
    : project(project), tokens(new TokenList()), scope(new Scope()), _path(path), _name(name)
{

}
