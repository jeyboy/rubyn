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
#include "editor/code_editor.h"

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
            Logger::error(QLatin1Literal("Dumper"), QLatin1Literal("Cant save project: ") % top -> text(0));
        }
        else {
            IFolder * folder = VariantPtr<IFolder>::asPtr(data);
            arr.append(folder -> fullPath());
        }
    }

    json.insert(QLatin1Literal("tree"), arr);
}

void Dumper::loadTabs(IDEWindow * w, JsonObj & json) {
    QJsonObject editors = json.obj(QLatin1Literal("editors"));

    TabsBlock * active = nullptr;

    loadSplitter(w, w -> widgets_list, editors, active);

    if (active)
        emit active -> activated(active);
}

void Dumper::saveTabs(IDEWindow * w, JsonObj & json) {
    QJsonObject editors_json;
    saveSplitter(w, w -> widgets_list, editors_json);

    json.insert(QLatin1Literal("editors"), editors_json);
}

void Dumper::saveTab(IDEWindow * w, TabsBlock * editor, QJsonObject & widget_obj) {
    int limit = editor -> tabsCount();

    QJsonArray tabs_arr;

    for(int j = 0; j < limit; j++) {
        QString tab_path = editor -> tabFilePath(j);

        if (!tab_path.isNull()) {
            QJsonObject tab_data;
            tab_data.insert(QLatin1Literal("path"), tab_path);

            QVariant state;
            if (editor -> tabDumpState(j, state))
                tab_data.insert(QLatin1Literal("state"), QJsonValue::fromVariant(state));

            tab_data.insert(QLatin1Literal("scroll_y"), editor -> tabVerticalScrollPos(j));

            tabs_arr.append(tab_data);
        }
    }

    QString curr_path = editor -> currentTabFilePath();

    if (!curr_path.isNull())
        widget_obj.insert(QLatin1Literal("current"), curr_path);

    widget_obj.insert(QLatin1Literal("tabs"), tabs_arr);

    QScrollBar * scroll = editor -> editor() -> verticalScrollBar();

    if (scroll -> value() != 0)
        widget_obj.insert(QLatin1Literal("scroll_y"), scroll -> value());

    if (w -> active_editor == editor)
        widget_obj.insert(QLatin1Literal("is_active"), true);
}

void Dumper::saveSplitter(IDEWindow * w, QSplitter * list, QJsonObject & obj) {
    QJsonArray arr;

    for(int i = 0; i < list -> count(); i++) {
        QJsonObject json;
        QWidget * widget = list -> widget(i);
        TabsBlock * editor = qobject_cast<TabsBlock *>(widget);

        if (editor) {
            int limit = editor -> tabsCount();

            if (limit == 0)
                continue;

            json.insert(QLatin1Literal("type"), "e");
            saveTab(w, editor, json);
        } else {
            QSplitter * splitter = qobject_cast<QSplitter *>(widget);

            if (splitter) {
                json.insert(QLatin1Literal("type"), "s");
                saveSplitter(w, splitter, json);
            } else {
                qDebug() << "PIPI";
                continue;
            }
        }

        arr << json;
    }

    obj.insert(QLatin1Literal("dir"), list -> orientation());
    obj.insert(QLatin1Literal("sizes"), QJsonValue::fromVariant(QVariant::fromValue(list -> sizes())));
    obj.insert(QLatin1Literal("child"), arr);
}

void Dumper::loadSplitter(IDEWindow * w, QSplitter * list, QJsonObject & obj, TabsBlock *& active) {
    list -> setOrientation(static_cast<Qt::Orientation>(obj.value(QLatin1Literal("dir")).toInt()));

    QJsonArray children = obj.value(QLatin1Literal("child")).toArray();

    if (children.isEmpty())
        return;

    for(QJsonArray::Iterator child = children.begin(); child != children.end(); child++) {
        JsonObj child_obj = (*child).toObject();

        if (child_obj.string(QLatin1Literal("type")) == QLatin1Literal("e")) {           
            QString curr_path = child_obj.string(QLatin1Literal("current"));
            int scroll_y = child_obj.integer(QLatin1Literal("scroll_y"));

            JsonArr items = child_obj.arr(QLatin1Literal("tabs"));
            int index = 0, counter = 0;

            w -> setupEditor(list);

            if (child_obj.hasKey(QLatin1Literal("is_active")))
                active = w -> active_editor;

            for(JsonArr::Iterator item = items.begin(); item != items.end(); item++, counter++) {
                QJsonObject obj = (*item).toObject();

                QString path = obj.value(QLatin1Literal("path")).toString();
                QVariant state = obj.value(QLatin1Literal("state")).toVariant();
                int tab_scroll_y = obj.value(QLatin1Literal("scroll_y")).toInt();

                if (path == curr_path) {
                    index = counter;
                    tab_scroll_y = scroll_y;
                }

                w -> fileOpenRequired(path, nullptr, false, true, tab_scroll_y);
                w -> active_editor -> tabRestoreState(counter, state);
            }

            w -> active_editor -> currentTabIndexChanged(index);
        } else {
            QSplitter * new_child = w -> setupChildSplitter(list);
            list -> addWidget(new_child);
            loadSplitter(w, new_child, child_obj, active);
        }
    }

    list -> setSizes(obj.value(QLatin1Literal("sizes")).toVariant().value<QList<int>>());
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

    QVariant tree_state = settings.value(QLatin1Literal("tree_state"));
    if (tree_state.isValid()) {
        w -> tree -> restoreState(tree_state.toByteArray());
    }

    QVariant tree_pos = settings.value(QLatin1Literal("tree_pos"));
    if (tree_pos.isValid()) {
        QScrollBar * scroll = w -> tree -> verticalScrollBar();
        scroll -> setProperty("last_pos", tree_pos);
        scroll -> setProperty("qty", 1);

        connect(scroll, SIGNAL(rangeChanged(int,int)), this, SLOT(scrollRangeChanged(int,int)));
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

void Dumper::scrollRangeChanged(int /*min*/, int /*max*/) {
    QScrollBar * scroll = static_cast<QScrollBar *>(sender());
    QVariant last_pos = scroll -> property("last_pos");

    if (last_pos.isValid()) {
//        QVariant qty = scroll -> property("qty");
        int pos = last_pos.toInt();
//        int qty_val = qty.toInt() - 1;

//        if (qty_val == 0) {
            disconnect(scroll, SIGNAL(rangeChanged(int,int)), this, SLOT(scrollRangeChanged(int,int)));
            scroll -> setProperty("last_pos", QVariant());
//        }
//        else scroll -> setProperty("qty", qty_val);

        scroll -> setValue(pos);
    }
}
