#include "header_dock_widget.h"

#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtoolbutton.h>

#include <qdebug.h>

HeaderDockWidget::HeaderDockWidget(QWidget * parent, const QString & title) : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground, true);
    setMaximumHeight(40);
    setContentsMargins(5, 0, 5, 0);
    setStyleSheet("HeaderDockWidget { background-color: rgba(0, 0, 0, .6); }");

    _layout = new QHBoxLayout(this);
    _layout -> setContentsMargins(1, 1, 1, 1);

    title_widget = new QLabel(title, this);
    QFont font = title_widget -> font();
    font.setBold(true);
    font.setPixelSize(12);
    font.setKerning(true);
    title_widget -> setFont(font);
    title_widget -> setStyleSheet("color: white;");

    _layout -> addWidget(title_widget, 0, Qt::AlignLeft);

    insertButton(QIcon(QLatin1Literal(":/tools/search")), this, SLOT(toggleSearch()), 1);
    _layout -> insertStretch(2);

    search_widget = new QLineEdit(this);
    connect(search_widget, SIGNAL(editingFinished()), this, SLOT(toggleSearch()));
//    connect(search_widget, SIGNAL(textEdited(const QString &)), , SLOT());

    _layout -> addWidget(search_widget, 2, Qt::AlignLeft);

    search_widget -> setVisible(false);
}

void HeaderDockWidget::setTitle(const QString & title) {
    title_widget -> setText(title);
}

void HeaderDockWidget::showSearch(const bool & show) {
    if (search_widget -> isVisible() != show)
        search_widget -> setText(QLatin1String());

    search_widget -> setVisible(show);
}

QToolButton * HeaderDockWidget::insertButton(const QIcon & ico, QObject * target, const char * slot, const int pos, const Qt::Alignment & alignment) {
    QToolButton * btn = new QToolButton(this);
    btn -> setIcon(ico);

    connect(btn, SIGNAL(released()), target, slot);

    if (pos < 0)
        _layout -> addWidget(btn, 0, alignment);
    else
        _layout -> insertWidget(pos, btn, 0, alignment);

    return btn;
}

void HeaderDockWidget::toggleSearch() {
    showSearch(!search_widget -> isVisible());
}
