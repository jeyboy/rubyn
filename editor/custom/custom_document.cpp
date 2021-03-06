#include "custom_document.h"

#include "project/file.h"

#include "custom_text_block.h"

using namespace Custom;

void Document::openFile() {
    QIODevice * source = _file -> source();

    char ch;
    QByteArray buff;
    buff.reserve(4096);

    while(!source -> atEnd()) {
        if (_file -> source() -> getChar(&ch)) {
            if (ch == '\n') {
                appendLine(buff);
                buff.clear();
            }
            else buff.append(ch);
        }
    }

    if (!buff.isEmpty()) {
        appendLine(buff);
    }
}

QPoint & Document::editorScrollPos(Editor * editor) {
    if (!scroll_pos.contains(editor)) {
        scroll_pos[editor] = QPoint(0, 0);
    }

    return scroll_pos[editor];
}

Document::Document(File * file, QObject * parent) : QObject(parent), _root(nullptr), _last(nullptr), _inline_pos(0), _max_line_length(0), _lines_count(0), _file(file) {
    _last = _root = new TextBlock(QByteArray(), nullptr);

    if (file) {
        openFile();
    }

    appendLine(QByteArray());
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
    IBlock * it = _last -> _prev;

    while(it != _root) {
        curr_it = it;
        it = it -> _prev;
        delete curr_it;
    }

    if (_root -> _next != _last) {
        _last -> _prev = _root;
        _root -> _next = _last;
    }

    _inline_pos = 0;
}

void Document::highlight(QRegularExpression * reg_exp, const bool & scroll) {

}

void Document::insertLine(IBlock * after, const QByteArray & line) {
    _last = new TextBlock(line, after);
    quint64 line_len = quint64(line.length());

    if (line_len > _max_line_length)
        _max_line_length = line_len;

    ++_lines_count;
}

void Document::appendLine(const QByteArray & line) {
    insertLine(_last, line);
}
