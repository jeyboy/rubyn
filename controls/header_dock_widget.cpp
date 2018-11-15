#include "header_dock_widget.h"

#include "search_box.h"

#include <qlayout.h>
#include <qlabel.h>
#include <qtoolbutton.h>

HeaderDockWidget::HeaderDockWidget(QWidget * parent, const QString & title) : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground, true);
    setMinimumHeight(26);
    setStyleSheet("HeaderDockWidget { background-color: rgba(0, 0, 0, .6); }");

    _layout = new QHBoxLayout(this);
    _layout -> setContentsMargins(5, 0, 5, 0);
    _layout -> setSpacing(2);
//    _layout -> setSizeConstraint(QLayout::SetDefaultConstraint);

    title_widget = new QLabel(title, this);
    title_widget -> setMinimumHeight(26);
    QFont font = title_widget -> font();
    font.setBold(true);
    font.setPixelSize(12);
    font.setKerning(true);
    title_widget -> setFont(font);
    title_widget -> setStyleSheet("color: white;");

    _layout -> addWidget(title_widget, 0, Qt::AlignLeft);
    _layout -> addWidget(new QLabel(QLatin1Literal(" "), this), 0, Qt::AlignLeft);
    _layout -> addStretch(0);

    search_btn = insertButton(QIcon(QLatin1Literal(":/tools/search")), this, SLOT(toggleSearch()), 0);
    search_btn -> setToolTip(QLatin1Literal("Find files and folders <br/><b>Ctrl + F</b>")); // "Find files and folders <br/><font color='#22aaff'>Ctrl + F</font>"
    search_btn -> setVisible(false);

    search_widget = new SearchBox(this);
    connect(search_widget, SIGNAL(returnPressed()), this, SLOT(toggleSearch()));

    _layout -> addWidget(search_widget, 10, Qt::AlignLeft);

    search_widget -> setVisible(false);
}

void HeaderDockWidget::setTitle(const QString & title) {
    title_widget -> setText(title);
}

QToolButton * HeaderDockWidget::insertButton(const QIcon & ico, QObject * target, const char * slot, const int pos, const Qt::Alignment & alignment) {
    QToolButton * btn = new QToolButton(this);
    btn -> setIcon(ico);

    if (target)
        connect(btn, SIGNAL(released()), target, slot);

    if (pos < 0)
        _layout -> addWidget(btn, 0, alignment);
    else
        _layout -> insertWidget(pos + 2, btn, 0, alignment);

    return btn;
}

void HeaderDockWidget::registerSearchCallbacks(QObject * target, const char * search_show_signal, const char * search_hide_signal, const char * search_request_slot, const char * search_close_slot) {
    search_btn -> setVisible(true);

    connect(target, search_show_signal, this, SLOT(initiateSearch(const QString &)));
    connect(target, search_hide_signal, this, SLOT(hideSearch()));
    connect(search_widget, SIGNAL(textChanged(const QString &)), target, search_request_slot);
    connect(search_widget, SIGNAL(hidden()), target, search_close_slot);
}


void HeaderDockWidget::showSearch(const bool & show) {
    blockSignals(true);

    if (search_widget -> isVisible() != show)
        search_widget -> setText(QLatin1String());

    if (!show) //INFO: monkey patch: focus out call toggleSearch second time. We shoul remove focus manually and block signal
        parentWidget() -> setFocus();

    search_widget -> setVisible(show);
    blockSignals(false);

    if (show && !search_widget -> hasFocus())
        search_widget -> setFocus();
}

void HeaderDockWidget::initiateSearch(const QString & pattern) {
    showSearch();
    search_widget -> setText(pattern);
}

void HeaderDockWidget::hideSearch() {
    showSearch(false);
}

void HeaderDockWidget::toggleSearch() {
    showSearch(!search_widget -> isVisible());
}
