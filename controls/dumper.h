#ifndef DUMPER_H
#define DUMPER_H

#include <qobject.h>
#include <qstring.h>

class IDEWindow;
class JsonObj;
class QSplitter;
class TabsBlock;

class Dumper : public QObject {
    Q_OBJECT

    void loadTree(IDEWindow * w, JsonObj & json);
    void saveTree(IDEWindow * w, JsonObj & json);

    void loadTabs(IDEWindow * w, JsonObj & json);
    void saveTabs(IDEWindow * w, JsonObj & json);
    void saveTab(TabsBlock * editor, QJsonObject & widget_obj);
    void saveSplitter(QSplitter * list, QJsonObject & obj);
    void loadSplitter(IDEWindow * w, QSplitter * list, QJsonObject & obj);
public:
    void load(IDEWindow * w, const QString & settings_filename = QString("fsettings"));
    void save(IDEWindow * w, const QString & settings_filename = QString("fsettings"));
    void locationCorrection(IDEWindow * w);
private slots:
    void scrollRangeChanged(int min, int max);
};

#endif // DUMPER_H
