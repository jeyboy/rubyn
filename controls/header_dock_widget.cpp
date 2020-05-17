#include "header_dock_widget.h"

#include "search_panel.h"

#include <qlayout.h>
#include <qlabel.h>
#include <qtoolbutton.h>

HeaderDockWidget::HeaderDockWidget(QWidget * parent, const QString & title) : QWidget(parent), ico_widget(nullptr) {
    setAttribute(Qt::WA_StyledBackground, true);
    setMinimumHeight(26);
    setStyleSheet("HeaderDockWidget { background-color: rgba(0, 0, 0, .6); }");

    _layout = new QHBoxLayout(this);
    _layout -> setContentsMargins(5, 0, 5, 0);
    _layout -> setSpacing(2);
//    _layout -> setSizeConstraint(QLayout::SetDefaultConstraint);

    ico_widget = new QLabel(this);
    ico_widget -> setMargin(0);
    ico_widget -> setFixedHeight(26);
    ico_widget -> hide();
    _layout -> addWidget(ico_widget, 0, Qt::AlignLeft);

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

    search_widget = new SearchPanel(this);
    search_widget -> setInfinityPad();
    connect(search_widget, SIGNAL(returnPressed()), this, SLOT(toggleSearch()));

    _layout -> addWidget(search_widget, 10, Qt::AlignLeft);

    search_widget -> setVisible(false);
}

void HeaderDockWidget::setIcon(const QString & ico_path) {
    ico_widget -> show();
    ico_widget -> setPixmap(QPixmap(ico_path).scaled(16, 16, Qt::KeepAspectRatio));
}

QString HeaderDockWidget::title() {
    return title_widget -> text();
}

void HeaderDockWidget::setTitle(const QString & title) {
    title_widget -> setText(title);
}

void HeaderDockWidget::insertButton(QWidget * btn, QObject * target, const char * slot, const int pos, const Qt::Alignment & alignment) {
    btn -> setParent(this);

    if (target)
        connect(btn, SIGNAL(released()), target, slot);

    if (pos < 0)
        _layout -> addWidget(btn, 0, alignment);
    else
        _layout -> insertWidget(pos < 0 ? pos : (pos + 3), btn, 0, alignment);
}

QToolButton * HeaderDockWidget::insertButton(const QIcon & ico, QObject * target, const char * slot, const int pos, const Qt::Alignment & alignment) {
    QToolButton * btn = new QToolButton(this);
    btn -> setIcon(ico);

    insertButton(btn, target, slot, pos, alignment);

    return btn;
}

void HeaderDockWidget::registerSearchCallbacks(const DockWidgetSearchConnector & connector) {
    search_btn -> setVisible(true);

    connect(connector.target, connector.search_show_signal, this, SLOT(initiateSearch(const QString &)));
    connect(connector.target, connector.search_hide_signal, this, SLOT(hideSearch()));

    if (connector.search_amount_signal)
        connect(connector.target, connector.search_amount_signal, search_widget, SLOT(finded(const int &)));

    connect(search_widget, SIGNAL(find(const QRegularExpression &)), connector.target, connector.search_request_slot);
    connect(search_widget, SIGNAL(closed()), connector.target, connector.search_close_slot);

    if (!connector.search_prev_result_slot || !connector.search_next_result_slot) {
        search_widget -> removePrevNext();
    } else {
        connect(search_widget, SIGNAL(toPrevResult(QString * replace)), connector.target, connector.search_prev_result_slot);
        connect(search_widget, SIGNAL(toNextResult(QString * replace)), connector.target, connector.search_next_result_slot);
    }
}


void HeaderDockWidget::showSearch(const bool & show) {
//    blockSignals(true);

    if (search_widget -> isVisible() != show)
        search_widget -> setText(QLatin1String());

//    if (!show) //INFO: monkey patch: focus out call toggleSearch second time. We shoul remove focus manually and block signal
//        parentWidget() -> setFocus();

    search_widget -> setVisible(show);
//    blockSignals(false);

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
