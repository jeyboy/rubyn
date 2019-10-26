#include "custom_editor.h"

#include <qpainter.h>
#include <qevent.h>
#include <qstyleoption.h>
#include <qapplication.h>

#include <qscrollbar.h>

#include <qscrollarea.h>
#include <qlayout.h>
#include <qlabel.h>

#include "custom_document.h"
#include "custom_draw_context.h"
#include "project/file.h"

using namespace Custom;

void Editor::drawDocument(QPainter & painter) {
    if (!_document) return;

    _context -> prepare(&painter, size(), QPointF(-hscroll -> value(), 0));
    qint32 top_val = vscroll -> value();


//    IBlock * it = _curr_block;


    IBlock * it = _document ? _document -> _root : nullptr;

    if (top_val > 0) {
        qint32 block_top = 0;

        while(it && block_top < top_val) {
            block_top += _context -> __line_height;
            it = it -> next();
        }

        if (it && block_top > top_val) {
            it = it -> prev();
        }
    }


    while(it) {
        it -> draw(_context);

        if (_context -> screenCovered())
            break;

        it = it -> next();
    }

    _context -> _painter = nullptr;
}

void Editor::recalcScrolls() {
    qint32 vmax = _document ? qint32(_document -> _lines_count * _context -> __line_height) - _context -> _screen_size.height() : -1;
    qint32 hmax = _document ? qint32(_document -> _max_line_length * _context -> __symbol_width - _context -> _screen_size.width()) : -1;

    vscroll -> setRange(0, vmax);
    hscroll -> setRange(0, hmax);
}

void Editor::intialize() {
//    QVBoxLayout * l = new QVBoxLayout(this);

//    _viewport = new QWidget(this);
//    _viewport -> setStyleSheet("background-color: #ffffff;");
//    _viewport -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    _scrollarea = new QScrollArea(this);
//    _scrollarea -> setWidget(_viewport);
//    _scrollarea -> setWidgetResizable(true);
//    _scrollarea -> setStyleSheet("background-color: #ff0000;");

//    l -> addWidget(_scrollarea);
//    l -> setContentsMargins(0,0,0,0);


    _context = new DrawContext(nullptr, size(), font());


    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

//    setStyleSheet("background-color: #ffffff;");

    vscroll = new QScrollBar(Qt::Vertical, this);
    vscroll -> setStyleSheet(
        QString(
             "QScrollBar:vertical {"
               "border-color: rgb(227, 227, 227);"
               "border-width: 1px;"
               "border-style: solid;"
               "background-color: rgb(240, 240, 240);"
               "width: 15px;"
               "margin: 1px 0 1px 0;"
             "}"
             "QScrollBar::handle:vertical {"
               "background-color: rgb(200, 200, 200);"
               "min-height: 25px;"
             "}"
              "QScrollBar::add-line:vertical {"
                 "border: 1px solid grey;"
                 "background-color: rgb(241, 241, 241);"
             "}"
             "QScrollBar::sub-line:vertical {"
                 "border: 1px solid grey;"
                 "background-color: rgb(241, 241, 241);"
             "}"
               "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                   "background: none;"
               "}"
                "QScrollBar::up-arrow:vertical {"
                    "height: 0px;"
//                    "image: url(:/BarIcon/Icons/uparrow.png);"
                "}"
                "QScrollBar::down-arrow:vertical {"
                    "height: 0px;"
//                  "image: url(:/BarIcon/Icons/downarrow.png);"
                "}"
    ));


    hscroll = new QScrollBar(Qt::Horizontal, this);
    hscroll -> setStyleSheet(
        QString(
            "QScrollBar:horizontal {"
              "border-color: rgb(227, 227, 227);"
              "border-width: 1px;"
              "border-style: solid;"
              "background-color: rgb(240, 240, 240);"
                "height: 15px;"
                "margin: 0px 1px 0 1px;"
             "}"
             "QScrollBar::handle:horizontal {"
                "background-color: rgb(200, 200, 200);"
                "min-width: 25px;"
             "}"
            "QScrollBar::add-line:horizontal {"
                "border: 1px solid grey;"
              "background-color: rgb(241, 241, 241);"
                "height: 20px;"
                "subcontrol-position: right;"
                "subcontrol-origin: margin;"
             "}"
             "QScrollBar::sub-line:horizontal {"
              "border: 1px solid grey;"
                "background-color: rgb(241, 241, 241);"
                "height: 20px;"
                "subcontrol-position: left;"
                "subcontrol-origin: margin;"
             "}"
            "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
                 "background: none;"
            "}"
                     "QScrollBar:left-arrow:horizontal {"
                        "height: 3px;"
                        "width: 3px;"
                      "image: url(:/BarIcon/Icons/leftarrow.png);"
                    "}"
                    "QScrollBar::right-arrow:horizontal {"
            "height: 3px;"
            "width: 3px;"
                      "image: url(:/BarIcon/Icons/rightarrow.png);"
                    "}"
        )
    );

    vscroll -> setRange(-1, -1);
    hscroll -> setRange(-1, -1);

    setVerticalScrollFactor();
    setHorizontalScrollFactor();

    connect(hscroll, &QScrollBar::valueChanged, [=]() { emit update(); });
    connect(hscroll, &QScrollBar::rangeChanged, [=]() { emit update(); });

    connect(vscroll, &QScrollBar::valueChanged, [=]() { emit update(); });
    connect(vscroll, &QScrollBar::rangeChanged, [=]() { emit update(); });

    QVBoxLayout * l = new QVBoxLayout(this);
    l -> setContentsMargins(0,0,0,0);
    l -> setSpacing(0);

    l -> addWidget(vscroll, 1, Qt::AlignRight);
    l -> addWidget(hscroll, 0, Qt::AlignBottom);
}

Editor::Editor(QWidget * parent) : QWidget(parent),/* _scrollarea(nullptr), _viewport(nullptr),*/ _curr_block(nullptr), _document(nullptr), _context(nullptr), vscroll(nullptr), hscroll(nullptr) {
    intialize();
}

Editor::~Editor() {
    delete _document;
}

QScrollBar * Editor::verticalScrollBar() { return vscroll; }

void Editor::setVerticalScrollFactor(uint factor) {
    vscroll_factor = factor;
}
void Editor::setHorizontalScrollFactor(uint factor) {
    hscroll_factor = factor;
}

void Editor::setVisible(bool visible) {
    QWidget::setVisible(visible);
}

void Editor::setDocument(Document * doc) {
    _document = doc;
    _curr_block = doc ? doc -> _root -> next() : nullptr;
    recalcScrolls();
}

void Editor::openDocument(File * file) {
    setDocument(file ? file -> asCustomText() : nullptr);
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

    if (_document) {
        drawDocument(painter);
    }
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

    if (e -> orientation() == Qt::Vertical) {
        qreal offset = -_context -> __line_height * vscroll_factor;

        if (e -> delta() < 0) {
            offset = -offset;
        }

        vscroll -> setValue(vscroll -> value() + qint32(offset));
    } else {
        qreal offset = -_context -> __symbol_width * hscroll_factor;

        if (e -> delta() < 0) {
            offset = -offset;
        }

        hscroll -> setValue(vscroll -> value() + qint32(offset));
    }
}
void Editor::focusInEvent(QFocusEvent * e) {
    QWidget::focusInEvent(e);
}
