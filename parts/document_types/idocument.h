#ifndef IDOCUMENTS
#define IDOCUMENTS

#include <qstring>
#include <qtextdocument>

#include "parts/editor_parts/file.h"
#include "parts/lexer/lexer_factory.h"

class IDocument : public QTextDocument, public File {
protected:
    QIODevice * _device;
    Lexer * _lexer;

    bool fully_readed;
public:
    static IDocument * create(const QUrl & url, Project * project = 0);

    IDocument(const QString & path, const QString & name, QIODevice * device, Project * project = 0, Lexer * lexer = 0);
    virtual ~IDocument();

    inline FormatType mime() const { return _lexer ? _lexer -> format() : ft_unknown; }
    inline bool isFullyReaded() const { return fully_readed; }

    inline bool isText() const { return mime() & ft_text; }
    inline bool isImage() const { return mime() & ft_image; }
};

#endif // IDOCUMENTS
