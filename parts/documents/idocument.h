#ifndef IDOCUMENTS
#define IDOCUMENTS

#include <qstring>
#include <qiodevice>

enum DocumentType {
    doc_type_text,
    doc_type_image
};

class IDocument {
protected:
    DocumentType _doc_type;
    QString _path;
    QString _name;
    QString _mime;
    QIODevice * _device;
public:
    IDocument(const QString & mime, const QString & path, const QString & name, QIODevice * device) : _path(path), _name(name), _mime(mime), _device(device) {}
    virtual ~IDocument() {
        if (_device) {
            if (_device -> isOpen())
                _device -> close();

            delete _device;
        }
    }

    inline QString name() const { return _name; }
    inline QString path() const { return _path; }
    inline QString mime() const { return _mime; }

    static QString extractMime(const QString & path) {
        QString mime = path.section('.', -1, -1);
        if (!(mime != path && mime.indexOf(' ') == -1))
            mime.clear();

        return mime;
    }
};

#endif // IDOCUMENTS
