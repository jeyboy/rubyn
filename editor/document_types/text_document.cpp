#include "text_document.h"

#include "project/file.h"

#include "lexer/ilexer.h"
#include "lexer/lexers_factory.h"

#include "editor/breakpoints_controller.h"

#include "highlighter/highlighter.h"

#include <qdebug.h>
#include <qtextcursor.h>
#include <qtextstream.h>
#include <qtextdocumentfragment.h>

#include <qelapsedtimer.h>

#include <qjsonobject.h>
#include <qjsonarray.h>

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
        highlighter = new Highlighter(this);

    return _lexer != nullptr;
}

bool TextDocument::registerStateChangedCallback(QObject * target, const char * slot) {
    connect(this, SIGNAL(hasChanges(QString, bool)), target, slot);

    return true;
}

TextDocument::TextDocument(File * file) : IDocument(), highlighter(nullptr), _file(file), layout(nullptr), force_word_wrap(false) {
    layout = new TextDocumentLayout(this);
    layout -> setCursorWidth(2);
    setDocumentLayout(layout);

    setFullyReaded(true);

    QIODevice * source = _file -> source();
    qint64 content_length = source -> size();
    int pack_limit = 4999999;

    if (content_length > pack_limit) {
        char ch;
        int len = 0;
        QTextCursor cursor(this);
        QByteArray buff;


        while(!source -> atEnd()) {
            ++len;

            if (_file -> source() -> getChar(&ch)) {
                if (ch == '\n' && len > pack_limit) {
                    qDebug() << source -> pos() << content_length;
                    cursor.insertFragment(QTextDocumentFragment::fromPlainText(buff));
                    len = 0;
                    buff.clear();
                }
                else buff.append(ch);
            }
        }

        if (len > 0) {
            cursor.insertFragment(QTextDocumentFragment::fromPlainText(buff));
        }



//        _file -> source() -> read()

//        QTextStream in(_file -> source());
//        QTextCursor cursor(this);

//        while (!in.atEnd()) {
//            qDebug() << in.pos() << content_length;
//            cursor.insertBlock();
//            cursor.insertText(in.readLine());
//        }

//        QTextDocumentFragment fragment();
//        cursor.insertFragment(fragment);


        source -> reset();
    } else {
        QByteArray ar = source -> readAll();
        ar.replace('\t', TextDocument::tab_space);
        setPlainText(ar);
    }

    identificateLexer();

    force_word_wrap = _file -> firstStr().length() > 10000 || content_length > 4999999;

    if (!highlighter)
        connect(this, SIGNAL(contentsChange(int, int, int)), this, SLOT(changesInContent(int,int,int)));
    else
        connect(this, SIGNAL(highlightingComplete()), this, SLOT(highlighterFinished()));


//    connect(this, &TextDocument::modificationChanged, this, &TextDocument::hasUnsavedChanges);
    connect(this, SIGNAL(contentsChanged()), this, SLOT(hasUnsavedChanges()));


    connect(this, &TextDocument::breakpointAdded, &BreakpointsController::obj(), &BreakpointsController::breakpointAdded);
    connect(this, &TextDocument::breakpointMoved, &BreakpointsController::obj(), &BreakpointsController::breakpointMoved);
    connect(this, &TextDocument::breakpointRemoved, &BreakpointsController::obj(), &BreakpointsController::breakpointRemoved);

    connect(&BreakpointsController::obj(), &BreakpointsController::activateBreakpoint, [=](const QString & path, const EDITOR_POS_TYPE & line_num) {
        if (_file -> path() == path)
            activateBreakpoint(line_num);
    });

    connect(&BreakpointsController::obj(), &BreakpointsController::removeBreakpoint, [=](const QString & path, const EDITOR_POS_TYPE & line_num) {
        if (_file -> path() == path)
            removeBreakpoint(line_num);
    });

    connect(this, &TextDocument::blocksLayoutChange, [=](const EDITOR_POS_TYPE & pos, const EDITOR_POS_TYPE & amount) {
        BreakpointsController::obj().breakpointMoved(_file -> path(), pos, pos + amount);
    });
}

