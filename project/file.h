#ifndef FILE_H
#define FILE_H

#include <qfile.h>
#include <qurl.h>
//#include <qhash.h>

//#include "misc/token_list.h"
//#include "parts/lexer/scopes/scope.h"
//#include "parts/formats/format_types.h"

#include "editor/idocument.h"
#include "code_formats.h"

class Project;
class TextDocument;
class ImageDocument;
class BinaryDocument;

class File {
    bool identifyType(const QString & name);
protected:
    IDocument * _doc;
    QIODevice * _device;

    FormatType _main_format;
    Project * _project;

    QString _path;
    QString _name;
public:
    void init(const QString & name, const QString & path, const bool & is_local);

    File(const QString & name, const QString & path = QString(), Project * project = 0);
    File(const QUrl & uri, Project * project = 0);

    virtual ~File() {
        delete _doc;

        if (_device) {
            if (_device -> isOpen())
                _device -> close();

            delete _device;
        }
    }

    inline IDocument * document() { return _doc; }
    inline QIODevice * source() { return _device; }

    inline QString name() const { return _name; }
    inline QString path() const { return _path; }

    inline bool isOpened() const { return _device && _device -> isOpen(); }
    inline bool isFullyReaded() const { return _device && _doc && _doc -> isFullyReaded(); }

    inline int formatType() const { return _main_format & ft_base; }

    inline bool isText() const { return _main_format & ft_text; }
    inline bool isImage() const { return _main_format & ft_image; }
    inline bool isBynary() const { return _main_format & ft_text; }

    TextDocument * asText();
    ImageDocument * asImage();
    BinaryDocument * asBinary();
};

#endif // FILE_H
