#include "custom_editor.h"

#include <qpainter.h>
#include <qevent.h>
#include <qstyleoption.h>
#include <qscrollbar.h>
#include <qlayout.h>
#include <qtimer.h>

#include "custom_document.h"
#include "custom_draw_context.h"
#include "project/file.h"

#include "controls/logger.h"
#include "controls/completer.h"

using namespace Custom;

void Editor::blickCursor() {
    _back_timer -> stop();
    _context -> _show_cursors = true;
    _back_timer -> start(500);
}

void Editor::nonBlickCursor() {
    if (_back_timer -> isActive() || !_context -> _show_cursors) {
        _back_timer -> stop();
        _context -> _show_cursors = true;
    }
}

void Editor::drawDocument(QPainter & painter) {
    if (!_document) return;

    _context -> initTopBlock(_document, true);

    Logger::obj().startMark();
    _context -> draw(&painter, size());
    Logger::obj() .endMark(false, "drawDocument");

    _context -> _painter = nullptr;
}

void Editor::recalcScrolls() {
    qint32 vmax = _document ? _context -> calcVScrollWidth(_document -> _lines_count) : -1;
    qint32 hmax = _document ? _context -> calcHScrollWidth(_document -> _max_line_length) : -1;

    //    vscroll -> setPageStep(_context -> __line_height);
    _vscroll -> setSingleStep(_context -> verticalSingleStep());
    _hscroll -> setSingleStep(_context -> horizontalSingleStep());


    _vscroll -> setVisible(vmax > 0);
    if (vmax > 0) {
        _vscroll -> setRange(0, vmax);
    } else {
        _vscroll -> setValue(0);
    }


    _hscroll -> setVisible(hmax > 0);
    if (hmax > 0) {
        _hscroll -> setRange(0, hmax);
    } else {
        _hscroll -> setValue(0);
    }
}

void Editor::ensureVisibleCurrentBlock(const qint64 & char_in_line) {
    bool update_requires = false;

    if (_vscroll -> value() == _context -> _top_block_offset) {
        update_requires = true;
    } else {
        _vscroll -> setValue(_context -> _top_block_offset);
    }

    if (_hscroll -> value() == char_in_line) {
        update_requires = true;
    } else {
        _hscroll -> setValue(char_in_line);
    }

    if (update_requires) {
        update();
    }
}

void Editor::intialize() {
    setFocusPolicy(Qt::StrongFocus);

    _context = new DrawContext(nullptr, size(), font());

    QPalette * line_num_section_pal = new QPalette();
    line_num_section_pal -> setColor(QPalette::Background, Qt::black);
    line_num_section_pal -> setColor(QPalette::Foreground, Qt::white);

    QPalette * content_section_pal = new QPalette();
    content_section_pal -> setColor(QPalette::Background, Qt::white);
    content_section_pal -> setColor(QPalette::Foreground, Qt::black);

    _context -> setPalettes(line_num_section_pal, content_section_pal);

    setAutoFillBackground(true);
    setPalette(*content_section_pal);
    setLeftMargin(10);

    _vscroll = new QScrollBar(Qt::Vertical, this);
    _hscroll = new QScrollBar(Qt::Horizontal, this);

    _vscroll -> setRange(-1, -1);
    _hscroll -> setRange(-1, -1);

    setVerticalScrollFactor();
    setHorizontalScrollFactor();

    connect(_hscroll, &QScrollBar::valueChanged, [=]() {
        if (_document) {
            _document -> editorScrollPos(this).rx() = _hscroll -> value();
        }

        emit update();
    });
    connect(_hscroll, &QScrollBar::rangeChanged, [=]() { emit update(); });

    connect(_vscroll, &QScrollBar::valueChanged, [=]() {
        if (_document) {
            _document -> editorScrollPos(this).ry() = _vscroll -> value();
        }
        emit update();
    });
    connect(_vscroll, &QScrollBar::rangeChanged, [=]() { emit update(); });

    QVBoxLayout * l = new QVBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    l -> setSpacing(0);

    l -> addWidget(_vscroll, 1, Qt::AlignRight);
    l -> addWidget(_hscroll, 0, Qt::AlignBottom);

    _context -> setScrolls(_hscroll, _vscroll);
    _context -> setSearcher(&searcher);
    _context -> _cursors.append(Cursor(_document));

    _back_timer = new QTimer(this);
    connect(_back_timer, &QTimer::timeout, [=]() {
        _context -> _show_cursors = !_context -> _show_cursors;
        QRectF r(_context -> _cursors[0].rect());

        r.adjust(-_context -> __letter_with_pad_width, -1, _context -> __letter_with_pad_width, 2);

        emit update(r.toRect());
    });
}

