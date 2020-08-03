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
    btn0 -> setIconSize(QSize(16, 16));
    btn0 -> setIcon(QIcon(QLatin1String(":/breakpoint_disabled")));
    btn0 -> setToolTip(QLatin1String("Disable selected"));
    control_panel -> addWidget(btn0);


    QToolButton * btn1 = new QToolButton(control_panel);
    QIcon ico;

    ico.addPixmap(QPixmap(QLatin1String(":/breakpoint_disable_all")), QIcon::Normal, QIcon::Off);
    ico.addPixmap(QPixmap(QLatin1String(":/breakpoint_enable_all")), QIcon::Normal, QIcon::On);

    btn1 -> setIcon(ico);
    btn1 -> setToolTip(QLatin1String("Disable all"));
    btn1 -> setCheckable(true);
    control_panel -> addWidget(btn1);


    QToolButton * btn2 = new QToolButton(control_panel);
    btn2 -> setIcon(QIcon(QLatin1String(":/breakpoint_delete_all")));
    btn2 -> setToolTip(QLatin1String("Remove all"));
    control_panel -> addWidget(btn2);

    breakpoints = new QListWidget(this);

    connect(breakpoints, &QListWidget::itemDoubleClicked, this, &BreakpointsPanel::breakpointDoubleClicked);

    QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), breakpoints);
    shortcut -> setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(deleteBreakpointItem()));


    l -> addWidget(control_panel, 0);
    l -> addWidget(breakpoints, 1);
}

void BreakpointsPanel::activateBreakpoint(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
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

void BreakpointsPanel::addBreakpoint(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
//    emit breakpointAdded(path, line_num);

    QListWidgetItem * itm = new QListWidgetItem(QIcon(QLatin1String(":/breakpoint")), buildName(path, line_num));
    itm -> setData(Qt::UserRole + 1, path);
    itm -> setData(Qt::UserRole + 2, line_num);
    itm -> setData(Qt::UserRole + 3, project_id);

    if (!records.contains(path))
        records.insert(path, QHash<EDITOR_POS_TYPE, QListWidgetItem * >());

    records[path].insert(line_num, itm);

    breakpoints -> addItem(itm);
}
void BreakpointsPanel::moveBreakpoint(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & old_line_num, const EDITOR_POS_TYPE & new_line_num) {
    if (!records.contains(path))
        return;

    QHash<EDITOR_POS_TYPE, QListWidgetItem * > & lines = records[path];

    QList<EDITOR_POS_TYPE> nums = lines.keys();

    EDITOR_POS_TYPE diff = new_line_num - old_line_num;

    for(QList<EDITOR_POS_TYPE>::Iterator it = nums.begin(); it != nums.end(); it++) {
        if (*it > old_line_num) {
            EDITOR_POS_TYPE new_pos = *it + diff;

            QListWidgetItem * itm = lines.take(*it);
            itm -> setText(buildName(path, new_pos));
            itm -> setData(Qt::UserRole + 2, new_pos);
            lines[new_pos] = itm;
        }
    }
}
void BreakpointsPanel::removeBreakpoint(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num) {
    if (!records.contains(path))
        return;

    if (line_num == NO_INFO) {
        if (active_breakpoint) {
            QString active_path = active_breakpoint -> data(Qt::UserRole + 1).toString();

            if (path == active_path)
                active_breakpoint = nullptr;
        }

        qDeleteAll(records.take(path));
    }

    QHash<EDITOR_POS_TYPE, QListWidgetItem * > & lines = records[path];

    if (!lines.contains(line_num))
        return;

    QListWidgetItem * item = lines.take(line_num);

    if (item == active_breakpoint)
        active_breakpoint = nullptr;

    delete item;
    emit breakpointRemoved(project_id, path, line_num);
}

void BreakpointsPanel::deleteBreakpointItem() {
    qDebug() << "deleteBreakpointItem";

    QListWidgetItem * item = breakpoints -> currentItem();

    QString path = item -> data(Qt::UserRole + 1).toString();
    EDITOR_POS_TYPE line_num = item -> data(Qt::UserRole + 2).toInt();
    uint project_id = item -> data(Qt::UserRole + 3).toUInt();

    removeBreakpoint(project_id, path, line_num);
}

void BreakpointsPanel::breakpointDoubleClicked(QListWidgetItem * item) {
    qDebug() << "breakpointDoubleClicked";

    QString path = item -> data(Qt::UserRole + 1).toString();
    EDITOR_POS_TYPE line_num = item -> data(Qt::UserRole + 2).toInt();
    uint project_id = item -> data(Qt::UserRole + 3).toUInt();

    activateBreakpoint(project_id, path, line_num);
}
