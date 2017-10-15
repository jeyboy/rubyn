#ifndef TEXT_DOCUMENT
#define TEXT_DOCUMENT

#include <qtextcursor>
#include <qtextdocument.h>
#include <QPlainTextDocumentLayout>
#include <qdebug.h>

#include "idocument.h"
#include "parts/lexer/scopes/scope.h"
#include "parts/editor_parts/highlighter.h"

//#include "parts/langs/ruby/lexer_ruby.h"


#define READ_LIMIT (qint64)(512000) // ~512 kb

class Project;

class TextDocument : public QTextDocument, public IDocument {
protected:
    TokenList * tokens;
    Scope * scope;
    Lexer * lexer;
public:
    TextDocument(QIODevice * device, Lexer * lexer = 0)
        : QTextDocument(), IDocument(device), tokens(new TokenList()), scope(new Scope()), lexer(lexer) {

        QByteArray ar = device -> readAll();

        setPlainText(ar);

        setDocumentLayout(new QPlainTextDocumentLayout(this));

        QTextOption option =  defaultTextOption();
        option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
    //    else
    //        option.setFlags(option.flags() & ~QTextOption::ShowTabsAndSpaces);
        option.setFlags(option.flags() | QTextOption::AddSpaceForLineAndParagraphSeparators);

        setDefaultTextOption(option);


//        _device -> close(); // this closed already in IDocument

//        if (_device -> size() < READ_LIMIT)
//            setPlainText(ar);
//        else {
//            fully_readed = false;
//            readNextBlock();
//        }

        if (lexer)
            new Highlighter(this);
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

    void lexicate(const QString & text, Highlighter * highlighter) {
        if (lexer)
            lexer -> handle(text, highlighter, scope, tokens);
    }
};

#endif // TEXT_DOCUMENT
