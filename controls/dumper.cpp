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

void Dumper::loadTree(IDEWindow * w, JsonObj & json) {
    JsonArr arr = json.arr(QLatin1Literal("tree"));

    if (!arr.isEmpty()) {
        for(JsonArr::Iterator it = arr.begin(); it != arr.end(); it++)
            w -> openFolder(QUrl::fromLocalFile((*it).toString()));
    }
}

void Dumper::saveTree(IDEWindow * w, JsonObj & json) {
    QTreeWidgetItem * top = w -> tree -> topLevelItem(0);

    JsonArr arr;

    for(int i = 0; i < top -> childCount(); i++) {
        QTreeWidgetItem * child = top -> child(i);

        QVariant data = child -> data(0, Qt::UserRole);

        if (data.isNull()) {
            Logger::obj().write(QLatin1Literal("Dumper"), QLatin1Literal("Cant save project: ") % child -> text(0));
        }
        else {
            IFolder * folder = VariantPtr<IFolder>::asPtr(data);
            arr.append(folder -> fullPath());
        }
    }

    json.insert(QLatin1Literal("tree"), arr);
}

void Dumper::loadTabs(IDEWindow * w, JsonObj & json) {
    int index = w -> widgets_list -> indexOf(w -> active_editor);

    JsonArr arr;

    for(int i = 0; i < w -> widgets_list -> count(); i++) {
        JsonObj widget_obj;
        JsonArr tabs_arr;

        QWidget * widget =w ->  widgets_list -> widget(index);
        TabsBlock * editor = dynamic_cast<TabsBlock *>(widget);


    }
}

void Dumper::saveTabs(IDEWindow * w, JsonObj & json) {

}

void Dumper::load(IDEWindow * w, const QString & settings_filename) {
    QSettings settings(Dir::appPath(settings_filename), QSettings::IniFormat, w);

//    QVariant data = settings.value(QLatin1Literal("data"));

//    if (data.isValid()) {
//        JsonObj obj(data.toJsonObject());

//        loadTree(w, obj);
//    }

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
}

void Dumper::save(IDEWindow * w, const QString & settings_filename) {
    QSettings settings(Dir::appPath(settings_filename), QSettings::IniFormat, w);

    JsonObj obj;

    saveTree(w, obj);
    saveTabs(w, obj);

    settings.setValue(QLatin1Literal("data"), obj.toJsonStr());
    settings.setValue(QLatin1Literal("geometry"), w -> saveGeometry());
    settings.setValue(QLatin1Literal("state"), w -> saveState());
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
