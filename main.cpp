#include "ide_window.h"
#include <QApplication>


// https://javascript-minifier.com/
// has api for online minify
// POST https://javascript-minifier.com/raw?input=...
// curl -X POST -s --data-urlencode 'input=console.log( 1 );' https://javascript-minifier.com/raw


//https://xdebug.org/docs/index.php?action=index // php debug


//https://www.rubyguides.com/2015/08/static-analysis-in-ruby/
//https://www.rubyguides.com/2017/01/spy-on-your-ruby-methods/

//test localhost
//https://dashboard.ngrok.com/get-started

// debug
//https://github.com/ruby-debug/ruby-debug-ide

//https://www.youtube.com/watch?v=K3gLlZm-m_8 // snippets logic

// all ROR files
// http://api.rubyonrails.org/panel/links.html
//https://github.com/rails/rails/tree/375a4143cf5caeb6159b338be824903edfd62836/activesupport/lib/active_support/core_ext

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


//String.methods //(All methods)
//String.public_methods //(All Public methods)
//String.private_methods //(All private methods)
//String.methods.sort //(All methods sorted)
//String.ancestors //(Hierarchy chain, useful for inspecting where methods are inherited from)
//String.methods.sort - Object.methods //(Methods particular to an object, not the ancestors)


//https://apidock.com/ruby/notes
//https://apidock.com/ruby/notes/good
//https://apidock.com/rails/notes
//https://apidock.com/rails/notes/good


//http://www.iconarchive.com/show/windows-8-icons-by-icons8.3.html

//https://stackoverflow.com/questions/16286064/customizing-scrollbar-over-qlistwidget
//http://www.qtcentre.org/threads/7134-QTreeWidget-Weights-Sorting


// QTextEdit: Как заполучить «универсальное» событие вставки символа?
//https://www.linux.org.ru/forum/development/12255845


//http://doc.qt.io/qt-5/qtwidgets-widgets-tooltips-example.html

// TODO:
// LOGING!
// DEBUG!
// catch all errors from rails - send it po the socket port of app and putput list of errors for developer
// build in converters:
//      JS <-> coffee
//      ERB <-> SLIM
//      ERB <-> HAML


// JAVASCRIPT

// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Language_Resources
// http://www.ecma-international.org/ecma-262/5.1/

// https://www.w3schools.com/jsref/jsref_obj_global.asp
// https://www.tutorialspoint.com/javascript/javascript_builtin_functions.htm
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects

// get all properties for object
// Object.getOwnPropertyNames(Math)

// only functions
// console.log(Object.getOwnPropertyNames(Math).filter(function (p) {
//return typeof Math[p] === 'function';
//}));


// https://books.goalkicker.com/

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

