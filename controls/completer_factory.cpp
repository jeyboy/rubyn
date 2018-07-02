#include "completer_factory.h"

CompleterFactory::CompleterFactory() {
    icons.insert(lmt_unknow,                       QIcon(QLatin1Literal(":/completer/unknow")));
    icons.insert(lmt_const,                        QIcon(QLatin1Literal(":/completer/const")));
    icons.insert(lmt_private_const,                QIcon(QLatin1Literal(":/completer/private_const")));
    icons.insert(lmt_global_method,                QIcon(QLatin1Literal(":/completer/global_method")));
    icons.insert(lmt_global_var,                   QIcon(QLatin1Literal(":/completer/global_var")));
    icons.insert(lmt_private_instance_method,      QIcon(QLatin1Literal(":/completer/private_instance_method")));
    icons.insert(lmt_instance_method,              QIcon(QLatin1Literal(":/completer/instance_method")));
    icons.insert(lmt_instance_var,                 QIcon(QLatin1Literal(":/completer/instance_var")));
    icons.insert(lmt_local_var,                    QIcon(QLatin1Literal(":/completer/local_var")));
    icons.insert(lmt_private_obj_method,           QIcon(QLatin1Literal(":/completer/private_obj_method")));
    icons.insert(lmt_object_method,                   QIcon(QLatin1Literal(":/completer/obj_method")));
    icons.insert(lmt_object_var,                      QIcon(QLatin1Literal(":/completer/obj_var")));
    icons.insert(lmt_template,                     QIcon(QLatin1Literal(":/completer/template")));
}
