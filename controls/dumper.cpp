#include "dumper.h"

#include "ide_window.h"

#include "misc/dir.h"
#include "misc/screen.h"
#include "misc/variant_ptr.h"
#include "misc/run_config.h"

#include "tools/json/json.h"
#include "tools/json/json_arr.h"
#include "tools/json/json_obj.h"

#include "controls/logger.h"
#include "controls/project_tree.h"
#include "controls/tabs_block.h"
//#include "controls/universal_editor.h"
#include "controls/dock_widget.h"
#include "controls/console_widget.h"
#include "controls/project_widget.h"
#include "controls/run_menu.h"

#include "project/ifolder.h"

#include <qsettings.h>
#include <qsplitter.h>
#include <qscrollbar.h>

void Dumper::loadTree(IDEWindow * w, JsonObj & json) {
    JsonArr arr = json.arr(QLatin1String("tree"));

    if (arr.isEmpty())
        return;

    for(JsonArr::Iterator it = arr.begin(); it != arr.end(); it++)
        w -> openFolder(QUrl::fromLocalFile((*it).toString()));
}

void Dumper::saveTree(IDEWindow * w, JsonObj & json) {
    int limit = w -> tree -> topLevelItemCount();

    if (limit == 0) return; // we do not have items in tree

    QJsonArray arr;

    for(int i = 0; i < limit; i++) {
        QTreeWidgetItem * top = w -> tree -> topLevelItem(i);

        QVariant data = top -> data(0, TREE_FOLDER_UID);

        if (data.isNull()) {
            Logger::error(QLatin1String("Dumper"), QLatin1String("Cant save project: ") % top -> text(0));
        }
        else {
            IFolder * folder = VariantPtr<IFolder>::asPtr(data);
            arr.append(folder -> fullPath());
        }
    }

    json.insert(QLatin1String("tree"), arr);
}

void Dumper::loadTabs(IDEWindow * w, JsonObj & json) {
    QJsonObject editors = json.obj(QLatin1String("editors"));

    TabsBlock * active = nullptr;

    loadSplitter(w, w -> widgets_list, editors, active);

    if (active)
        emit active -> activated(active);
}

void Dumper::saveTabs(IDEWindow * w, JsonObj & json) {
    QJsonObject editors_json;
    saveSplitter(w, w -> widgets_list, editors_json);

    json.insert(QLatin1String("editors"), editors_json);
}

void Dumper::saveTab(IDEWindow * w, TabsBlock * editor, QJsonObject & widget_obj) {
    int limit = editor -> tabsCount();

    QJsonArray tabs_arr;

    for(int j = 0; j < limit; j++) {
        QString tab_path = editor -> tabFilePath(j);

        if (!tab_path.isNull()) {
            QJsonObject tab_data;
            tab_data.insert(QLatin1String("path"), tab_path);

            QVariant state;
            if (editor -> tabDumpState(j, state))
                tab_data.insert(QLatin1String("state"), QJsonValue::fromVariant(state));

            QPoint scroll_data = editor -> tabScrollPos(j);

            tab_data.insert(QLatin1String("scroll_x"), scroll_data.x());
            tab_data.insert(QLatin1String("scroll_y"), scroll_data.y());

            tabs_arr.append(tab_data);
        }
    }

    QString curr_path = editor -> currentTabFilePath();

    if (!curr_path.isNull())
        widget_obj.insert(QLatin1String("current"), curr_path);

    widget_obj.insert(QLatin1String("tabs"), tabs_arr);

    QPoint scroll_val = editor -> currentTabScrollPos();

    widget_obj.insert(QLatin1String("scroll_x"), scroll_val.x());
    widget_obj.insert(QLatin1String("scroll_y"), scroll_val.y());

    if (w -> active_editor == editor)
        widget_obj.insert(QLatin1String("is_active"), true);
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

            json.insert(QLatin1String("type"), "e");
            saveTab(w, editor, json);
        } else {
            QSplitter * splitter = qobject_cast<QSplitter *>(widget);

            if (splitter) {
                json.insert(QLatin1String("type"), "s");
                saveSplitter(w, splitter, json);
            } else {
                qDebug() << "PIPI";
                continue;
            }
        }

        arr << json;
    }

    obj.insert(QLatin1String("dir"), list -> orientation());
    obj.insert(QLatin1String("sizes"), intArrToStr(list -> sizes()));
    obj.insert(QLatin1String("child"), arr);
}

