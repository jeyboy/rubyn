#ifndef FILE_H
#define FILE_H

#include <qurl.h>
#include <qhash.h>

#include "misc/token_list.h"
#include "parts/lexer/scopes/scope.h"
#include "parts/formats/format_types.h"
#include "parts/document_types/idocument.h"

class Project;

class File {
protected:
    IDocument * doc;

    FormatType _main_format;
    Project * _project;

    QString _path;
    QString _name;
public:
    void init(const QString & name, const QString & path, const bool & is_local);

    File(const QString & name, const QString & path = QString(), Project * project = 0);
    File(const QUrl & uri, Project * project = 0);

    virtual ~File() {}

    inline IDocument * document() { return doc; }

    inline QString name() const { return _name; }
    inline QString path() const { return _path; }

    inline bool isOpened() const { return doc && doc -> isOpened(); }
    inline bool isFullyReaded() const { return doc -> isReaded(); }

    inline int formatType() const {
        return _main_format & (ft_text | ft_image | ft_text);
    }
    inline bool isText() const { return _main_format & ft_text; }
    inline bool isImage() const { return _main_format & ft_image; }
    inline bool isBynary() const { return _main_format & ft_text; }
};

#endif // FILE_H
