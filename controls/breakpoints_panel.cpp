#include "breakpoints_panel.h"

#include "controls/logger.h"
#include "project/file.h"

#include <qlistwidget.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qshortcut.h>

BreakpointsPanel::BreakpointsPanel(QWidget * parent) : QWidget(parent), breakpoints(nullptr), active_breakpoint(nullptr) {
    QHBoxLayout * l = new QHBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    l -> setSpacing(0);

    QToolBar * control_panel = new QToolBar(this);
    control_panel -> setOrientation(Qt::Vertical);
    control_panel -> setIconSize(QSize(18, 18));

    QToolButton * btn0 = new QToolButton(control_panel);
    QIcon ico;

    ico.addPixmap(QPixmap(QLatin1Literal(":/breakpoint_disable_all")), QIcon::Normal, QIcon::Off);
    ico.addPixmap(QPixmap(QLatin1Literal(":/breakpoint_enable_all")), QIcon::Normal, QIcon::On);

    btn0 -> setIcon(ico);
    btn0 -> setToolTip(QLatin1Literal("Disable all"));
    btn0 -> setCheckable(true);
    control_panel -> addWidget(btn0);

    QToolButton * btn1 = new QToolButton(control_panel);
    btn1 -> setIcon(QIcon(QLatin1Literal(":/breakpoint_delete_all")));
    btn1 -> setToolTip(QLatin1Literal("Remove all"));
    control_panel -> addWidget(btn1);

    breakpoints = new QListWidget(this);

    connect(breakpoints, &QListWidget::itemDoubleClicked, this, &BreakpointsPanel::breakpointDoubleClicked);

    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), breakpoints);
    connect(shortcut, SIGNAL(activated()), this, SLOT(deleteBreakpointItem()));


    l -> addWidget(control_panel, 0);
    l -> addWidget(breakpoints, 1);
}

void BreakpointsPanel::activateBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num) {
    if (active_breakpoint) {
        active_breakpoint -> setData(Qt::BackgroundRole, QVariant());
//        active_breakpoint -> setData(Qt::ForegroundRole, QVariant());
    }

    if (!records.contains(path))
        return;

    active_breakpoint = records[path][line_num];
    active_breakpoint -> setData(Qt::BackgroundRole, QColor(0, 212, 212));
//    active_breakpoint -> setData(Qt::ForegroundRole, QColor(255, 255, 255));
}

void BreakpointsPanel::addBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num) {
//    emit breakpointAdded(path, line_num);

    QListWidgetItem * itm = new QListWidgetItem(QIcon(QLatin1Literal(":/breakpoint")), buildName(path, line_num));
    itm -> setData(Qt::UserRole + 1, path);
    itm -> setData(Qt::UserRole + 2, line_num);

    if (!records.contains(path))
        records.insert(path, QHash<EDITOR_POS_TYPE, QListWidgetItem * >());

    records[path].insert(line_num, itm);

    breakpoints -> addItem(itm);
}
void BreakpointsPanel::moveBreakpoint(const QString & path, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num) {
    if (!records.contains(path))
        return;

    QHash<EDITOR_POS_TYPE, QListWidgetItem * > & lines = records[path];

    if (lines.contains(old_line_num)) {
        QListWidgetItem * itm = lines.take(old_line_num);
        itm -> setText(buildName(path, new_line_num));
        itm -> setData(Qt::UserRole + 2, new_line_num);
    }
}
void BreakpointsPanel::removeBreakpoint(const QString & path, const EDITOR_POS_TYPE & line_num) {
    if (!records.contains(path))
        return;

    QHash<EDITOR_POS_TYPE, QListWidgetItem * > & lines = records[path];

    if (!lines.contains(line_num))
        return;

    delete lines.take(line_num);
    emit breakpointRemoved(path, line_num);
}

void BreakpointsPanel::deleteBreakpointItem() {
    qDebug() << "deleteBreakpointItem";

    QListWidgetItem * item = breakpoints -> currentItem();

    if (item == active_breakpoint)
        active_breakpoint = nullptr;

    QString path = item -> data(Qt::UserRole + 1).toString();
    EDITOR_POS_TYPE line_num = item -> data(Qt::UserRole + 2).toInt();

    removeBreakpoint(path, line_num);
}

void BreakpointsPanel::breakpointDoubleClicked(QListWidgetItem * item) {
    qDebug() << "breakpointDoubleClicked";

    QString path = item -> data(Qt::UserRole + 1).toString();
    EDITOR_POS_TYPE line_num = item -> data(Qt::UserRole + 2).toInt();

    activateBreakpoint(path, line_num);
}