Editor::Editor(QWidget * parent) : QWidget(parent), _back_timer(nullptr), _completer(nullptr), _document(nullptr), _context(nullptr), _vscroll(nullptr), _hscroll(nullptr) {
    intialize();
    openDocument();
}

Editor::~Editor() {
    delete _document;

    delete _context;
}

void Editor::ensureVisibleBlock(const qint64 & block_num, const qint64 & char_in_line) {
    ensureVisible(block_num);

    ensureVisibleCurrentBlock(char_in_line);
}

void Editor::ensureVisibleBlock(IBlock * block, const qint64 & char_in_line) {
    ensureVisible(block);

    ensureVisibleCurrentBlock(char_in_line);
}

QScrollBar * Editor::verticalScrollBar() { return _vscroll; }

void Editor::setVerticalScrollFactor(uint factor) {
    _context -> _vscroll_factor = factor;
}
void Editor::setHorizontalScrollFactor(uint factor) {
    _context -> _hscroll_factor = factor;
}

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

bool Editor::blockIsVisible(IBlock * block) {
    return _context -> _on_screen.contains(block);
}

void Editor::ensureVisible(IBlock * block) {
    _context -> initTopBlock(_document, block);
}

void Editor::ensureVisible(const qint64 & block_num) {
    _context -> initTopBlock(_document, block_num);
}


void Editor::openDocument(Document * doc) {
    qDebug() << this << "setDocument";

    _context -> setFont(font());
//    _context -> _screen_size = size();

    _document = doc;
    _context -> _select_block = nullptr;
    _context -> _top_block_offset = 0;
    _context -> _top_block_number = 0;
    QPoint scroll_pos(0, 0);

    if (doc) {
        _context -> _top_block = doc -> first();
        setLeftMargin(_context -> calcNumWidth(doc -> linesCount()) + 3);

        if (doc -> verticalScrollPos(false) > 0) {
            doc -> editorScrollPos(this).ry() = doc -> verticalScrollPos(true);
        }

        scroll_pos = doc -> editorScrollPos(this);
    } else {
        _context -> _top_block = nullptr;
        setLeftMargin(_context -> calcNumWidth(1) + 3);
    }

    recalcScrolls();

    _hscroll -> setValue(scroll_pos.x());
    _vscroll -> setValue(scroll_pos.y());

    _context -> initTopBlock(_document);
}

void Editor::openDocument(File * file) {
    openDocument(file ? file -> asCustomText() : nullptr);
}

void Editor::setCompleter(Completer * new_completer) {
    if (_completer)
        disconnect(_completer, nullptr, this, nullptr);

    _completer = new_completer;

    if (!_completer)
        return;

    _completer -> setWidget(this);
    _completer -> setCompletionMode(QCompleter::PopupCompletion);
    _completer -> setCaseSensitivity(Qt::CaseInsensitive);

    connect(_completer, SIGNAL(activated(QString)), this, SLOT(applyCompletion(QString)));
}

void Editor::setTextCursorWidth(const qreal & new_width) {
    if (_context -> _cursor_width == new_width)
        return;

    _context -> setCursorWidth(new_width);
    update();
}

void Editor::setTextCursor(const Cursor & cursor) { _context -> _cursors[0] = cursor; }
Cursor & Editor::textCursor() { return _context -> _cursors[0]; }
Cursor Editor::textCursorForPos(const QPointF & pos) {
    QHash<IBlock *, LineAttrs>::Iterator it = _context -> _on_screen.begin();
    QHash<IBlock *, LineAttrs>::Iterator target = _context -> _on_screen.end();

    IBlock * active_block = nullptr;

    for(; it != target; it++) {
        if (pos.y() >= it.value().rect.top() && pos.y() <= it.value().rect.bottom()) {
            active_block = it.key();
            break;
        }
    }

    if (active_block) {
        return Cursor(_document, active_block, _context -> mouseXToCharPos(pos.x()));
    }

    return Cursor(_document);
}

