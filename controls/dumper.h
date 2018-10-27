#ifndef DUMPER_H
#define DUMPER_H

#include <qobject.h>
#include <qstring.h>

class IDEWindow;
class JsonObj;

class Dumper : public QObject {
    Q_OBJECT

    void loadTree(IDEWindow * w, JsonObj & json);
    void saveTree(IDEWindow * w, JsonObj & json);

    void loadTabs(IDEWindow * w, JsonObj & json);
    void saveTabs(IDEWindow * w, JsonObj & json);
public:
    void load(IDEWindow * w, const QString & settings_filename = QString("fsettings"));
    void save(IDEWindow * w, const QString & settings_filename = QString("fsettings"));
    void locationCorrection(IDEWindow * w);
private slots:
    void treeRangeChanged(int min, int max);
};

#endif // DUMPER_H
