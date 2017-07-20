#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qtextcursor>
#include <QPlainTextDocumentLayout>
#include <qdebug.h>

#include "idocument.h"

#define READ_LIMIT (qint64)(512000) // ~512 kb

class TextDocument : public IDocument {
public:
    TextDocument(const QString & path, const QString & name, QIODevice * device, const FormatType & def_format = ft_unknown, const bool & complex = false)
        : IDocument(path, name, device, def_format, complex) {

        setDocumentLayout(new QPlainTextDocumentLayout(this));

        if (_device -> size() < READ_LIMIT)
            setPlainText(_device -> readAll());
        else
            fully_readed = false;
            readNextBlock();
    }

    void readNextBlock() {
        if (fully_readed) return;

        QTextCursor * myCursor = new QTextCursor(this);

//          // Insert an image
//          QTextImageFormat imageFormat;
//          imageFormat.setName("logo.jpg");
//          myCursor->insertImage(imageFormat, QTextFrameFormat::InFlow);
//          myCursor->insertText("\n");

        myCursor -> movePosition(QTextCursor::End);
        char * data = new char[qMin(_device -> bytesAvailable(), READ_LIMIT)];
        _device -> read(data, READ_LIMIT);
        myCursor -> insertText(QString(data));
        delete [] data;
        fully_readed = _device -> atEnd();
    }
};

#endif // TEXT_DOCUMENT
