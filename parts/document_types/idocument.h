#ifndef IDOCUMENTS
#define IDOCUMENTS

#include <qstring>
#include <qtextdocument>
#include <qurl.h>
#include <qfile>

class Lexer;

class IDocument : public QTextDocument {
protected:
    QString _path;
    QString _name;
    QIODevice * _device;

    bool fully_readed;
public:
    static IDocument * create(const QUrl & url);

    IDocument(const QString & path, const QString & name, QIODevice * device, Lexer * lexer = 0);
    virtual ~IDocument();

    inline QString name() const { return _name; }
    inline QString path() const { return _path; }
    inline FormatType mime() const { return _format -> formatType(); }
    inline bool isFullyReaded() const { return fully_readed; }

    inline bool isText() const { return mime() & ft_text; }
    inline bool isImage() const { return mime() & ft_image; }
};

#endif // IDOCUMENTS