void Dumper::loadSplitter(IDEWindow * w, QSplitter * list, QJsonObject & obj, TabsBlock *& active) {
    list -> setOrientation(static_cast<Qt::Orientation>(obj.value(QLatin1String("dir")).toInt()));

    QJsonArray children = obj.value(QLatin1String("child")).toArray();

    if (children.isEmpty())
        return;

    for(QJsonArray::Iterator child = children.begin(); child != children.end(); child++) {
        JsonObj child_obj = (*child).toObject();

        if (child_obj.string(QLatin1String("type")) == QLatin1String("e")) {
            QString curr_path = child_obj.string(QLatin1String("current"));

            QPoint scroll_data(child_obj.integer(QLatin1String("scroll_x")), child_obj.integer(QLatin1String("scroll_y")));

            JsonArr items = child_obj.arr(QLatin1String("tabs"));
            int index = 0, counter = 0;

            w -> setupEditor(list);

            if (child_obj.hasKey(QLatin1String("is_active")))
                active = w -> active_editor;

            for(JsonArr::Iterator item = items.begin(); item != items.end(); item++, counter++) {
                QJsonObject obj = (*item).toObject();

                QString path = obj.value(QLatin1String("path")).toString();
                QVariant state = obj.value(QLatin1String("state")).toVariant();


                QPoint tab_scroll_data(obj.value(QLatin1String("scroll_x")).toInt(), obj.value(QLatin1String("scroll_y")).toInt());

                if (path == curr_path) {
                    index = counter;
                    tab_scroll_data = scroll_data;
                }

                w -> fileOpenRequired(path, nullptr, false, true, tab_scroll_data);
                w -> active_editor -> tabRestoreState(counter, state);
            }

            w -> active_editor -> currentTabIndexChanged(index);
        } else {
            QSplitter * new_child = w -> setupChildSplitter(list);
            list -> addWidget(new_child);
            loadSplitter(w, new_child, child_obj, active);
        }
    }

    list -> setSizes(strToIntArr(obj.value(QLatin1String("sizes")).toString()));
}

void Dumper::loadConsoles(IDEWindow * w, JsonObj & json) {
    QJsonArray consoles = json.arr(QLatin1String("consoles"));

    if (consoles.isEmpty())
        return;

    for(JsonArr::Iterator it = consoles.begin(); it != consoles.end(); it++)
        w -> setupConsole(new ConsoleWidget((*it).toObject(), w));
}

void Dumper::saveConsoles(IDEWindow * w, JsonObj & json) {
    QList<DockWidget *> dock_widgets = w -> findChildren<DockWidget *>();

    QJsonArray ar;

    for(QList<DockWidget *>::Iterator it = dock_widgets.begin(); it != dock_widgets.end(); it++) {
        ConsoleWidget * console = qobject_cast<ConsoleWidget *>((*it) -> widget());

        if (console && (*it) -> isVisible()) {
            ar << console -> save();
        }
    }

    if (ar.size() > 0)
        json.insert(QLatin1String("consoles"), ar);
}

void Dumper::loadProjectWidgets(IDEWindow * w, JsonObj & json) {
    QJsonArray pro_widgets = json.arr(QLatin1String("pro_widgets"));

    if (pro_widgets.isEmpty())
        return;

    for(JsonArr::Iterator it = pro_widgets.begin(); it != pro_widgets.end(); it++) {
        QJsonObject obj = (*it).toObject();

        RunConfig * conf = RunConfig::fromJson(obj);

        ProjectWidget * project_widget = w -> setupProjectPanel(conf);

        project_widget -> load(obj);
    }
}

