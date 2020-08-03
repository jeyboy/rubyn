#include "completer_factory.h"

#include "misc/dir.h"

CompleterFactory::CompleterFactory() {
    icons.insert(lmt_unknow,                       QIcon(QLatin1String(":/completer/unknow")));
    icons.insert(lmt_const,                        QIcon(QLatin1String(":/completer/const")));
    icons.insert(lmt_private_const,                QIcon(QLatin1String(":/completer/private_const")));
    icons.insert(lmt_global_method,                QIcon(QLatin1String(":/completer/global_method")));
    icons.insert(lmt_global_var,                   QIcon(QLatin1String(":/completer/global_var")));
    icons.insert(lmt_private_instance_method,      QIcon(QLatin1String(":/completer/private_instance_method")));
    icons.insert(lmt_instance_method,              QIcon(QLatin1String(":/completer/instance_method")));
    icons.insert(lmt_instance_var,                 QIcon(QLatin1String(":/completer/instance_var")));
    icons.insert(lmt_local_var,                    QIcon(QLatin1String(":/completer/local_var")));
    icons.insert(lmt_private_obj_method,           QIcon(QLatin1String(":/completer/private_obj_method")));
    icons.insert(lmt_object_method,                QIcon(QLatin1String(":/completer/obj_method")));
    icons.insert(lmt_object_var,                   QIcon(QLatin1String(":/completer/obj_var")));
    icons.insert(lmt_class,                        QIcon(QLatin1String(":/completer/class")));
    icons.insert(lmt_module,                       QIcon(QLatin1String(":/completer/module")));
    icons.insert(lmt_template,                     QIcon(QLatin1String(":/completer/template")));
}

void CompleterFactory::buildDataSet(const FormatType & format) {

}


void CompleterFactory::dataSetBuildingReady(const FormatType & format, Completer * datum) {

}
