#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qtextcursor>
#include <qtextdocument>
#include <QPlainTextDocumentLayout>
#include <qdebug.h>

#include "idocument.h"

#define READ_LIMIT (qint64)(512000) // ~512 kb
class TextDocument : public QTextDocument,  public IDocument {
    bool fully_readed;
public:
    TextDocument(const QString & mime, const QString & path, const QString & name, QIODevice * device)
        : IDocument(mime, path, name, device), fully_readed(true) {
        _doc_type = doc_type_text;

        setDocumentLayout(new QPlainTextDocumentLayout(this));

        if (_device -> size() < READ_LIMIT)
            setPlainText(_device -> readAll());
        else
            fully_readed = false;
            readNextBlock();
    }

    inline bool isFullyReaded() { return fully_readed; }

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
