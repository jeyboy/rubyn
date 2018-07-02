#ifndef DUMPER_H
#define DUMPER_H

#include <qstring.h>

class IDEWindow;
class JsonObj;

class Dumper {
    static void loadTree(IDEWindow * w, JsonObj & json);
    static void saveTree(IDEWindow * w, JsonObj & json);

    static void loadTabs(IDEWindow * w, JsonObj & json);
    static void saveTabs(IDEWindow * w, JsonObj & json);
public:
    static void load(IDEWindow * w, const QString & settings_filename = QString("fsettings"));
    static void save(IDEWindow * w, const QString & settings_filename = QString("fsettings"));
    static void locationCorrection(IDEWindow * w);
};

#endif // DUMPER_H
