#include "ide_window.h"
#include <QApplication>

// get ruby version
// ruby --version

//http://www.chrisrolle.com/en/blog/private-classes-in-ruby


//class Person
//  RETIREMENT_AGE = 68
//  ADULT_AGE      = 18
//  private_constant :ADULT_AGE
//end

// List of public constants
// Person.constants

// List of public and private constants
// Person.constants false

// Liat of all classes
// ObjectSpace.each_object(Class) { |c| p c.name }
// ObjectSpace.each_object(Module) { |c| p c.name }

// List of common methods
// Kernel.methods

// List of global variables
// Kernel.global_variables

// IO.new.methods(false) // take only this class methods
// "asdasda".method(:to_s).parameters // return list of requred parameters
// "asdasda".method(:to_s).arity // return count of required parameters
// http://codeloveandboards.com/blog/2014/02/05/ruby-and-method-arguments/
// https://holgerjust.de/2016/detecting-default-arguments-in-ruby/
// https://www.oreilly.com/learning/ruby-cookbook-modules-and-namespaces

// take list of extends
// String.singleton_class.included_modules


//https://apidock.com/ruby/notes
//https://apidock.com/ruby/notes/good
//https://apidock.com/rails/notes
//https://apidock.com/rails/notes/good


//http://www.iconarchive.com/show/windows-8-icons-by-icons8.3.html

//https://stackoverflow.com/questions/16286064/customizing-scrollbar-over-qlistwidget
//http://www.qtcentre.org/threads/7134-QTreeWidget-Weights-Sorting


// QTextEdit: Как заполучить «универсальное» событие вставки символа?
//https://www.linux.org.ru/forum/development/12255845


//http://doc.qt.io/qt-5/qprocess.html
//http://doc.qt.io/qt-5/qprocessenvironment.html#systemEnvironment



// TODO:
// LOGING!
// DEBUG!
// catch all errors from rails - send it po the socket port of app and putput list of errors for developer
// build in converters:
//      JS <-> coffee
//      ERB <-> SLIM
//      ERB <-> HAML



//completer icons:
// - add template: green round - inside right arrow // t
//      example: "def method_name; end" and etc...

// - local variable: var // #
// - instance variable: @var // @
// - class variable: @@var // @@
// - global variable: #var // $

// - module constant // (C)
// - module 'member' method // (member)
// - module 'self' method // (self)
// - class constant // <C>
// - class instance method // <instance>
// - class self method // <self>



int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    IDEWindow w;
    w.show();

    return a.exec();
}

//QString Get::osName()
//{
//#if defined(Q_OS_ANDROID)
//return QLatin1String("android");
//#elif defined(Q_OS_BLACKBERRY)
//return QLatin1String("blackberry");
//#elif defined(Q_OS_IOS)
//return QLatin1String("ios");
//#elif defined(Q_OS_MACOS)
//return QLatin1String("macos");
//#elif defined(Q_OS_TVOS)
//return QLatin1String("tvos");
//#elif defined(Q_OS_WATCHOS)
//return QLatin1String("watchos");
//#elif defined(Q_OS_WINCE)
//return QLatin1String("wince");
//#elif defined(Q_OS_WIN)
//return QLatin1String("windows");
//#elif defined(Q_OS_LINUX)
//return QLatin1String("linux");
//#elif defined(Q_OS_UNIX)
//return QLatin1String("unix");
//#else
//return QLatin1String("unknown");
//#endif
//}

//If single required

//#ifdef Q_OS_LINUX
//return QString::fromLatin1(DATADIR"/"APPLICATION_EXECUTABLE"/i18n/");
//#endif
//#ifdef Q_OS_MACOS
//return QApplication::applicationDirPath()+QLatin1String("/../Resources/translations"); // path defaults to app dir.
//#endif
//#ifdef Q_OS_DARWIN
//return QApplication::applicationDirPath()+QLatin1String("/translations"); // path defaults to app dir.
//#endif
//#ifdef Q_OS_WIN
//return QApplication::applicationDirPath();
//#endif

