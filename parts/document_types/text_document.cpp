#include "text_document.h"

#include "parts/editor_parts/file.h"

#include <qtextdocument.h>
#include <qtextcursor>
#include <QPlainTextDocumentLayout>

TextDocument::TextDocument(File * file, Lexer * lexer)
    : IDocument(), _doc(0), _tokens(new TokenList()), _scope(new Scope()), _lexer(lexer), _file(file) {

    setFullyReaded(true);
    QByteArray ar = _file -> source() -> readAll();

    _doc = new QTextDocument(ar);

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
