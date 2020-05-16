#ifndef RUN_CONFIG_H
#define RUN_CONFIG_H

enum RunConfig : int {
    rc_none = 0,
    rc_debug = 1,
    rc_server = 2,
    rc_console = 4,

    rc_server_debug = rc_debug | rc_server,
    rc_console_debug = rc_debug | rc_console,
};

#endif // RUN_CONFIG_H
