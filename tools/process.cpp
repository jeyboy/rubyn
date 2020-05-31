#include "process.h"

#include "loggers/iprocess_logger.h"

Process::Process(QObject * parent) : QProcess(parent) {
}

Process::~Process() {
    stop();
}

void Process::bindOutput(IProcessLogger * logger) {
    _logger = logger;

    if (_logger) {
        connect(this, &Process::errorOccurred, [=](const QProcess::ProcessError & /*error*/) {
            _logger -> printError(errorString());
        });

        connect(this, &Process::stateChanged, [=](const QProcess::ProcessState & state) {
            switch(state) {
                case QProcess::Starting: {
                    _logger -> printNotify(readLine());
                break;}

                case QProcess::Running: {
                    _logger -> printNotify(readLine());
                break;}

                default: {
    //                logger -> printNotify(readLine());
                }
            };
        });

        connect(this, &Process::readyReadStandardOutput, [=]() {
            setReadChannel(QProcess::StandardOutput);

            while(canReadLine()) {
                _logger -> printText(readLine());
            }
        });

        connect(this, &Process::readyReadStandardError, [=]() {
            setReadChannel(QProcess::StandardError);

            while(canReadLine()) {
                _logger -> printError(readLine());
            }
        });
    }
}

void Process::proc(const QString & cmd) {
    //    if (process -> state() == QProcess::NotRunning) {
    //        process -> start(cmd_path + '/' + cmd);

    _logger -> printNotify(workingDirectory());
    _logger -> printNotify("Run \"" + cmd + "\"");

    start(cmd);
}

void Process::stop() {
    if (state() == QProcess::Running) {
        terminate();
        waitForFinished(3000);

        if (state() == QProcess::Running) {
            kill();
            waitForFinished(3000);
        }
    }
}

bool Process::getVal(const QString & cmd, QString & res) {
    bool cmd_res = false;

    QProcess pr;
    pr.setReadChannel(QProcess::StandardOutput);

//    connect(&pr, &Process::readyReadStandardOutput, [&pr]() {
//        pr.setReadChannel(QProcess::StandardOutput);
//    });

//    connect(&pr, &Process::readyReadStandardError, [&pr]() {
//        pr.setReadChannel(QProcess::StandardError);
//    });

    pr.start(cmd);

    if (!pr.waitForStarted())
        return false;

    int steps = 0;
    int limit = 10;

    while(true) {
        if (++steps >= limit)
            break;

        if (pr.waitForReadyRead(25)) {
            cmd_res = true;
            break;
        }

        if (pr.state() != QProcess::Running) {
            break;
        }
    }

    res = pr.readAll();

    pr.waitForFinished(200);

    if (pr.state() == QProcess::Running) {
        pr.kill();
    }

    return cmd_res;
}
