#include "custom_editor.h"

#include <qpainter.h>
#include <qevent.h>
#include <qscrollarea.h>
#include <qstyleoption.h>

#include "custom_document.h"
#include "project/file.h"

using namespace Custom;

void Editor::intialize() {
    setStyleSheet("background-color: #ffffff;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    _viewport = new QScrollArea(this);
    _viewport -> setWidgetResizable(true);
    _viewport -> setStyleSheet("background-color: #ff0000;");
}

Editor::Editor(QWidget * parent) : QWidget(parent), _viewport(nullptr), _document(nullptr) {
    intialize();
}

Editor::~Editor() {
    delete _document;
}

void Editor::setDocument(Document * doc) {
    _document = doc;
}

QScrollBar * Editor::verticalScrollBar() { return nullptr; }

void Editor::setVisible(bool visible) {
    QWidget::setVisible(visible);
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
//    QWidget::paintEvent(e);

    QPainter painter(this);

    QStyleOption opt;
    opt.init(this);
    style() -> drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    painter.setPen(QColor(0,0,0));

    painter.drawText(0, 10, "HUDO");
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
