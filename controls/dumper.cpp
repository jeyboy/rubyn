#include "dumper.h"

#include "ide_window.h"

#include "misc/dir.h"
#include "misc/screen.h"
#include "misc/variant_ptr.h"

#include "tools/json/json.h"
#include "tools/json/json_arr.h"
#include "tools/json/json_obj.h"

#include "controls/logger.h"
#include "controls/project_tree.h"
#include "controls/tabs_block.h"

#include "project/ifolder.h"

#include <qsettings.h>
#include <qsplitter.h>
#include <qscrollbar.h>

void Dumper::loadTree(IDEWindow * w, JsonObj & json) {
    JsonArr arr = json.arr(QLatin1Literal("tree"));

    if (arr.isEmpty()) {
        return;
    }

    for(JsonArr::Iterator it = arr.begin(); it != arr.end(); it++)
        w -> openFolder(QUrl::fromLocalFile((*it).toString()));
}

void Dumper::saveTree(IDEWindow * w, JsonObj & json) {
    int limit = w -> tree -> topLevelItemCount();

    if (limit == 0) return; // we do not have items in tree

    QJsonArray arr;

    for(int i = 0; i < limit; i++) {
        QTreeWidgetItem * top = w -> tree -> topLevelItem(i);

        QVariant data = top -> data(0, Qt::UserRole);

        if (data.isNull()) {
            Logger::obj().write(QLatin1Literal("Dumper"), QLatin1Literal("Cant save project: ") % top -> text(0));
        }
        else {
            IFolder * folder = VariantPtr<IFolder>::asPtr(data);
            arr.append(folder -> fullPath());
        }
    }

    json.insert(QLatin1Literal("tree"), arr);
}

void Dumper::loadTabs(IDEWindow * w, JsonObj & json) {
    JsonArr tabs = json.arr(QLatin1Literal("editors"));

    if (tabs.isEmpty())
        return;

    bool new_editor = false;

    for(JsonArr::Iterator tab = tabs.begin(); tab != tabs.end(); tab++) {
        JsonObj widget_obj = (*tab).toObject();
        new_editor = tab != tabs.begin();

        QString curr_path = widget_obj.string(QLatin1Literal("current"));

        JsonArr items = widget_obj.arr(QLatin1Literal("tabs"));
        int index = 0, counter = 0;

        for(JsonArr::Iterator item = items.begin(); item != items.end(); item++, counter++) {
            QString path = (*item).toString();

            if (path == curr_path) {
                index = counter;
            }

            w -> fileOpenRequired(path, nullptr, new_editor);
            new_editor = false;
        }

        w -> active_editor -> currentTabIndexChanged(index);
    }
}

void Dumper::saveTabs(IDEWindow * w, JsonObj & json) {
//    int index = w -> widgets_list -> indexOf(w -> active_editor);

    QJsonArray arr;

    for(int i = 0; i < w -> widgets_list -> count(); i++) {
        QWidget * widget = w ->  widgets_list -> widget(i);
        TabsBlock * editor = dynamic_cast<TabsBlock *>(widget);

        uint limit = editor -> tabsCount();

        if (limit == 0)
            continue;

        QJsonObject widget_obj;
        QJsonArray tabs_arr;

        for(uint j = 0; j < limit; j++) {
            QString tab_path = editor -> tabFilePath(j);

            if (!tab_path.isNull())
                tabs_arr.append(tab_path);
        }

        QString curr_path = editor -> currentTabFilePath();

        if (!curr_path.isNull())
            widget_obj.insert(QLatin1Literal("current"), curr_path);

        widget_obj.insert(QLatin1Literal("tabs"), tabs_arr);

        arr << widget_obj;
    }

    json.insert(QLatin1Literal("editors"), arr);
}

