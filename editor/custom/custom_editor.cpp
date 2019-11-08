#include "custom_editor.h"

#include <qpainter.h>
#include <qevent.h>
#include <qstyleoption.h>
#include <qscrollbar.h>
#include <qlayout.h>

#include "custom_document.h"
#include "custom_draw_context.h"
#include "project/file.h"
#include "controls/logger.h"

using namespace Custom;

void Editor::drawDocument(QPainter & painter) {
    if (!_document) return;

    initTopBlock(true);

    Logger::obj().startMark();
    _context -> draw(&painter, size(), _top_block, _top_block_number);
    Logger::obj() .endMark(false, "drawDocument");
    _context -> _painter = nullptr;
}

void Editor::recalcScrolls() {
    qint32 vmax = _document ? _context -> calcVScrollWidth(_document -> _lines_count) : -1;
    qint32 hmax = _document ? _context -> calcHScrollWidth(_document -> _max_line_length) : -1;

    //    vscroll -> setPageStep(_context -> __line_height);
    vscroll -> setSingleStep(_context -> verticalSingleStep());
    hscroll -> setSingleStep(_context -> horizontalSingleStep());


    vscroll -> setVisible(vmax > 0);
    if (vmax > 0) {
        vscroll -> setRange(0, vmax);
    } else {
        vscroll -> setValue(0);
    }


    hscroll -> setVisible(hmax > 0);
    if (hmax > 0) {
        hscroll -> setRange(0, hmax);
    } else {
        hscroll -> setValue(0);
    }
}

void Editor::initTopBlock(const bool & recalc) {
    IBlock * it;

    if (recalc) {
        it = _top_block;
    } else {
        it = _document ? _document -> first() : nullptr;
    }

    qreal scroll_offset = vscroll -> value();

    if (scroll_offset <= 0) {
        _top_block = _document ? _document -> first() : nullptr;
        _top_block_number = 0;
        _top_block_offset = 0;
        return;
    }

    qint32 number_offset = 0;
    qreal block_top = _top_block_offset;
    qreal next_top = block_top;

    if (_top_block_offset < scroll_offset) {
        while(it) {
            next_top += 1;//_context -> __line_height;

            if (next_top > scroll_offset)
                break;

            block_top = next_top;
            ++number_offset;
            it = it -> next();
        }

        if (!it) {
            it = _document -> last();
            --number_offset;
        }
    } else {
        while(it != _document -> _root) {
            next_top -= 1;//_context -> __line_height;

            if (next_top < scroll_offset)
                break;

            block_top = next_top;
            --number_offset;
            it = it -> prev();
        }
    }


    _top_block_offset = block_top;
    _top_block_number += number_offset;
    _top_block = it;
}

void Editor::intialize() {
    _context = new DrawContext(nullptr, size(), font());

    QPalette * line_num_section_pal = new QPalette();
    line_num_section_pal -> setColor(QPalette::Background, Qt::black);
    line_num_section_pal -> setColor(QPalette::Foreground, Qt::white);

    QPalette * content_section_pal = new QPalette();
    content_section_pal -> setColor(QPalette::Background, Qt::white);
    content_section_pal -> setColor(QPalette::Foreground, Qt::black);

    _context -> setPaletes(line_num_section_pal, content_section_pal);

    setAutoFillBackground(true);
    setPalette(*content_section_pal);
    setLeftMargin();

    vscroll = new QScrollBar(Qt::Vertical, this);
    hscroll = new QScrollBar(Qt::Horizontal, this);

    vscroll -> setRange(-1, -1);
    hscroll -> setRange(-1, -1);

    setVerticalScrollFactor();
    setHorizontalScrollFactor();

    connect(hscroll, &QScrollBar::valueChanged, [=]() {
        if (_document) {
            _document -> editorScrollPos(this).rx() = hscroll -> value();
        }

        emit update();
    });
    connect(hscroll, &QScrollBar::rangeChanged, [=]() { emit update(); });

    connect(vscroll, &QScrollBar::valueChanged, [=]() {
        if (_document) {
            _document -> editorScrollPos(this).ry() = vscroll -> value();
        }
        emit update();
    });
    connect(vscroll, &QScrollBar::rangeChanged, [=]() { emit update(); });

    QVBoxLayout * l = new QVBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    l -> setSpacing(0);

    l -> addWidget(vscroll, 1, Qt::AlignRight);
    l -> addWidget(hscroll, 0, Qt::AlignBottom);

    _context -> setScrolls(hscroll, vscroll);
}

Editor::Editor(QWidget * parent) : QWidget(parent), _select_block(nullptr), _top_block(nullptr), _document(nullptr), _context(nullptr), vscroll(nullptr), hscroll(nullptr) {
    intialize();
    openDocument();
}

Editor::~Editor() {
    delete _document;

    delete _context;
}

QScrollBar * Editor::verticalScrollBar() { return vscroll; }

void Editor::setLeftMargin(const qint32 & margin) { _context -> setLeftMargin(margin); }

//void Editor::setColor(const QPalette::ColorRole & acr, const QColor & acolor) {
//    QPalette pal(palette());
//    pal.setColor(acr, acolor);
//    setAutoFillBackground(true);
//    setPalette(pal);
//}

void Editor::setVisible(bool visible) {
    QWidget::setVisible(visible);
}

void Editor::openDocument(Document * doc) {
    qDebug() << this << "setDocument";

    _context -> setFont(font());
//    _context -> _screen_size = size();

    _document = doc;
    _select_block = nullptr;
    _top_block_offset = 0;
    _top_block_number = 0;
    QPoint scroll_pos(0, 0);

    if (doc) {
        _top_block = doc -> first();
        setLeftMargin(_context -> calcNumWidth(doc -> linesCount()) + 3);

        if (doc -> verticalScrollPos(false) > 0) {
            doc -> editorScrollPos(this).ry() = doc -> verticalScrollPos(true);
        }

        scroll_pos = doc -> editorScrollPos(this);
    } else {
        _top_block = nullptr;
        setLeftMargin(_context -> calcNumWidth(1) + 3);
    }

    recalcScrolls();

    hscroll -> setValue(scroll_pos.x());
    vscroll -> setValue(scroll_pos.y());

    initTopBlock();
}

void Editor::openDocument(File * file) {
    openDocument(file ? file -> asCustomText() : nullptr);
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

    _context -> prepare(nullptr, size());
    recalcScrolls();
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
        qint32 offset = -1/*_context -> __line_height*/ * vscroll_factor;

        if (e -> delta() < 0) {
            offset = -offset;
        }

        vscroll -> setValue(vscroll -> value() + qint32(offset));
    } else {
        qint32 offset = -1/*_context -> __symbol_width*/ * hscroll_factor;

        if (e -> delta() < 0) {
            offset = -offset;
        }

        hscroll -> setValue(vscroll -> value() + qint32(offset));
    }
}
void Editor::focusInEvent(QFocusEvent * e) {
    QWidget::focusInEvent(e);
}
