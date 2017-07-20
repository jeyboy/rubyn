#ifndef IDOCUMENTS
#define IDOCUMENTS

#include <qstring>
#include <qtextdocument>
#include <qiodevice>

#include "parts/formats/format_types.h"

class IDocument : public QTextDocument {
protected:
    QString _path;
    QString _name;
    QIODevice * _device;
    FormatType _mime;
    bool complex;

    bool fully_readed;
public:
    static IDocument * create(const QString & path, const QString & name, QIODevice * device);

    IDocument(const QString & path, const QString & name, QIODevice * device, const FormatType & def_format = ft_unknown, const bool & complex = false) :
        _path(path), _name(name), _device(device), _mime(def_format), complex(complex), fully_readed(true) {

//        presets.insert(ft_rb, &RubyPreset::obj());
//        presets.insert(ft_sql, &SQLPreset::obj());

//        new Highlighter(this, presets[_mime]);
    }

    virtual ~IDocument() {
        if (_device) {
            if (_device -> isOpen())
                _device -> close();

            delete _device;
        }
    }

    inline QString name() const { return _name; }
    inline QString path() const { return _path; }
    inline FormatType mime() const { return _mime; }
    inline bool isFullyReaded() const { return fully_readed; }

    inline bool isText() const { return _mime & ft_text; }
    inline bool isImage() const { return _mime & ft_image; }
};

#endif // IDOCUMENTS
