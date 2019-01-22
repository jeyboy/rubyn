#ifndef PROCESS_H
#define PROCESS_H

//http://doc.qt.io/qt-5/qprocess.html
//http://doc.qt.io/qt-5/qprocessenvironment.html#systemEnvironment

#include <qprocess.h>

class Process : public QProcess {
public:
    Process(QObject * parent = Q_NULLPTR);
};

#endif // PROCESS_H
