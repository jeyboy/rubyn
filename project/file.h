#ifndef FILE_H
#define FILE_H

#include <qfile.h>
#include <qurl.h>
//#include <qhash.h>
#include <qdebug.h>

#include "lexer/lexer_context.h"
#include "editor/idocument.h"
#include "projects.h"
#include "misc/format.h"

class TextDocument;
class ImageDocument;
class BinaryDocument;
class TreeDocument;
namespace Custom { class Document; }
class Folder;

class File {
    static bool identifyType(const QString & name, LexerContext *& context, const uint & level = 0);
    static bool identifyTypeByShebang(const QString & str, LexerContext *& context);
protected:
    IDocument * _doc;
    QIODevice * _device;
    LexerContext * _context;

    QString _path;
    QString _name;
    QString _uid;

    QString first_non_null_str;

    uint level;
    uint opened_count;

    bool is_external;

    bool userAskFileType();
    void initUid();
    bool openDevice(const QFile::OpenMode & def_mode = QFile::NotOpen);
    void closeDevice();
    const QFile::OpenMode openMode();

    friend class TextDocument;
    friend class ImageDocument;
    friend class BinaryDocument;
    friend class Custom::Document;
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

    inline IDocument * document() {
        if (!_doc) {
            if (!open())
                return nullptr;
        }

        return _doc;
    }
    inline QIODevice * source() { return _device; }

    inline QString unitSize() { return Info::toUnits(size()); }

    inline bool tooLarge() {
        return size() > 1499999;
//        return true;
    }

    inline qint64 size() {
        if (!isOpened())
            if (!openDevice())
                return 0;

        return _device -> size();
    }
    inline const QString & name() { return _name; }
    inline const QString & path() { return _path; }
    inline const QString & uid() { return _uid; }

    inline uint openedAmount() { return opened_count; }
    inline uint incOpened() {
        ++opened_count;
        qDebug() << "incOpened" << (opened_count);
//        Projects::obj().fileUsabilityChanged(this);
        return opened_count;
    }
    inline uint decOpened() {
        --opened_count;
        qDebug() << "decOpened" << (opened_count);
        Projects::obj().fileUsabilityChanged(this);
        return opened_count;
    }

    inline bool isExternal() { return is_external; }
    inline void setExternal(const bool & ext) { is_external = ext; }

    const QString & firstStr();

    FormatType icoType() { return _context -> _main_format; }
    QIcon ico();

    inline bool isOpened() const { return _device && _device -> isOpen(); }
    inline bool isChanged() const { return _doc && _doc -> isChanged(); }
    inline bool isFullyReaded() const { return _doc && _doc -> isFullyReaded(); }

    inline FormatType formatType() const { return _context -> _main_format; }
    inline int baseFormatType() const { return _context -> _main_format & ft_base_file_types; }

    inline bool isText() const { return _context -> _main_format & ft_text; }
    inline bool isCustomText() const { return _context -> _main_format & ft_custom_text; }
    inline bool isImage() const { return _context -> _main_format & ft_image; }
    inline bool isBinary() const { return _context -> _main_format & ft_binary; }
    inline bool isTree() const { return _context -> _main_format & ft_tree; }

    TextDocument * asText();
    Custom::Document * asCustomText();
    ImageDocument * asImage();
    BinaryDocument * asBinary();
    TreeDocument * asTree();

    bool dumpState(QVariant & data);
    bool restoreState(QVariant & data);
    int verticalScrollState(const bool & drop = false);
    bool setVerticalScrollState(const int & pos);
};

#endif // FILE_H
