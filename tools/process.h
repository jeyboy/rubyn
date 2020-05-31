#ifndef PROCESS_H
#define PROCESS_H

//http://doc.qt.io/qt-5/qprocess.html
//http://doc.qt.io/qt-5/qprocessenvironment.html#systemEnvironment

#include <qprocess.h>

class IProcessLogger;
class QTimer;

class Process : public QProcess {
    IProcessLogger * _logger;
    QTimer * _timer;
public:
    Process(QObject * parent = Q_NULLPTR);
    virtual ~Process();

    void bindOutput(IProcessLogger * logger);

    void proc(const QString & cmd);

    void stop();

    static bool getVal(const QString & cmd, QString & res);

    //    void setWorkingDirectory(const QString &dir);
    //    void setEnvironment(const QStringList &environment);

    //    void setStandardOutputFile(const QString &fileName, OpenMode mode = Truncate);
    //    void setStandardErrorFile(const QString &fileName, OpenMode mode = Truncate);
};

#endif // PROCESS_H
