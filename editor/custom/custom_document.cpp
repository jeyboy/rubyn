#include "custom_document.h"

#include "project/file.h"

#include "custom_text_block.h"

using namespace Custom;

void Document::openFile() {
    QIODevice * source = _file -> source();

    char ch;
    QByteArray buff;
    buff.reserve(2048);

    while(!source -> atEnd()) {
        if (_file -> source() -> getChar(&ch)) {
            if (ch == '\n') {
                addLine(buff);
                buff.clear();
            }
            else buff.append(ch);
        }
    }

    if (!buff.isEmpty()) {
        addLine(buff);
    }
}

Document::Document(File * file, QObject * parent) : QObject(parent), _root(nullptr), _last(nullptr), _curr(nullptr), _inline_pos(0), _file(file) {
    //    root = new TokenCell(lex_none, 0, 0);
    //    last = new TokenCell(lex_end_doc, 0, 0, root);

    openFile();
}

Document::~Document() {
    if (_root != _last) {
        clear();
    }

    delete _root;
    delete _last;
}

void Document::clear() {
    IBlock * curr_it;
    IBlock * it = _last -> prev;

    while(it != _root) {
        curr_it = it;
        it = it -> prev;
        delete curr_it;
    }

    if (_root -> next != _last) {
        _last -> prev = _root;
        _curr = _root -> next = _last;
    }

    _inline_pos = 0;
}

void Document::addLine(const QString & line) {
    _curr = new TextBlock(line, _last);
}
