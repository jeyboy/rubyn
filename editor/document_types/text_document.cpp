#include "text_document.h"

#include "project/file.h"

#include "lexer/ilexer.h"
//#include "parts/langs/ruby/lexer_ruby.h"

#include <qtextdocument.h>
#include <qtextcursor>
#include <QPlainTextDocumentLayout>

#include <qelapsedtimer.h>

QLatin1String TextDocument::tab_space = QLatin1Literal("  ");

bool TextDocument::identificateLexer() {
//    FormatType format = _file -> formatType();

    //    if (lexer)
    //        new Highlighter(this);

    return false;
}

TextDocument::TextDocument(File * file) : IDocument(), _doc(0), _lexer(0), _file(file) {
    qint64 content_length = _file -> source() -> size();

    setFullyReaded(true);

    QElapsedTimer timer;
    qDebug() << "START FILE READING" << "FILE SIZE: " << content_length;
    timer.start();

    if (content_length < 50000000) { // ~ 50 MB
//        char * buff = new char[content_length];

        QByteArray ar = _file -> source() -> readAll();
//        _file -> source() -> read(buff, content_length);
        qDebug() << "readed";
        ar.replace('\t', TextDocument::tab_space);
        qDebug() << "replaced";
//        _doc = new QTextDocument(QString(buff));
        _doc = new QTextDocument(ar);
        _doc -> setProperty("tab_space", TextDocument::tab_space);

//        delete [] buff;
    } else {
        _doc = new QTextDocument();
        _doc -> setProperty("tab_space", QLatin1String("\t"));

        QTextStream stream(_file -> source());
        QTextCursor * cursor = new QTextCursor(_doc);

        while(!stream.atEnd()) {
            cursor -> insertText(stream.readLine());
            cursor -> insertBlock();
        }

        delete cursor;
    }


    _doc -> setDocumentLayout(new QPlainTextDocumentLayout(_doc));

    QTextOption option = _doc -> defaultTextOption();
    option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
//    else
//        option.setFlags(option.flags() & ~QTextOption::ShowTabsAndSpaces);
    option.setFlags(option.flags() | QTextOption::AddSpaceForLineAndParagraphSeparators);

    _doc -> setDefaultTextOption(option);


//        _device -> close(); // this closed already in IDocument

//        if (_device -> size() < READ_LIMIT)
//            setPlainText(ar);
//        else {
//            fully_readed = false;
//            readNextBlock();
//        }


    identificateLexer();
}

TextDocument::~TextDocument() {
    delete _doc;
    delete _lexer;
}

void TextDocument::lexicate(const QString & text, Highlighter * highlighter) {
    if (_lexer)
        _lexer -> handle(text, highlighter);
}

void TextDocument::calcFoldings() {
    if (_lexer)
        _lexer -> calcFoldings();
}

void TextDocument::readNextBlock() {
    if (isFullyReaded()) return;

    QTextCursor * myCursor = new QTextCursor(_doc);

//          // Insert an image
//          QTextImageFormat imageFormat;
//          imageFormat.setName("logo.jpg");
//          myCursor->insertImage(imageFormat, QTextFrameFormat::InFlow);
//          myCursor->insertText("\n");

    myCursor -> movePosition(QTextCursor::End);

    QIODevice * source = _file -> source();

    char * data = new char[qMin(source -> bytesAvailable(), READ_LIMIT)];
    source -> read(data, READ_LIMIT);
    myCursor -> insertText(QString(data));
    delete [] data;

    setFullyReaded(source -> atEnd());
}
