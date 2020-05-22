#ifndef RUN_CONFIG_H
#define RUN_CONFIG_H

#include <qmap.h>
#include <qvariant.h>
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
    QString cmd;
    QStringList env_variables;
    QVariantMap run_params;
    CmdType cmd_type;

    QJsonObject toJson() {
        QJsonObject res;

        res.insert(QLatin1Literal("name"), name);
        res.insert(QLatin1Literal("dir"), work_dir);
        res.insert(QLatin1Literal("type"), cmd_type);
        res.insert(QLatin1Literal("cmd"), cmd);

        if (!env.isEmpty()) {
            res.insert(QLatin1Literal("env"), env);
        }

        if (!env_variables.isEmpty()) {
            res.insert(QLatin1Literal("vars"), QJsonArray::fromStringList(env_variables));
        }

        if (!run_params.isEmpty()) {
            res.insert(QLatin1Literal("pars"), QJsonObject::fromVariantMap(run_params));
        }

        return res;
    }

    static RunConfig * fromJson(const QJsonObject & obj) {
        RunConfig * conf = new RunConfig(CmdType(obj.value(QLatin1Literal("type")).toInt()));

        conf -> name = obj.value("name").toString();
        conf -> work_dir = obj.value("dir").toString();
        conf -> env = obj.value("env").toString();
        conf -> cmd = obj.value("cmd").toString();

        if (obj.contains("vars")) {
            QJsonArray arr = obj.value("vars").toArray();

            for(QJsonArray::Iterator it = arr.begin(); it != arr.end(); it++) {
                conf -> env_variables.append((*it).toString());
            }
        }

        if (obj.contains("pars")) {
            conf -> run_params = obj.value("pars").toObject().toVariantMap();
        }

        return conf;
    }


//    int port() {
//        if (run_params.contains(QLatin1Literal("port"))) {
//            QString p = run_params[QLatin1Literal("port")];

//            if (!p.isEmpty())
//                return p.toInt();
//        }

//        return 3000;
//    }

    QString envName() {
        return env.isEmpty() ? "development" : env;
    }

    QString token() {
        return QString::number(cmd_type) + '|' + name.replace('|', '+') + '|' + envName() + '|' + work_dir;
    }

    RunConfig(const CmdType & cmd_type) : cmd_type(cmd_type) {
        cmd = cmdConfigToCmd(cmd_type);
    }


    QString wrapWithDebug(const QString & cmd) {
        return cmd;
    }

    QString cmdConfigToCmd(const CmdType & conf) {
//        http://rusrails.ru/a-guide-to-the-rails-command-line#rails-server

        switch(conf) {
            case rc_rails_server: {
                //  -e, [--environment=ENVIRONMENT]              # Specifies the environment to run this server under (test/development/production).
                //  -p, [--port=port]                            # Runs Rails on the specified port - defaults to 3000.
                //  -b, [--binding=IP]                           # Binds Rails to the specified IP - defaults to 'localhost' in development and '0.0.0.0' in other environments'.
                //  -c, [--config=file]                          # Uses a custom rackup configuration.
                //                                               # Default: config.ru
                //  -d, [--daemon], [--no-daemon]                # Runs server as a Daemon.
                //  -u, [--using=name]                           # Specifies the Rack server used to run the application (thin/puma/webrick).
                //  -P, [--pid=PID]                              # Specifies the PID file.
                //                                               # Default: tmp/pids/server.pid
                //  -C, [--dev-caching], [--no-dev-caching]      # Specifies whether to perform caching in development.
                //      [--early-hints], [--no-early-hints]      # Enables HTTP/2 early hints.
                //      [--log-to-stdout], [--no-log-to-stdout]  # Whether to log to stdout. Enabled by default in development when not daemonized.

                QString res = QLatin1Literal("bundle exec rails s -e ") + envName();

                QVariantMap::Iterator it = run_params.begin();

                for(; it != run_params.end(); it++) {
                    QString val = it.value().toString();

                    if (it.key().startsWith("--")) {
                        if (val.isEmpty()) {
                            res += " " + it.key();
                        } else {
                            res += " " + it.key() + '=' + val;
                        }

                    } else if (it.key().startsWith('-')) {
                        res += " " + it.key() + ' ' + val;
                    }
                }

                return res;
            }

            case rc_rails_console: {
                //  -e, [--environment=ENVIRONMENT]  # Specifies the environment to run this console under (test/development/production).
                //  -s, [--sandbox], [--no-sandbox]  # Rollback database modifications on exit.

                QString res = QLatin1Literal("bundle exec rails c -e ") + envName();

                QVariantMap::Iterator it = run_params.begin();

                for(; it != run_params.end(); it++) {
                    QString val = it.value().toString();

                    if (it.key().startsWith("--")) {
                        if (val.isEmpty()) {
                            res += " " + it.key();
                        } else {
                            res += " " + it.key() + '=' + val;
                        }

                    } else if (it.key().startsWith('-')) {
                        res += " " + it.key() + ' ' + val;
                    }
                }

                return res;
            }

            case rc_rails_server_debug:
            case rc_rails_console_debug: { return wrapWithDebug(cmdConfigToCmd(CmdType(conf ^ rc_debug))); }

            default: { return QString(); }
        }
    }
};

#endif // RUN_CONFIG_H
