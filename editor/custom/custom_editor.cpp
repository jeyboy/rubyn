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
    painter.setFont(_context -> _font);
    _context -> setRightMargin(vscroll -> isVisible() ? vscroll -> width() + 3 : 0);
    _context -> prepare(&painter, size(), QPointF(-hscroll -> value(), 0));

    qDebug() << "-------------------------------";

    initTopBlock(true);
    IBlock * it = _top_block;
    int c = 0;
    quint32 block_num = _top_block_number;
    painter.fillRect(_context -> numbersAreaRect(), line_num_section_pal -> background());
    painter.setClipRect(_context -> contentAreaRect());

    while(it) {
        _context -> _pos.ry() += _context -> __line_height;
        it -> draw(_context);
        ++c;

        painter.save();

        painter.setClipping(false);
        painter.setPen(line_num_section_pal -> color(QPalette::Foreground));
        painter.drawText(0, qint32(_context -> _pos.y()), QString::number(++block_num));
        painter.setClipping(true);

        painter.restore();

        if (_context -> screenCovered())
            break;

        it = it -> next();
    }

    qDebug() << c;
    _context -> _painter = nullptr;
}

void Editor::recalcScrolls() {
    qint32 vmax = _document ? qint32(_document -> _lines_count * _context -> __line_height)/* - _context -> _screen_size.height()*/ : -1;
    qint32 hmax = _document ? qint32((_document -> _max_line_length * _context -> __symbol_width + _context -> _left_margin) - size().width()) : -1;

    qDebug() << "hmax" << hmax << (_document ? _document -> _max_line_length : 0);

    vscroll -> setRange(0, vmax);
    hscroll -> setRange(0, hmax);
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
            next_top += _context -> __line_height;

            if (next_top > scroll_offset)
                break;

            block_top = next_top;
            ++number_offset;
            it = it -> next();
        }

        if (!it)
            it = _document -> last();
    } else {
        while(it != _document -> _root) {
            next_top -= _context -> __line_height;

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
    hscroll = new QScrollBar(Qt::Horizontal, this);

    vscroll -> setRange(-1, -1);
//    vscroll -> setPageStep(_context -> __line_height);
    vscroll -> setSingleStep(_context -> __line_height);
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
}

Editor::Editor(QWidget * parent) : QWidget(parent), _select_block(nullptr), _top_block(nullptr), _document(nullptr), _context(nullptr), vscroll(nullptr), hscroll(nullptr) {
    intialize();
    openDocument();
}

Editor::~Editor() {
    delete _document;

    delete line_num_section_pal;
    delete content_section_pal;

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
        setLeftMargin(_context -> calcNumWidth(doc -> linesCount()));
        scroll_pos = doc -> editorScrollPos(this);
    } else {
        _top_block = nullptr;
        setLeftMargin(_context -> calcNumWidth(1));
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
        qint32 offset = -_context -> __line_height * vscroll_factor;

        if (e -> delta() < 0) {
            offset = -offset;
        }

        vscroll -> setValue(vscroll -> value() + qint32(offset));
    } else {
        qint32 offset = -_context -> __symbol_width * hscroll_factor;

        if (e -> delta() < 0) {
            offset = -offset;
        }

        hscroll -> setValue(vscroll -> value() + qint32(offset));
    }
}
void Editor::focusInEvent(QFocusEvent * e) {
    QWidget::focusInEvent(e);
}
