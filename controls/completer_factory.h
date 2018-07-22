#ifndef COMPLETER_FACTORY_H
#define COMPLETER_FACTORY_H

#include <qhash.h>

#include "project/code_formats.h"
#include "lexer/obj_lexems.h"

#include "misc/singleton.h"

#include "controls/completer.h"

class CompleterFactory : public QObject, public Singleton<CompleterFactory> {
    Q_OBJECT

    QHash<ObjLexem, QIcon> icons;

    QHash<FormatType, Completer *> completers;

    CompleterFactory();

    void buildDataSet(const FormatType & format);
//    void loadDataSet(const FormatType & format);
//    void saveDataSet(const FormatType & format);
public:
    inline QIcon & ico(const ObjLexem & ico_type) { return icons[ico_type]; }

    friend class Singleton<CompleterFactory>;

signals:
    void dataSetReady(const FormatType & format, Completer * datum);
private slots:
    void dataSetBuildingReady(const FormatType & format, Completer * datum);
};

#endif // COMPLETER_FACTORY_H
