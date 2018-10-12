#include "text_document.h"

#include "project/file.h"

#include "lexer/ilexer.h"
#include "lexer/lexers_factory.h"

#include <qdebug.h>
#include <qtextdocument.h>
#include <qtextcursor.h>
#include <QPlainTextDocumentLayout>

#include <qelapsedtimer.h>

QLatin1String TextDocument::tab_space = QLatin1Literal("  ");

QHash<QChar, bool> TextDocument::word_boundary = {
    {'~', true}, {'#', true}, {'%', true},
    {'^', true}, {'&', true}, {'*', true},
    {'(', true}, {')', true}, {'+', true},
    {'{', true}, {'}', true}, {'|', true},
    {'"', true}, {'<', true}, {'>', true},
    {',', true}, {'.', true}, {'/', true},
    {';', true}, {'\'', true}, {'[', true},
    {']', true}, {'\\', true}, {'-', true},
    {'=', true}, {' ', true}, {'`', true}
};

bool TextDocument::identificateLexer() {
    FormatType format = _file -> formatType();

    _lexer = LexersFactory::obj().lexerFor(format);
    if (_lexer)
        new Highlighter(this);

    return _lexer != nullptr;
}

TextDocument::TextDocument(File * file) : IDocument(), pos(-1), removed(0), added(0), _doc(nullptr), _lexer(nullptr), _file(file) {
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


    connect(_doc, SIGNAL(contentsChange(int, int, int)), this, SLOT(changesInContent(int,int,int)));

    QPlainTextDocumentLayout * layout = new QPlainTextDocumentLayout(_doc);
    layout -> setCursorWidth(1);
    _doc -> setDocumentLayout(layout);

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
}

void TextDocument::lexicate(const QString & text, Highlighter * highlighter) {
    if (_lexer)
        _lexer -> handle(text, highlighter);
}

bool TextDocument::getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_POS_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos) {
    BlockUserData * udata = static_cast<BlockUserData *>(block.userData());

    start = block.position();

    if (udata) {
        TokenCell * tkn = udata -> tokenForPos(pos);

        if (tkn) {
            start += tkn -> start_pos;
            length = tkn -> length;
            return true;
        }
    }

    const QString block_text = block.text();

    if (block_text.isEmpty()) {
        length = 0;
        return true;
    }

    int offset = 0;
    for(int iter = pos - 1; iter >= 0; --iter, ++offset) {
        if (word_boundary.contains(block_text[iter]))
            break;
    }

    start += pos - offset;

    if (length != -1) {
        const int end_pos = block.length() - 1;
        length = offset;

        for(int iter = pos; iter < end_pos; ++iter, ++length) {
            if (word_boundary.contains(block_text[iter]))
                break;
        }
    }

    return true;
}

//void TextDocument::calcFoldings() {
//    if (_lexer)
//        _lexer -> calcFoldings();
//}

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

void TextDocument::changesInContent(int position, int removed_count, int added_count) {
    pos = position;
    removed = removed_count;
    added = added_count;
}
