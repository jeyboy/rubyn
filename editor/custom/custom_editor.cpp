#include "custom_editor.h"

#include <qpainter.h>
#include <qevent.h>
#include <qscrollarea.h>

using namespace Custom;

void Editor::intialize() {
    _viewport = new QScrollArea(this);
    this -> setBackgroundRole(QPalette::Button);
}

Editor::Editor(QWidget * parent) : QWidget(parent), _root(nullptr), _last(nullptr) {
//    root = new TokenCell(lex_none, 0, 0);
//    last = new TokenCell(lex_end_doc, 0, 0, root);
}

Editor::~Editor() {
    clear();

    delete _root;
    delete _last;
}

void Editor::setDocument(Document * doc) {
    _document = doc;
}

void Editor::clear() {
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

QScrollBar * Editor::verticalScrollBar() { return nullptr; }

void Editor::setVisible(bool visible) {

}

void Editor::openDocument(File * file) {}

//  void Editor::searchIsShow(const bool & show) = 0;
void Editor::searchInitiated(const QRegularExpression & pattern, const bool & scroll) {

}
void Editor::searchNextResult(QString * replace) {

}
void Editor::searchPrevResult(QString * replace) {

}
void Editor::searchRepaceAll(const QString & replace) {

}
void Editor::searchClosed() {

}


bool Editor::event(QEvent * event) {

}
void Editor::paintEvent(QPaintEvent * e) {
    QPainter painter(_viewport);
    painter . drawText(0, 0, "HUDO");
}
void Editor::resizeEvent(QResizeEvent * e) {

}
void Editor::keyPressEvent(QKeyEvent * e) {

}
void Editor::keyReleaseEvent(QKeyEvent * e) {

}
void Editor::wheelEvent(QWheelEvent * e) {

}
void Editor::focusInEvent(QFocusEvent * e) {

}