TextDocument::~TextDocument() {

}

const QString & TextDocument::documentUid() { return _file -> uid(); }

void TextDocument::lexicate(const QString & text, IHighlighter * highlighter) {
    if (_lexer)
        _lexer -> handle(text, highlighter);
}

bool TextDocument::isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end) {
    if (_lexer)
        return _lexer -> isCompleterInitiable(lex, at_end);
    else
        return false;
}

bool TextDocument::isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end) {
    if (_lexer)
        return _lexer -> isCompleterContinuable(lex, at_end);
    else
        return false;
}

bool TextDocument::isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start) {
    if (_lexer)
        return _lexer -> isCompleterReplaceable(lex, at_start);
    else
        return false;
}

void TextDocument::paraOpositionStr(const PARA_TYPE & para, QString & res) {
    if (_lexer)
        _lexer -> paraOpositionStr(para, res);
    else
        res.clear();
}

LEXEM_TYPE TextDocument::getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_POS_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const bool & global_offset) {
    BlockUserData * udata = static_cast<BlockUserData *>(block.userData());

    start = global_offset ? block.position() : 0;

    if (udata) {
        TokenCell * tkn = udata -> tokenForPos(pos);

        if (tkn) {
            switch(tkn -> lexem) {
                case lex_blanks: {
                    start += pos;
                    length = 1;
                    return lex_blank;
                }
                case lex_tabs: {
                    start += pos;
                    length = 1;
                    return lex_tab;
                }

                default: {
                    start += tkn -> start_pos;
                    length = static_cast<int>(tkn -> length);
                    return tkn -> lexem;
                }
            }
        }
    }

    const QString block_text = block.text();

    if (block_text.isEmpty()) {
        length = 0;
        return lex_none;
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

    return lex_undefined;
}

ParaCell * TextDocument::getPara(const QTextBlock & block, const EDITOR_POS_TYPE & pos) {
    BlockUserData * udata = static_cast<BlockUserData *>(block.userData());

    return udata ? udata -> paraForPos(pos) : nullptr;
}

bool TextDocument::save() {
    return false; // TODO: remove me

    if (!isModified())
        return true;

    if (_file -> openDevice(QFile::WriteOnly)) {
        QTextStream writer(_file -> _device);
//        writer.setGenerateByteOrderMark(true);
//        writer.setCodec();

        writer << toPlainText();//toRawText();

        writer.flush();

        hasUnsavedChanges(false);
    }

    return false;
}

bool TextDocument::dump(QVariant & data) {
    if (_lexer) {
        QTextBlock blk = begin();
        int block_num = 0;

        QByteArray res;
        BlockUserData * udata;

        while(blk.isValid()) {
            int item_state = 0;
            udata = TextDocumentLayout::getUserDataForBlock(blk);

            if (udata && udata -> isFolded())
                item_state |= 1;

            if (!blk.isVisible())
                item_state |= 2;

            if (udata && udata -> hasBreakpoint())
                item_state |= 4;

            if (item_state > 0) {
                res.append(QByteArray::number(block_num));
                res.append('|');
                res.append(QByteArray::number(item_state));
                res.append('\n');
            }

            blk = blk.next();
            ++block_num;
        }

        if (res.isEmpty())
            return false;
        else {
            res.prepend('!' % QByteArray::number(_file -> size()) % '\n');
//            res = qCompress(res, 9);
            data = QVariant::fromValue(res);
            return true;
        }
    }

    return false;
}
bool TextDocument::restore(const QVariant & data) {
    QTextBlock blk = begin();

    if (!blk.isValid())
        return false;

    if (data.isValid()) {
        QByteArray res = data.toByteArray();
//        res = qUncompress(res);

        QByteArray::Iterator it = res.begin();
        QByteArray::Iterator it_end = res.end();

        if (*it != '!')
            return false;

        ++it; // move '!'

        int num = 0;

        for(; it != it_end; ++it, ++num) {
            if (*it == '\n')
                break;
        }

        if (num == 0)
            return false;
        else {
            QByteArray buff((it - num), num);

            if (buff.toLongLong() != _file -> size())
                return false;
        }

        ++it; // move '\n'

        int item_data;
        int block_pos = 0;
        int block_num = 0;
        int blocks_limit = blockCount();
        BlockUserData * udata;

        for(num = 0; it != it_end; ++it, ++num) {
            switch(*it) {
                case '|': {
                    QByteArray buff((it - num), num);

                    block_pos = buff.toInt();

                    if (block_pos > blocks_limit)
                        return false;

                    num = -1;
                break;}

                case '\n': {
                    if (num > 0) {
                        QByteArray buff((it - num), num);
                        item_data = buff.toInt();

                        while(block_num < block_pos) {
                            blk = blk.next();
                            ++block_num;
                        }

                        if (item_data > 0) {
                            if (item_data & 2) {
                                blk.setVisible(false);
                                blk.setLineCount(0);
                            }

                            if (item_data & 1 || item_data & 4) {
                                udata = TextDocumentLayout::getUserDataForBlock(blk);

                                if (!udata)
                                    return false;

                                if (item_data & 1) {
                                    udata -> setFolded(true);
                                }

                                if (item_data & 4) {
                                    emitBreakpointAdded(block_num);
                                    udata -> setBreakpoint(true);
                                }
                            }
                        }
                    }

                    num = -1;
                break;}
            }
        }
    }

    return false;
}

void TextDocument::emitBreakpointAdded(const EDITOR_POS_TYPE & line_num) { emit breakpointAdded(_file -> path(), line_num); }
void TextDocument::emitBreakpointRemoved(const EDITOR_POS_TYPE & line_num)  { emit breakpointRemoved(_file -> path(), line_num); }
void TextDocument::emitBreakpointMoved(const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & line_num)  { emit breakpointMoved(_file -> path(), old_line_num, line_num); }

//void TextDocument::readNextBlock() {
//    if (isFullyReaded()) return;

//    QTextCursor * myCursor = new QTextCursor(this);

////          // Insert an image
////          QTextImageFormat imageFormat;
////          imageFormat.setName("logo.jpg");
////          myCursor->insertImage(imageFormat, QTextFrameFormat::InFlow);
////          myCursor->insertText("\n");

//    myCursor -> movePosition(QTextCursor::End);

//    QIODevice * source = _file -> source();

//    char * data = new char[qMin(source -> bytesAvailable(), READ_LIMIT)];
//    source -> read(data, READ_LIMIT);
//    myCursor -> insertText(QString(data));
//    delete [] data;

//    setFullyReaded(source -> atEnd());
//}

void TextDocument::activateBreakpoint(const EDITOR_POS_TYPE & line_num) {
    qDebug() << "TextDocument::activateBreakpoint" << line_num;
}

void TextDocument::removeBreakpoint(const EDITOR_POS_TYPE & line_num) {
    qDebug() << "TextDocument::removeBreakpoint" << line_num;

    QTextBlock block = findBlockByNumber(line_num);

    if (block.isValid()) {
        BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(block);

        udata -> setBreakpoint(false);
        emit rowRedrawRequired(line_num);
    }
}

void TextDocument::hasUnsavedChanges(const bool & has) {
    emit hasChanges(_file -> uid(), has);
}

void TextDocument::changesInContent(int position, int removed_count, int added_count) {
    qDebug() << "changesInContent" << position << removed_count << added_count;
}

void TextDocument::highlighterFinished() {
    qDebug() << "highlighterFinished";
}