//  void Editor::searchIsShow(const bool & show) = 0;
void Editor::searchInitiated(const QRegularExpression & pattern, const bool & scroll) {
    qDebug() << "Custom::Editor::searchInitiated" << pattern.pattern();

    if (pattern.pattern().isEmpty()) {
        searcher.clearSearch();
        emit searchResultsFinded(0);
    } else {
        searcher.beginSearch(pattern);
        EditorSearcherResult match = searcher.search(_document -> first());

        if (match.isValid()) {
            ensureVisibleBlock(match.block, match.text_part.first);
        }

        emit searchResultsFinded(searcher.foundResultsAmount());
    }
}
void Editor::searchNextResult(QString * replace) {
    qDebug() << "CustomEditor::searchNextResult" << replace;

    if (!searcher.hasResults()) {
        qDebug() << "CustomEditor::searchNextResult" << "NO RESULTS";
        return;
    }

//    QTextCursor cursor = textCursor();
//    bool has_selection = cursor.hasSelection();

//    if (replace && has_selection) {
//        searcher.procSearchReplace(cursor, *replace, false);
//        delete replace;

//        has_selection = false;
//    }

//    EDITOR_POS_TYPE pos = cursor.positionInBlock();
//    bool limited = true;

//    for(QTextBlock block = cursor.block(); block.isValid(); limited = false, block = block.next()) {
//        TextParts & mappings = searcher.searchResultsFor(block);

//        if (mappings.isEmpty())
//            continue;

//        TextParts::ConstIterator index_it = mappings.constBegin();

//        for(; index_it != mappings.constEnd(); index_it++) {
//            if (!limited || (has_selection && (cursor.selectionStart() - block.position()) < (*index_it).first) || (!has_selection && pos < (*index_it).first)) {
//                EDITOR_POS_TYPE block_pos = block.position();

//                cursor.setPosition(block_pos + (*index_it).first, QTextCursor::MoveAnchor);
//                cursor.setPosition(block_pos + (*index_it).first + (*index_it).second, QTextCursor::KeepAnchor);
//                setTextCursor(cursor);

//                return;
//            }
//        }
//    }

//    emit searchResultsFinded(searcher.search_results);
}
void Editor::searchPrevResult(QString * replace) {
    qDebug() << "CustomEditor::searchPrevResult" << replace;

    if (!searcher.hasResults()) {
        qDebug() << "CustomEditor::searchPrevResult" << "NO RESULTS";
        return;
    }

//    QTextCursor cursor = textCursor();
//    bool has_selection = cursor.hasSelection();

//    if (replace && has_selection) {
//        searcher.procSearchReplace(cursor, *replace, true);
//        delete replace;

//        has_selection = false;
//    }

//    EDITOR_POS_TYPE pos = cursor.positionInBlock();
//    bool limited = true;

//    for(QTextBlock block = cursor.block(); block.isValid(); limited = false, block = block.previous()) {
//        TextParts & mappings = searcher.searchResultsFor(block);

//        if (mappings.isEmpty())
//            continue;

//        TextParts::const_reverse_iterator index_it = mappings.rbegin();

//        for(; index_it != mappings.rend(); index_it++) {
//            if (!limited || (has_selection && (cursor.selectionStart() - block.position()) > (*index_it).first) || (!has_selection && pos > (*index_it).first)) {
//                EDITOR_POS_TYPE block_pos = block.position();

//                cursor.setPosition(block_pos + (*index_it).first, QTextCursor::MoveAnchor);
//                cursor.setPosition(block_pos + (*index_it).first + (*index_it).second, QTextCursor::KeepAnchor);
//                setTextCursor(cursor);

//                return;
//            }
//        }
//    }

//    emit searchResultsFinded(searcher.search_results);
}
void Editor::searchRepaceAll(const QString & replace) {
    qDebug() << "CustomEditor::searchRepaceAll" << replace;

    if (!searcher.hasResults()) {
        qDebug() << "CustomEditor::searchRepaceAll" << "NO RESULTS";
        return;
    }

//    QTextCursor cursor = textCursor();

////    EDITOR_POS_TYPE block_num = cursor.blockNumber();
////    EDITOR_POS_TYPE pos = cursor.positionInBlock();

//    cursor.beginEditBlock();

//    for( QTextBlock block = wrapper -> lastBlock(); block.isValid(); block = block.previous()) {
//        TextParts & mappings = searcher.searchResultsFor(block);

//        if (mappings.isEmpty())
//            continue;

//        TextParts::const_reverse_iterator index_it = mappings.rbegin();
//        EDITOR_POS_TYPE block_pos = block.position();

//        for(; index_it != mappings.rend(); index_it++) {
//            cursor.setPosition(block_pos + (*index_it).first, QTextCursor::MoveAnchor);
//            cursor.setPosition(block_pos + (*index_it).first + (*index_it).second, QTextCursor::KeepAnchor);
//            cursor.insertText(replace);
//        }
//    }

//    cursor.endEditBlock();

//    emit searchResultsFinded(searcher.search_results);
}
void Editor::searchClosed() {
    searcher.closeSearch();
    emit searchResultsFinded(0);
    update();
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

    qDebug() << opt.rect;

    if (_document) {
        drawDocument(painter);
    }
}
void Editor::resizeEvent(QResizeEvent * e) {
    QWidget::resizeEvent(e);

    _context -> prepare(nullptr, size());
    recalcScrolls();
}

