#ifndef RUN_CONFIG_H
#define RUN_CONFIG_H

#include <qregularexpression.h>
#include <qmap.h>
#include <qvariant.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

#include <qdebug.h>

#include "tools/process.h"

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


    uint id;
    QString name;
    QString work_dir;
    QString env;
    QString cmd;
    QStringList env_variables;
    QVariantMap run_params;
    CmdType cmd_type;

    QJsonObject toJson() {
        QJsonObject res;

        res.insert(QLatin1String("id"), double(id));
        res.insert(QLatin1String("name"), name);
        res.insert(QLatin1String("dir"), work_dir);
        res.insert(QLatin1String("type"), cmd_type);
        res.insert(QLatin1String("cmd"), cmd);

        if (!env.isEmpty()) {
            res.insert(QLatin1String("env"), env);
        }

        if (!env_variables.isEmpty()) {
            res.insert(QLatin1String("vars"), QJsonArray::fromStringList(env_variables));
        }

        if (!run_params.isEmpty()) {
            res.insert(QLatin1String("pars"), QJsonObject::fromVariantMap(run_params));
        }

        return res;
    }

    static RunConfig * fromJson(const QJsonObject & obj) {
        RunConfig * conf = new RunConfig(CmdType(obj.value(QLatin1String("type")).toInt()));

        conf -> id = obj.value("id").toDouble();
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
//        if (run_params.contains(QLatin1String("port"))) {
//            QString p = run_params[QLatin1String("port")];

//            if (!p.isEmpty())
//                return p.toInt();
//        }

//        return 3000;
//    }

    uint uid() { return id; }

    QString envName() {
        return env.isEmpty() ? "development" : env;
    }

    QString token() {
        return QString::number(cmd_type) + '|' + name.replace('|', '+') + '|' + envName() + '|' + work_dir;
    }

    QString runCmd() {
        return cmd.length() > 0 ? cmd : cmdConfigToCmd(cmd_type);
    }

    RunConfig(const CmdType & cmd_type) : cmd_type(cmd_type) {
//        cmd = cmdConfigToCmd(cmd_type);
    }


    QString wrapWithDebug(const QString & cmd) {
        return cmd;
    }

    QString cmdConfigToCmd(const CmdType & conf) {
        //   http://rusrails.ru/a-guide-to-the-rails-command-line#rails-server

        //    https://ss64.com/nt/cmd.html

        //    Syntax
        //          CMD [charset] [options]

        //          CMD [charset] [options] [/C Command]

        //          CMD [charset] [options] [/K Command]

        //    Options
        //       /C     Run Command and then terminate

        //       /K     Run Command and then return to the CMD prompt.
        //              This is useful for testing, to examine variables

        //       Command : The command, program or batch script to be run.
        //                 This can even be several commands separated with '&'
        //                 (the whole should also be surrounded by "quotes")

        //       /T:fg  Sets the foreground/background colours

        //       /A     Output ANSI characters
        //       /U     Output UNICODE characters (UCS-2 le)
        //              These options will affect piping or redirecting to a file.
        //              Most common text files are ANSI, use these switches
        //              when you need to convert the character set.

        //       /D     Ignore registry AutoRun commands
        //              HKLM | HKCU \Software\Microsoft\Command Processor\AutoRun

        //       /E:ON  Enable CMD Command Extensions (default)
        //       /X     Enable CMD Command Extensions (old switch for compatibility)
        //       /E:OFF Disable CMD Command Extensions
        //       /Y     Disable CMD Command Extensions (old switch for compatibility)

        //       /F:ON  Enable auto-completion of pathnames entered at the CMD prompt
        //       /F:OFF Disable auto-completion of pathnames entered at the CMD prompt (default)

        //            At the command prompt Ctrl-D gives folder name completion and Ctrl-F gives File and folder name completion.

        //            These key-strokes will display the first matching path. Thereafter, repeated pressing of the same control key will cycle through the list of matching paths. Pressing SHIFT with the control key will move through the list backwards.

        //       /Q    Turn echo off

        //       /S    Strip " quote characters from command.
        //             If command starts with a quote, the first and last quote chars in command
        //             will be removed, whether /s is specified or not.

        //       /V:ON Enable delayed environment variable expansion
        //             this allows a FOR loop to specify !variable! instead of %variable%
        //             expanding the variable at execution time instead of at input time.

        //       /V:OFF
        //             Disable delayed environment expansion.
        //             Delayed Environment expansion can also be set with SETLOCAL

        //    start("cmd.exe");




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

                #ifdef Q_OS_WIN
                    QString rails_path;
                    Process::getVal("cmd.exe /C \"where rails\"", rails_path);

                    QStringList paths = rails_path.split("\r\n");
                    int pos = -1, it_pos = 0;
                    QRegularExpression pattern("rails.bat", QRegularExpression::OptimizeOnFirstUsageOption | QRegularExpression::CaseInsensitiveOption);

                    for(QStringList::Iterator it = paths.begin(); it != paths.end(); it++, ++it_pos) {
                        if ((*it).indexOf(pattern) != -1) {
                            pos = it_pos;
                            break;
                        }
                    }

                    if (pos != -1) {
                        rails_path = paths.takeAt(pos);
                    } else {
                        rails_path = paths.takeFirst();
                    }

                    QString res = rails_path + " s -e " + envName();
//                    QString res = "cmd.exe /C \"cd /d " + work_dir + " && bundle exec rails s -e " + envName();

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

//                    return res;
                    return res + '"';
                #elif Q_OS_MAC
                    "";
                #else
                    "/bin/bash -c \"/home/jb/.rvm/bin/rvm ruby-2.4.5@monitorhealth do /home/jb/.rvm/rubies/ruby-2.4.5/bin/ruby /home/jb/.rvm/gems/ruby-2.4.5@monitorhealth/gems/ruby-debug-ide-0.8.0.beta24/bin/rdebug-ide --key-value --step-over-in-blocks --disable-int-handler --evaluation-timeout 10 --evaluation-control --time-limit 100 --memory-limit 0 --rubymine-protocol-extensions --port 35205 --host 0.0.0.0 --dispatcher-port 35567 -- /home/jb/projects/customer-monitorhealth-healthhub-server/bin/rails console -- --prompt simple\"";
                #endif
            }

            case rc_rails_console: {
                //  -e, [--environment=ENVIRONMENT]  # Specifies the environment to run this console under (test/development/production).
                //  -s, [--sandbox], [--no-sandbox]  # Rollback database modifications on exit.

                QString res = QLatin1String("bundle exec rails c -e ") + envName();

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
