#ifndef PROJECT_FORMAT_H
#define PROJECT_FORMAT_H

#pragma once

#include "misc/defines.h"

enum ProjectFormat : PROJECT_FORMAT_TYPE {
    pft_unknow = 0,
    pft_rails
};

class ProjectIdentificator {
public:
    static PROJECT_FORMAT_TYPE proc(const QUrl & url) {

    }
};

#endif // PROJECT_FORMAT_H