void Editor::customKeyPressEvent(QKeyEvent * e) {
    int curr_key = e -> key();

    if (!_context -> _has_cursor_on_screen) {
        _context -> ensureVisibleCursor();
    }


    switch (curr_key) {
        case Qt::Key_Delete: {
            nonBlickCursor();
        break;}

        case Qt::Key_Backspace: {
            nonBlickCursor();
        break;}

        case Qt::Key_Return: {
            nonBlickCursor();
        break;}

        case Qt::Key_Tab: {
            nonBlickCursor();
        break;}

        case Qt::Key_Backtab: {
            nonBlickCursor();
        break; }

        case Qt::Key_Right: {
            nonBlickCursor();

            if (_context -> _cursors[0].toNextChar()) {
                Cursor::MoveFlag move_flag = _context -> _cursors[0].moveFlag();

                if (move_flag & Cursor::mf_line_move) {
                    _context -> ensureVisibleCursorAfterMoveDown();
                    _context -> ensureVisibleCursorLineBegin();
                } else {
                    _context -> ensureVisibleCursorAfterMoveRight();
                }

                update();
            }
        break;}

        case Qt::Key_Left: {
            nonBlickCursor();

            if (_context -> _cursors[0].toPrevChar()) {
                Cursor::MoveFlag move_flag = _context -> _cursors[0].moveFlag();

                if (move_flag & Cursor::mf_line_move) {
                    _context -> ensureVisibleCursorAfterMoveUp();
                    _context -> ensureVisibleCursorLineEnd();
                } else {
                    _context -> ensureVisibleCursorAfterMoveLeft();
                }

                update();
            }
        break;}

        case Qt::Key_Up: {
            nonBlickCursor();

            if (_context -> _cursors[0].toPrevLine()) {
                Cursor::MoveFlag move_flag = _context -> _cursors[0].moveFlag();

                _context -> ensureVisibleCursorAfterMoveUp();

                if (move_flag & Cursor::mf_pos_move) {
                    _context -> ensureVisibleCursorLineEnd();
                }

                update();
            }
        break;}

        case Qt::Key_Down: {
            nonBlickCursor();

            if (_context -> _cursors[0].toNextLine()) {
                Cursor::MoveFlag move_flag = _context -> _cursors[0].moveFlag();

                _context -> ensureVisibleCursorAfterMoveDown();

                if (move_flag & Cursor::mf_pos_move) {
                    _context -> ensureVisibleCursorLineEnd();
                }

                update();
            }
        break;}

        case Qt::Key_Home: {
            nonBlickCursor();

            if (e -> modifiers() == Qt::ControlModifier) {
                _context -> _cursors[0].setBlock(_document -> first());
                _context -> ensureVisibleCursorDocBegin();
            } else {
                _context -> _cursors[0].toLineStart();
                _context -> ensureVisibleCursorLineBegin();
            }

            update();
        break;}

        case Qt::Key_End: {
            nonBlickCursor();

            if (e -> modifiers() == Qt::ControlModifier) {
                _context -> _cursors[0].setBlock(_document -> last());
                _context -> _vscroll -> setValue(_document -> linesCount());
            } else {
                _context -> _cursors[0].toLineEnd();
                _context -> ensureVisibleCursorLineEnd();
            }

            update();
        break;}

        case Qt::Key_Escape: // ignore non printable keys
        case Qt::Key_CapsLock:
        case Qt::Key_NumLock:
        case Qt::Key_ScrollLock:
        case Qt::Key_Meta:
        case Qt::Key_Alt:
        case Qt::Key_Shift:
        case Qt::Key_Control: { QWidget::keyPressEvent(e); break;}

        default: {
//            bool is_shortcut = e -> modifiers() == Qt::ControlModifier && curr_key == Qt::Key_Space;

        }
    }

    e -> accept();
}

