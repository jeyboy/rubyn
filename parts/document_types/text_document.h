#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qtextcursor>
#include <QPlainTextDocumentLayout>
#include <qdebug.h>

#include "idocument.h"
#include "parts/editor_parts/highlighter.h"
//#include "parts/langs/ruby/lexer_ruby.h"


#define READ_LIMIT (qint64)(512000) // ~512 kb

class Project;

class TextDocument : public IDocument {
public:
    TextDocument(const QString & path, const QString & name, QIODevice * device, Project * project = 0, Lexer * lexer = 0)
        : IDocument(path, name, device, project, lexer) {

        setDocumentLayout(new QPlainTextDocumentLayout(this));

        QByteArray ar = _device -> readAll();
        setPlainText(ar);
        _device -> close(); // this closed already in IDocument

//        if (_device -> size() < READ_LIMIT)
//            setPlainText(ar);
//        else {
//            fully_readed = false;
//            readNextBlock();
//        }

        if (lexer)
            new Highlighter(this, lexer);
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
