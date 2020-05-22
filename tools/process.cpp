#include "process.h"

#include "loggers/iprocess_logger.h"

Process::Process(QObject * parent) : QProcess(parent) {

}

void Process::bindOutput(IProcessLogger * logger) {
    _logger = logger;

//    connect(this, &Process::started, [=]() {

//    });

    connect(this, &Process::errorOccurred, [=](const QProcess::ProcessError & /*error*/) {
        logger -> printError(errorString());
    });

    connect(this, &Process::stateChanged, [=](const QProcess::ProcessState & state) {
        switch(state) {
            case QProcess::Starting: {
                logger -> printNotify(readLine());
            break;}

            case QProcess::Running: {
                logger -> printNotify(readLine());
            break;}

            default: {
//                logger -> printNotify(readLine());
            }
        };
    });

    connect(this, &Process::readyReadStandardOutput, [=]() {
        setReadChannel(QProcess::StandardOutput);

        while(canReadLine()) {
            logger -> printText(readLine());
        }
    });

    connect(this, &Process::readyReadStandardError, [=]() {
        setReadChannel(QProcess::StandardError);

        while(canReadLine()) {
            logger -> printError(readLine());
        }
    });
}

void Process::proc(const QString & cmd) {
    //    if (process -> state() == QProcess::NotRunning) {
    //        process -> start(cmd_path + '/' + cmd);

    _logger -> printNotify(workingDirectory());
    _logger -> printNotify("Run \"" + cmd + "\"");

    start(cmd);
}