void Editor::keyPressEvent(QKeyEvent * e) {
    int curr_key = e -> key();

    if (_completer && _completer -> isVisible()) {
        switch (curr_key) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
                e -> ignore();
                return; // let the completer do default behavior
            default: break;
        }
    }

    if (curr_key == Qt::Key_Escape && searcher.isOpened()) {
        qDebug() << "----------------------- JOJ";
        emit searchRequired(false);
        return;
    }


    if (curr_key == Qt::Key_L && e -> modifiers() == Qt::ControlModifier) {
        emit lineChooseModalRequired();
        return;
    }


    if (curr_key == Qt::Key_F && e -> modifiers() == Qt::ControlModifier) { // && !searcher.is_active
        qDebug() << "----------------------- SOS";
//        QTextCursor cursor = textCursor();

//        if (cursor.hasSelection()) {
//            QString str = cursor.selectedText();

//            str.replace(QChar(8233), char(13));

//            emit searchRequestRequired(str);
//        }
//        else emit searchRequired(true);

        emit searchRequired(true);
        return;
    }

    switch (curr_key) {
        case Qt::Key_Delete: {
//            para_info.clear();
            customKeyPressEvent(e);
        return;}

//        case Qt::Key_Backspace: {
//            customKeyPressEvent(e);
//        return;}

        case Qt::Key_Return: {
            customKeyPressEvent(e);

//            QTextCursor cursor = textCursor();
//            int level = TextDocumentLayout::getBlockLevel(cursor.block());

//            if (level > DEFAULT_LEVEL) {
//                const QLatin1String & tab_str = wrapper -> tabSpace();
//                QString str = QString(level * tab_str.size(), tab_str[0].toLatin1());

//                cursor.insertText(str);
//            }
        return;}

        case Qt::Key_Tab: { /*procSelectionIndent();*/ break;}
        case Qt::Key_Backtab: { /*procSelectionIndent(false);*/ break; }


        case Qt::Key_Home: { break;}
        case Qt::Key_End: { break;}

        case Qt::Key_Right:
        case Qt::Key_Left: {
//            QTextCursor cursor = textCursor();
//            QTextBlock blk = cursor.block();
//            int pos_in_block = cursor.positionInBlock();

//            if (curr_key == Qt::Key_Right && pos_in_block == blk.length() - 1) {
//                BlockUserData * udata = TextDocumentLayout::getUserDataForBlock(blk);

//                if (udata && udata -> isFolded()) {
//                    wrapper -> layout -> toggleFolding(blk);
//                }
//            }

            customKeyPressEvent(e);

//            if (curr_key == Qt::Key_Left && pos_in_block == 0) {
//                QTextBlock tail_blk = blk.previous();

//                if (!tail_blk.isVisible()) {
//                    cursor = textCursor();
//                    QTextBlock head_blk = cursor.block().previous();

//                    cursor.setPosition(tail_blk.position() + tail_blk.length() - 1);
//                    setTextCursor(cursor);
//                    wrapper -> layout -> toggleFolding(head_blk);
//                }
//            }

//            if (completer && completer -> isVisible()) {
//                QTextCursor tc = textCursor();
//                procCompleterForCursor(tc, false);
//            }
        return;}

        case Qt::Key_Escape: // ignore non printable keys
        case Qt::Key_CapsLock:
        case Qt::Key_NumLock:
        case Qt::Key_ScrollLock:
        case Qt::Key_Meta:
        case Qt::Key_Alt:
        case Qt::Key_Shift:
        case Qt::Key_Control: { customKeyPressEvent(e); return;}

        default: {
            bool is_shortcut = e -> modifiers() == Qt::ControlModifier && curr_key == Qt::Key_Space;

            if (!_completer || (!_completer -> isVisible() &&
                    (curr_key < Qt::Key_Space || curr_key > Qt::Key_ydiaeresis)
                ) || (e -> modifiers() != Qt::NoModifier && !is_shortcut)
            ) {
                customKeyPressEvent(e);
//                procRevision();
                return;
            }

            if (!is_shortcut)
                customKeyPressEvent(e);

//            QTextCursor tc = textCursor();
//            procCompleterForCursor(tc, is_shortcut);

            if (!is_shortcut)
                return;
        }
    }

    customKeyPressEvent(e);
}

