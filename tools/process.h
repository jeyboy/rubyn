#ifndef PROCESS_H
#define PROCESS_H

//http://doc.qt.io/qt-5/qprocess.html
//http://doc.qt.io/qt-5/qprocessenvironment.html#systemEnvironment

#include <qprocess.h>

class IProcessLogger;

class Process : public QProcess {

public:
    Process(QObject * parent = Q_NULLPTR);

    void bindOutput(IProcessLogger * logger);

    void proc(const QString & cmd);

    //    void setWorkingDirectory(const QString &dir);
    //    void setEnvironment(const QStringList &environment);

    //    if (process -> state() == QProcess::NotRunning) {
    //        process -> start(cmd_path + '/' + cmd);

//    void setStandardOutputFile(const QString &fileName, OpenMode mode = Truncate);
//    void setStandardErrorFile(const QString &fileName, OpenMode mode = Truncate);
};

#endif // PROCESS_H