void Dumper::saveProjectWidgets(IDEWindow * w, JsonObj & json) {
    QList<DockWidget *> dock_widgets = w -> findChildren<DockWidget *>();

    QJsonArray ar;

    for(QList<DockWidget *>::Iterator it = dock_widgets.begin(); it != dock_widgets.end(); it++) {
        ProjectWidget * project_widget = qobject_cast<ProjectWidget *>((*it) -> widget());

        if (project_widget) {
            QJsonObject obj = project_widget -> save();
            obj.insert(QLatin1String("header"), (*it) -> windowTitle());
            ar << obj;
        }
    }

    if (ar.size() > 0)
        json.insert(QLatin1String("pro_widgets"), ar);
}




QString Dumper::intArrToStr(const QList<int> & arr) {
    QString res;

    if (arr.isEmpty())
        return res;

    QList<int>::ConstIterator it = arr.constBegin();

    for(; it != arr.constEnd(); it++)
        res = res % "," % QString::number(*it);

    return res.mid(1);
}
QList<int> Dumper::strToIntArr(const QString & str) {
    QVector<QStringRef> parts = str.splitRef(',');
    QList<int> res;

    QVector<QStringRef>::ConstIterator it = parts.constBegin();

    for(; it != parts.constEnd(); it++)
        res.append((*it).toInt());

    return res;
}


void Dumper::load(IDEWindow * w, const QString & settings_filename) {
    QSettings settings(Dir::appPath(settings_filename), QSettings::IniFormat, w);

    QVariant data = settings.value(QLatin1String("data"));

    if (data.isValid()) {
        JsonObj obj = JsonObj::fromJsonStr(data.toString());

        loadTree(w, obj);
        loadProjectWidgets(w, obj);
        loadTabs(w, obj);
        loadConsoles(w, obj);
    }

    QVariant geometry_state = settings.value(QLatin1String("geometry"));
    if (geometry_state.isValid())
        w -> restoreGeometry(geometry_state.toByteArray());

//    ///////////////////////////////////////////////////////////
//    ///location correction (test needed)
//    ///////////////////////////////////////////////////////////
    locationCorrection(w);

    QVariant obj_state = settings.value(QLatin1String("state"));
    if (obj_state.isValid())
        w -> restoreState(obj_state.toByteArray());
    ///////////////////////////////////////////////////////////

//    if (settings.value(SETTINGS_WINDOW_MAXIMIZED_KEY).toBool()) {
//        QApplication::processEvents();
//        showMaximized();
//    }

    QVariant tree_state = settings.value(QLatin1String("tree_state"));
    if (tree_state.isValid()) {
        w -> tree -> restoreState(tree_state.toByteArray());
    }

    QVariant tree_pos = settings.value(QLatin1String("tree_pos"));
    if (tree_pos.isValid()) {
        QScrollBar * scroll = w -> tree -> verticalScrollBar();
        scroll -> setProperty("last_pos", tree_pos);
        scroll -> setProperty("qty", 1);

        connect(scroll, SIGNAL(rangeChanged(int,int)), this, SLOT(scrollRangeChanged(int,int)));
    }

    QVariant widgets_list_geom = settings.value(QLatin1String("widgets_list_geom"));
    if (widgets_list_geom.isValid())
        w -> widgets_list -> restoreGeometry(widgets_list_geom.toByteArray());

    QVariant widgets_list_state = settings.value(QLatin1String("widgets_list_state"));
    if (widgets_list_state.isValid())
        w -> widgets_list -> restoreState(widgets_list_state.toByteArray());

    QVariant active_editor_index = settings.value(QLatin1String("active_editor_index"));

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
    saveConsoles(w, obj);
    saveProjectWidgets(w, obj);

    settings.setValue(QLatin1String("data"), obj.toJsonStr());
    settings.setValue(QLatin1String("geometry"), w -> saveGeometry());
    settings.setValue(QLatin1String("state"), w -> saveState());
    settings.setValue(QLatin1String("tree_state"), w -> tree -> saveState());
    settings.setValue(QLatin1String("tree_pos"), w -> tree -> verticalScrollBar() -> value());

    settings.setValue(QLatin1String("widgets_list_state"), w -> widgets_list -> saveState());
    settings.setValue(QLatin1String("widgets_list_geom"), w -> widgets_list -> saveGeometry());
    settings.setValue(QLatin1String("active_editor_index"), w -> widgets_list -> indexOf(w -> active_editor));

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
