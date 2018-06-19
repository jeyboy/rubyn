#include "ide_window.h"
#include <QApplication>

//docs
//https://ruby-doc.org/downloads/
//https://www.jstorimer.com/blogs/workingwithcode/7766081-5-reasons-you-should-use-ri-to-read-ruby-documentation
//http://api.rubyonrails.org/

//http://www.iconarchive.com/show/windows-8-icons-by-icons8.3.html

//https://stackoverflow.com/questions/16286064/customizing-scrollbar-over-qlistwidget
//http://www.qtcentre.org/threads/7134-QTreeWidget-Weights-Sorting


// QTextEdit: Как заполучить «универсальное» событие вставки символа?
//https://www.linux.org.ru/forum/development/12255845


// get ruby version
// ruby --version

// Liat of all classes
// ObjectSpace.each_object(Class) { |c| p c.name }
// ObjectSpace.each_object(Module) { |c| p c.name }

// List of common methods
// Kernel.methods

// List of global variables
// Kernel.global_variables



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
