#include "text_document.h"

#include "parts/editor_parts/file.h"

#include <qtextdocument.h>
#include <qtextcursor>
#include <QPlainTextDocumentLayout>

#include <qelapsedtimer.h>

QLatin1String TextDocument::tab_space = QLatin1Literal("  ");

TextDocument::TextDocument(File * file, Lexer * lexer)
    : IDocument(), _doc(0), _tokens(new TokenList()), _paras(new ParaList()), _scope(new Scope()), _lexer(lexer), _file(file) {

    qint64 content_length = _file -> source() -> size();

    setFullyReaded(true);

    QElapsedTimer timer;
    qDebug() << "START FILE READING" << "FILE SIZE: " << content_length;
    timer.start();

    if (content_length < 50000000) { // ~ 50 MB
        QByteArray ar = _file -> source() -> readAll();
        ar.replace('\t', TextDocument::tab_space);
        _doc = new QTextDocument(ar);
        _doc -> setProperty("tab_space", TextDocument::tab_space);
    } else {
        _doc = new QTextDocument();
        _doc -> setProperty("tab_space", QLatin1String("\t"));

        QTextStream stream(_file -> source());
        QTextCursor * cursor = new QTextCursor(_doc);

        while(!stream.atEnd()) {
            cursor -> insertBlock();
            cursor -> insertText(stream.readLine());
        }

        delete cursor;
    }

    qDebug() << "ELAPSED: " << timer.elapsed();

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

    if (lexer)
        new Highlighter(this);
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
