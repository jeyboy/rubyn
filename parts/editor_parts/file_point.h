#ifndef FILE_POINT_H
#define FILE_POINT_H

class File;

struct FilePoint {
    File * file;
    int line;
    int left;
};

#endif // FILE_POINT_H
