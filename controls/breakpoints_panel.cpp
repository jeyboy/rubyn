#include "breakpoints_panel.h"

#include <qlistwidget.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>

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

}
void BreakpointsPanel::moveBreakpoint(File * f, const EDITOR_POS_TYPE & line_num) {

}
void BreakpointsPanel::removeBreakpoint(File * f, const EDITOR_POS_TYPE & line_num) {

}
