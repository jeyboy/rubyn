#include "breakpoints_panel.h"

#include "controls/logger.h"
#include "project/file.h"

#include <qlistwidget.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>

QString BreakpointsPanel::buildUid(File * f, const EDITOR_POS_TYPE & line_num) {
    return f -> uid() % ':' % QString::number(line_num);
}

BreakpointsPanel::BreakpointsPanel(QWidget * parent) : QWidget(parent), breakpoints(nullptr) {
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

    l -> addWidget(control_panel, 0);
    l -> addWidget(breakpoints, 1);
}

void BreakpointsPanel::addBreakpoint(File * f, const EDITOR_POS_TYPE & line_num) {
    emit breakpointAdded(f, line_num);

    QListWidgetItem * itm = new QListWidgetItem(QIcon(QLatin1Literal(":/breakpoint")), f -> path());
    itm -> setData(Qt::UserRole + 1, line_num);

    records.insert(buildUid(f, line_num), itm);

    breakpoints -> addItem(itm);
}
void BreakpointsPanel::moveBreakpoint(File * f, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num) {
    emit breakpointMoved(f, old_line_num, new_line_num);

    if (records.contains(f -> uid())) {
        QListWidgetItem * itm = records[f -> uid()];
    } else {
        Logger::error(QLatin1Literal("moveBreakpoint"), QLatin1Literal("Can't find breakpoint for action"));
    }
}
void BreakpointsPanel::removeBreakpoint(File * f, const EDITOR_POS_TYPE & line_num) {
    emit breakpointRemoved(f, line_num);

}
