#ifndef FILE_H
#define FILE_H

#include <qhash.h>

#include "parts/formats/format_types.h"

class Project;

class File {
    FormatType main_format;
    Project * project;
public:
    File(Project * project);
};

#endif // FILE_H
