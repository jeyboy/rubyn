#include "custom_editor.h"

#include <qpainter.h>
#include <qevent.h>
#include <qstyleoption.h>
#include <qscrollbar.h>
#include <qlayout.h>

#include "custom_document.h"
#include "custom_draw_context.h"
#include "project/file.h"

using namespace Custom;

void Editor::drawDocument(QPainter & painter) {
    if (!_document) return;

    painter.setPen(content_section_pal -> color(QPalette::Foreground));
    _context -> prepare(&painter, size(), QPointF(-hscroll -> value() + qint32(_left_margin), 0));

    qDebug() << "-------------------------------";

//    recalcTopBlock();
    initTopBlock();
    IBlock * it = _top_block;
    int c = 0;
    quint32 block_num = _top_block_number;

    QRectF block_nums_rect = QRectF(0, 0, qint32(_left_margin), _context -> _screen_size.height());

    painter.fillRect(block_nums_rect, line_num_section_pal -> background());
    painter.setClipRect(block_nums_rect);

    while(it) {
        _context -> _pos.ry() += _context -> __line_height;

        it -> draw(_context);
        ++c;

        painter.save();

        painter.setClipping(false);
        painter.setPen(line_num_section_pal -> color(QPalette::Foreground));
        painter.drawText(0, _context -> _pos.y(), QString::number(++block_num));

        painter.restore();

        if (_context -> screenCovered())
            break;

        it = it -> next();
    }

    qDebug() << c;
    _context -> _painter = nullptr;
}

void Editor::recalcScrolls() {
    qint32 vmax = _document ? qint32(_document -> _lines_count * _context -> __line_height) - _context -> _screen_size.height() : -1;
    qint32 hmax = _document ? qint32((_document -> _max_line_length * _context -> __symbol_width + _left_margin) - _context -> _screen_size.width()) : -1;

    vscroll -> setRange(0, vmax);
    hscroll -> setRange(0, hmax);
}

void Editor::initTopBlock() {
    IBlock * it = _document ? _document -> first() : nullptr;

    qint32 top_val = vscroll -> value();

    if (top_val > 0) {
        qint32 block_top = 0;
        qint32 next_top = block_top;

        while(it) {
            next_top += _context -> __line_height;

            if (next_top > top_val)
                break;

            block_top = next_top;
            it = it -> next();
        }

        if (it) {
            _top_block_offset = block_top - _context -> __line_height;
            _top_block = it -> prev();
        }
    }
}

void Editor::recalcTopBlock() {
    if (!_top_block)
        return;

    IBlock * it = _top_block;
    qint32 top_val = vscroll -> value();

    if (top_val > 0) {
        qint32 block_top = _top_block_offset;

        while(it && block_top < top_val) {
            block_top += _context -> __line_height;
            it = it -> next();
        }

        if (it && block_top > top_val) {
            _top_block_offset = block_top - _context -> __line_height;
            _top_block = it -> prev();
        }
    }
}

void Editor::intialize() {
    _context = new DrawContext(nullptr, size(), font());

    line_num_section_pal = new QPalette();
    line_num_section_pal -> setColor(QPalette::Background, Qt::black);
    line_num_section_pal -> setColor(QPalette::Foreground, Qt::white);

    content_section_pal = new QPalette();
    content_section_pal -> setColor(QPalette::Background, Qt::white);
    content_section_pal -> setColor(QPalette::Foreground, Qt::black);

    setAutoFillBackground(true);
    setPalette(*content_section_pal);

    setLeftMargin();

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

Editor::Editor(QWidget * parent) : QWidget(parent), _select_block(nullptr), _top_block(nullptr), _left_margin(0), _document(nullptr), _context(nullptr), vscroll(nullptr), hscroll(nullptr) {
    intialize();
    setDocument(nullptr);
}

Editor::~Editor() {
    delete _document;

    delete line_num_section_pal;
    delete content_section_pal;

    delete _context;
}

QScrollBar * Editor::verticalScrollBar() { return vscroll; }

void Editor::setColor(const QPalette::ColorRole & acr, const QColor & acolor) {
    QPalette pal(palette());
    pal.setColor(acr, acolor);
    setAutoFillBackground(true);
    setPalette(pal);
}

void Editor::setVisible(bool visible) {
    QWidget::setVisible(visible);
}

void Editor::setDocument(Document * doc) {
    _document = doc;
    _select_block = nullptr;
    _top_block_offset = 0;
    _top_block_number = 0;

    if (doc) {
        _top_block = doc -> _root -> next();
        _left_margin = _context -> calcNumWidth(doc -> linesCount());
    } else {
        _top_block = doc ? doc -> first() : nullptr;
        _left_margin = _context -> calcNumWidth(1);
    }

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

            for(uint i = 0; i < vscroll_factor - 1; i++) {
                IBlock * next = _top_block -> next();

                if (!next)
                    break;

                _top_block = next;
            }
        } else {
            for(uint i = 0; i <= vscroll_factor; i++) {
                IBlock * prev = _top_block -> prev();

                if (!prev || prev == _document -> _root)
                    break;

                _top_block = prev;
            }
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