void Dumper::load(IDEWindow * w, const QString & settings_filename) {
    QSettings settings(Dir::appPath(settings_filename), QSettings::IniFormat, w);

    QVariant data = settings.value(QLatin1Literal("data"));

    if (data.isValid()) {
        JsonObj obj = JsonObj::fromJsonStr(data.toString());

        loadTree(w, obj);
        loadTabs(w, obj);
    }

    QVariant geometry_state = settings.value(QLatin1Literal("geometry"));
    if (geometry_state.isValid())
        w -> restoreGeometry(geometry_state.toByteArray());

//    ///////////////////////////////////////////////////////////
//    ///location correction (test needed)
//    ///////////////////////////////////////////////////////////
    locationCorrection(w);

    QVariant obj_state = settings.value(QLatin1Literal("state"));
    if (obj_state.isValid())
        w -> restoreState(obj_state.toByteArray());
    ///////////////////////////////////////////////////////////

//    if (settings.value(SETTINGS_WINDOW_MAXIMIZED_KEY).toBool()) {
//        QApplication::processEvents();
//        showMaximized();
//    }

    qApp -> processEvents();

    QVariant tree_state = settings.value(QLatin1Literal("tree_state"));
    if (tree_state.isValid()) {
        w -> tree -> restoreState(tree_state.toByteArray());
    }

    QVariant tree_pos = settings.value(QLatin1Literal("tree_pos"));
    if (tree_pos.isValid()) {
        QScrollBar * scroll = w -> tree -> verticalScrollBar();
        scroll -> setProperty("last_pos", tree_pos);

        connect(scroll, SIGNAL(rangeChanged(int,int)), this, SLOT(treeRangeChanged(int,int)));
    }

    QVariant widgets_list_geom = settings.value(QLatin1Literal("widgets_list_geom"));
    if (widgets_list_geom.isValid())
        w -> widgets_list -> restoreGeometry(widgets_list_geom.toByteArray());

    QVariant widgets_list_state = settings.value(QLatin1Literal("widgets_list_state"));
    if (widgets_list_state.isValid())
        w -> widgets_list -> restoreState(widgets_list_state.toByteArray());

    QVariant active_editor_index = settings.value(QLatin1Literal("active_editor_index"));

    if (active_editor_index.isValid()) {
        TabsBlock * active = dynamic_cast<TabsBlock *>(w -> widgets_list -> widget(active_editor_index.toInt()));
        if (active)
            w -> setActiveEditor(active);
    }
}

void Dumper::save(IDEWindow * w, const QString & settings_filename) {
    QSettings settings(Dir::appPath(settings_filename), QSettings::IniFormat, w);

    JsonObj obj;

    saveTree(w, obj);
    saveTabs(w, obj);

    settings.setValue(QLatin1Literal("data"), obj.toJsonStr());
    settings.setValue(QLatin1Literal("geometry"), w -> saveGeometry());
    settings.setValue(QLatin1Literal("state"), w -> saveState());
    settings.setValue(QLatin1Literal("tree_state"), w -> tree -> saveState());
    settings.setValue(QLatin1Literal("tree_pos"), w -> tree -> verticalScrollBar() -> value());

    settings.setValue(QLatin1Literal("widgets_list_state"), w -> widgets_list -> saveState());
    settings.setValue(QLatin1Literal("widgets_list_geom"), w -> widgets_list -> saveGeometry());
    settings.setValue(QLatin1Literal("active_editor_index"), w -> widgets_list -> indexOf(w -> active_editor));

    settings.sync();
}

void Dumper::locationCorrection(IDEWindow * w) {
    int left = w -> x();
    int top = w -> y();
    int width, height;

    Screen::screenSize(width, height);

    if (left >= width)
        left = width - 50;

    if (top >= height)
        top = height - 50;

    w -> move(left, top);
}

void Dumper::treeRangeChanged(int /*min*/, int /*max*/) {
    QScrollBar * scroll = static_cast<QScrollBar *>(sender());
    QVariant last_pos = scroll -> property("last_pos");

    if (last_pos.isValid()) {
        int pos = last_pos.toInt();

        disconnect(scroll, SIGNAL(rangeChanged(int,int)), this, SLOT(treeRangeChanged(int,int)));
        scroll -> setValue(pos);
    }
}
