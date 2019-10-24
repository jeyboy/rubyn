#include "custom_editor.h"

#include <qpainter.h>
#include <qevent.h>
#include <qscrollarea.h>

#include "custom_document.h"
#include "project/file.h"

using namespace Custom;

void Editor::intialize() {
    _viewport = new QScrollArea(this);
    this -> setBackgroundRole(QPalette::Button);
}

Editor::Editor(QWidget * parent) : QWidget(parent) {
//    root = new TokenCell(lex_none, 0, 0);
//    last = new TokenCell(lex_end_doc, 0, 0, root);
}

Editor::~Editor() {
    delete _document;
}

void Editor::setDocument(Document * doc) {
    _document = doc;
}

QScrollBar * Editor::verticalScrollBar() { return nullptr; }

void Editor::setVisible(bool visible) {

}

void Editor::openDocument(File * file) {
    if (file)
        _document = file -> asCustomText();
    else
        _document = nullptr;
}

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


bool Editor::event(QEvent * e) {
    return QWidget::event(e);
}
void Editor::paintEvent(QPaintEvent * e) {
    QPainter painter(_viewport);
    painter . drawText(0, 0, "HUDO");
}
void Editor::resizeEvent(QResizeEvent * e) {
    QWidget::resizeEvent(e);
}
void Editor::keyPressEvent(QKeyEvent * e) {
    QWidget::keyPressEvent(e);
}
void Editor::keyReleaseEvent(QKeyEvent * e) {
    QWidget::keyReleaseEvent(e);
}
void Editor::wheelEvent(QWheelEvent * e) {
    QWidget::wheelEvent(e);
}
void Editor::focusInEvent(QFocusEvent * e) {
    QWidget::focusInEvent(e);
}
