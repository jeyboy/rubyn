#ifndef RUN_CONFIG_H
#define RUN_CONFIG_H

#include <qstring.h>

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
