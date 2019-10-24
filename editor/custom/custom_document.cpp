#include "custom_document.h"

#include "project/file.h"

using namespace Custom;

void Document::openFile() {
    QIODevice * source = _file -> source();
    qint64 content_length = source -> size();
    int pack_limit = 4999999;

    if (content_length > pack_limit) {
        char ch;
        int len = 0;
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
}

Document::Document(File * file, QObject * parent) : QObject(parent), _file(file) {
    openFile();
}

void Document::clear() {
    IBlock * curr;
    IBlock * it = _last -> prev;

    while(it != _root) {
        curr = it;
        it = it -> prev;
        delete curr;
    }

    if (_root -> next != _last) {
        _last -> prev = _root;
        _root -> next = _last;
    }
}
