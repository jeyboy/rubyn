#include "ide_window.h"
#include <QApplication>

//http://www.iconarchive.com/show/windows-8-icons-by-icons8.3.html

// TODO:
// LOGING!
// DEBUG!
// catch all errors from rails - send it po the socket port of app and putput list of errors for developer

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IDEWindow w;
    w.show();

    return a.exec();
}
