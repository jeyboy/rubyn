#ifndef FILE_H
#define FILE_H

#include <qfile.h>
#include <qurl.h>
//#include <qhash.h>

#include "editor/idocument.h"
#include "code_formats.h"
#include "projects.h"

class TextDocument;
class ImageDocument;
class BinaryDocument;
class TreeDocument;
class Folder;

class File {
    static bool identifyType(const QString & name, FormatType & format, const uint & level = 0);
    static bool identifyTypeByShebang(const QString & str, FormatType & format);
protected:
    IDocument * _doc;
    QIODevice * _device;

    FormatType _main_format;

    QString _path;
    QString _name;
    QString _uid;

    QString first_non_null_str;

    uint level;

    bool userAskFileType();
    void initUid();
    bool openDevice(const QFile::OpenMode & def_mode = QFile::NotOpen);
    void closeDevice();
    const QFile::OpenMode openMode();

    friend class TextDocument;
    friend class ImageDocument;
    friend class BinaryDocument;
public:
    static QString default_uid;

    enum FileOps {
        fo_none = 0,
        fo_open = 1,
    };

    bool identifyTypeByShebang(const QString & str);

    bool open();
    void close();
    inline bool save() { return _doc && _doc -> save(); }

    File(const uint & inproject_level, const QString & name, const QString & path, const FileOps & ops = fo_none);

    virtual ~File();

    inline IDocument * document() { return _doc; }
    inline QIODevice * source() { return _device; }

    inline qint64 size() { return _device -> size(); }
    inline const QString & name() { return _name; }
    inline const QString & path() { return _path; }
    inline const QString & uid() { return _uid; }

    FormatType icoType() { return _main_format; }
    QIcon ico() {
        if (_main_format == ft_file_ico) {
            QIcon ico(_path);

            if (ico.isNull() || ico.availableSizes().isEmpty())
                return Projects::obj().getIco(ft_broken);
            else
                return ico;
        }
        else return Projects::obj().getIco(icoType());
    }

    inline bool isOpened() const { return _device && _device -> isOpen(); }
    inline bool isChanged() const { return _doc && _doc -> isChanged(); }
    inline bool isFullyReaded() const { return _doc && _doc -> isFullyReaded(); }

    inline FormatType formatType() const { return _main_format; }
    inline int baseFormatType() const { return _main_format & ft_base_file_types; }

    inline bool isText() const { return _main_format & ft_text; }
    inline bool isImage() const { return _main_format & ft_image; }
    inline bool isBinary() const { return _main_format & ft_binary; }
    inline bool isTree() const { return _main_format & ft_tree; }

    TextDocument * asText();
    ImageDocument * asImage();
    BinaryDocument * asBinary();
    TreeDocument * asTree();

    bool dumpState(QVariant & data);
    bool restoreState(QVariant & data);
    int verticalScrollState(const bool & drop = false);
    bool setVerticalScrollState(const int & pos);
};

#endif // FILE_H
