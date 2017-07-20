#ifndef IDOCUMENTS
#define IDOCUMENTS

#include <qstring>
#include <qtextdocument>
#include <qurl.h>
#include <qfile>
#include <qdebug.h>

#include "parts/formats/format_text.h"
#include "parts/highligters/highlighter.h"

class IDocument : public QTextDocument {
protected:
    QString _path;
    QString _name;
    QIODevice * _device;
    IFormat * _format;

    bool fully_readed;
public:
    static IDocument * create(const QUrl & url);

    IDocument(const QString & path, const QString & name, QIODevice * device, IFormat * def_format = &FormatText::obj()) :
        _path(path), _name(name), _device(device), _format(def_format), fully_readed(true) {

        IHighlightPreset * preset = _format -> highlightPreset();

        if (preset)
            new Highlighter(this, preset);
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
    inline FormatType mime() const { return _format -> formatType(); }
    inline bool isFullyReaded() const { return fully_readed; }

    inline bool isText() const { return mime() & ft_text; }
    inline bool isImage() const { return mime() & ft_image; }
};

#endif // IDOCUMENTS
