#ifndef FILE_H
#define FILE_H

#include <qurl.h>
#include <qfile>
#include <qhash.h>

#include "misc/token_list.h"
#include "parts/lexer/scopes/scope.h"
#include "parts/formats/format_types.h"

class Project;

class File {
protected:
    FormatType main_format;
    Project * project;

    TokenList * tokens;
    Scope * scope;

    QString _path;
    QString _name;
public:
    File(const QString & name, const QString & path = QString(), Project * project = 0);

    virtual ~File() {
        delete scope;
        delete tokens;
    }

    inline TokenList * tokensList() { return tokens; }
    inline Scope * varsScope() { return scope; }

    inline QString name() const { return _name; }
    inline QString path() const { return _path; }
};

#endif // FILE_H