void Editor::keyReleaseEvent(QKeyEvent * e) {
    int curr_key = e -> key();

    switch (curr_key) {
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_Delete:
        case Qt::Key_Backspace:
        case Qt::Key_Return:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
        case Qt::Key_Right:
        case Qt::Key_Left:
        case Qt::Key_Up:
        case Qt::Key_Down: {
            blickCursor();
        break;}
    }

    QWidget::keyReleaseEvent(e);
}
void Editor::wheelEvent(QWheelEvent * e) {
    QWidget::wheelEvent(e);

    if (e -> orientation() == Qt::Vertical) {
        qint32 offset = -1/*_context -> __line_height*/ * _context -> _vscroll_factor;

        if (e -> delta() < 0) {
            offset = -offset;
        }

        _vscroll -> setValue(_vscroll -> value() + qint32(offset));
    } else {
        qint32 offset = -1/*_context -> __symbol_width*/ * _context -> _hscroll_factor;

        if (e -> delta() < 0) {
            offset = -offset;
        }

        _hscroll -> setValue(_hscroll -> value() + qint32(offset));
    }
}
void Editor::focusInEvent(QFocusEvent * e) {
    QWidget::focusInEvent(e);
}

void Editor::mousePressEvent(QMouseEvent * e) {
    Cursor c = textCursorForPos(e -> localPos());

    if (c.isValid()) {
        _context -> _cursors[0] = c;

        blickCursor();
        emit update();
    }

    QWidget::mousePressEvent(e);
}

void Editor::mouseDoubleClickEvent(QMouseEvent * e) {

    QWidget::mouseDoubleClickEvent(e);
}

//void Editor::procCompleter(QTextCursor & tc, const bool & initiate_popup) {
//    QTextBlock block = tc.block();

//    completer_info.cursor_pos = tc.positionInBlock();
//    completer_info.word_start = 0;
//    completer_info.word_length = 0;
//    completer_info.lex = wrapper -> getWordBoundaries(completer_info.word_start, completer_info.word_length, block, completer_info.cursor_pos, false);
//    completer_info.at_word_end = completer_info.cursor_pos - completer_info.word_start == completer_info.word_length;

//    QString block_text = block.text();
//    QStringRef completion_prefix = block_text.midRef(completer_info.word_start, completer_info.cursor_pos - completer_info.word_start);
//    QStringRef text = block_text.midRef(completer_info.word_start, completer_info.word_length);

//    if (!wrapper -> isCompleterInitiable(completer_info.lex, completer_info.at_word_end)) {
//        completer -> hide();
//        return;
//    }

//    if (initiate_popup && tc.hasSelection()) {
//        completer -> reset();
//        completer -> setCompletionPrefix(QString());
//    } else {
//        if (!initiate_popup && text.length() < 2) {
//            completer -> hide();
//            return;
//        }

//        if (completion_prefix != completer -> completionPrefix()) {
//            completer -> reset();

//            bool from_scratch = !wrapper -> isCompleterContinuable(completer_info.lex, completer_info.at_word_end);

//            completer -> setCompletionPrefix(
//                from_scratch ? QString() : completion_prefix.toString()
//            );
//        }
//    }

//    int completions_amount = completer -> completionCount();

//    if (completions_amount == 0) {
//        completer -> hide();
//        return;
//    }

//    if (initiate_popup && completions_amount == 1 && completion_prefix == text) {
//        applyCompletion(completer -> currentCompletion());
//        completer -> hide();
//    } else {
//        QRect cr = cursorRect();
//        cr.setLeft(cr.left() + extra_area -> width());
//        cr.setWidth(completer -> execWidth());

//        completer -> complete(cr);
//    }
//}

void Editor::applyCompletion(const QString & completion) {
    qDebug() << "CUSTOM EDITOR: applyCompletion";

//    QTextCursor tc = textCursor();

//    if (!tc.hasSelection()) {
//        bool is_replaceable = wrapper -> isCompleterReplaceable(completer_info.lex, completer_info.cursor_pos == completer_info.word_start);

//        if (is_replaceable) {
//            int pos = tc.block().position();
//            tc.setPosition(pos + completer_info.word_start, QTextCursor::MoveAnchor);
//            tc.setPosition(pos + completer_info.word_start + completer_info.word_length, QTextCursor::KeepAnchor);
//        }
//    }

////        wordUnderCursor(tc, wuco_remove_full);

//    tc.insertText(completion);

    _completer -> reset();
}

