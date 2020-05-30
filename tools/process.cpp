#include "process.h"

#include "loggers/iprocess_logger.h"

Process::Process(QObject * parent) : QProcess(parent) {
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
