#ifndef RUN_CONFIG_H
#define RUN_CONFIG_H

#include <qstring.h>
#include <qstringlist.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

struct RunConfig {
    enum CmdType : int {
        rc_none = 0,
        rc_debug = 1,
        rc_rails_server = 2,
        rc_rails_console = 4,

        rc_custom = 8,

        rc_rails_server_debug = rc_debug | rc_rails_server,
        rc_rails_console_debug = rc_debug | rc_rails_console,

        rc_custom_debug = rc_custom | rc_rails_console
    };


    QString name;
    QString work_dir;
    QString env;
    QString custom_cmd;
    QStringList env_variables;
    int port;
    CmdType cmd_type;

    QJsonObject toJson() {
        QJsonObject res;

        res.insert(QLatin1Literal("name"), name);
        res.insert(QLatin1Literal("dir"), work_dir);
        res.insert(QLatin1Literal("env"), env);
        res.insert(QLatin1Literal("type"), cmd_type);
        res.insert(QLatin1Literal("port"), port);


        if (!env_variables.isEmpty()) {
            res.insert(QLatin1Literal("vars"), QJsonArray::fromStringList(env_variables));
        }

        if (!custom_cmd.isEmpty()) {
            res.insert(QLatin1Literal("custom"), custom_cmd);
        }

        return res;
    }

    static RunConfig * fromJson(const QJsonObject & obj) {
        RunConfig * conf = new RunConfig(CmdType(obj.value(QLatin1Literal("type")).toInt()));

        conf -> name = obj.value("name").toString();
        conf -> work_dir = obj.value("dir").toString();
        conf -> env = obj.value("env").toString();
        conf -> port = obj.value("port").toInt();

        if (obj.contains("custom")) {
            conf -> custom_cmd = obj.value("custom").toString();
        }

        if (obj.contains("vars")) {
            QJsonArray arr = obj.value("vars").toArray();

            for(QJsonArray::Iterator it = arr.begin(); it != arr.end(); it++) {
                conf -> custom_cmd.append((*it).toString());
            }
        }

        return conf;
    }

    QString token() {
        return QString::number(cmd_type) + '|' + name.replace('|', '+') + '|' + env;
    }

    RunConfig(const CmdType & cmd_type) : port(3000), cmd_type(cmd_type) {

    }


    QString wrapWithDebug(const QString & cmd) {
        return cmd;
    }

    QString cmdConfigToCmd(const CmdType & conf) {
        switch(conf) {
            case rc_rails_server: {

            }

            case rc_rails_console: {

            }

            case rc_rails_server_debug:
            case rc_rails_console_debug: { return wrapWithDebug(cmdConfigToCmd(CmdType(conf ^ rc_debug))); }

            default: { return QString(); }
        }
    }
};

#endif // RUN_CONFIG_H
