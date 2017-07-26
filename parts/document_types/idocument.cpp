#include "idocument.h"
#include "documents_types.h"
#include "parts/formats/iformat.h"
#include "parts/highligters/highlighter.h"

IDocument * IDocument::create(const QUrl & url) {
    bool isLocal = url.isLocalFile();
    QString path = isLocal ? url.toLocalFile() : url.toString();

    QString name;
    QIODevice * device = 0;
    IFormat * f;

    if (isLocal)
        name = path.section('/', -1, -1);
    else
        name = path;

    bool res = IFormat::determine(name, f);

    if (!res) {
        //TODO: ask user about preffered type of file
    }

    FormatType format = f -> formatType();

    bool is_text = format & ft_text, is_bynary = format & ft_bynary;

    if (is_text || is_bynary) {
        if (isLocal) {
            QFile * file = new QFile(path);

            //TODO: update permissions for file before opening
            QFile::OpenMode omode = QFile::ReadOnly;
            if (is_text)
                omode |= QFile::Text;

            if (file -> open(omode)) {
                device = file;
            } else {
                file -> deleteLater();
                return 0;
            }
        } else {
            //TODO: proceed remote file
            return 0; // but not now ...
        }

        //TODO: return BynaryDocument if is_bynary

        return new TextDocument(path, name, device, f);
    }

    if (format & ft_image)
        return new ImageDocument(path, name, device, f);

    return 0;
}

IDocument::IDocument(const QString & path, const QString & name, QIODevice * device, IFormat * def_format) :
    _path(path), _name(name), _device(device), _format(def_format), fully_readed(true) {

    IHighlightPreset * preset = _format -> highlightPreset();

    if (preset)
        new Highlighter(this, preset);
}

IDocument::~IDocument() {
    if (_device) {
        if (_device -> isOpen())
            _device -> close();

        delete _device;
    }
}
