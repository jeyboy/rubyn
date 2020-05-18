#ifndef RUN_CONFIG_H
#define RUN_CONFIG_H

#include <qstring.h>
#include <qstringlist.h>

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

    QString token() {
        return QString::number(cmd_type) + '|' + name.replace('|', '+') + '|' + work_dir + '|' + ;
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
