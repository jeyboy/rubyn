#ifndef KEYWORDS_RUBY_H
#define KEYWORDS_RUBY_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"

//https://ruby-doc.org

class KeywordsRuby : public SingletonPtr<KeywordsRuby> {
    QHash<QByteArray, bool> keys;

    KeywordsRuby() {
        keys.insert(QByteArrayLiteral("__ENCODING__"), true); // The script encoding of the current file
        keys.insert(QByteArrayLiteral("__LINE__"), true); // The line number of this keyword in the current file
        keys.insert(QByteArrayLiteral("__FILE__"), true); // The path to the current file.
        keys.insert(QByteArrayLiteral("__END__"), true); // Denotes the end of the regular source code section of a program file. Lines below __END__ will not be executed

        keys.insert(QByteArrayLiteral("=begin"), true); // Start of multiline comment
        keys.insert(QByteArrayLiteral("=end"), true); // End of multiline comment

        keys.insert(QByteArrayLiteral("BEGIN"), true); // Runs before any other code in the current file
        keys.insert(QByteArrayLiteral("END"), true); // Runs after any other code in the current file

        keys.insert(QByteArrayLiteral("alias"), true); // Creates an alias between two methods (and other things)
        keys.insert(QByteArrayLiteral("and"), true); // Short-circuit Boolean and with lower precedence than &&

        keys.insert(QByteArrayLiteral("begin"), true); // Starts an exception handling block
        keys.insert(QByteArrayLiteral("break"), true); // Leaves a block early
        keys.insert(QByteArrayLiteral("case"), true); // Starts a case expression
        keys.insert(QByteArrayLiteral("class"), true); // Creates or opens a class
        keys.insert(QByteArrayLiteral("def"), true); // Defines a method
        keys.insert(QByteArrayLiteral("defined?"), true); // Returns a string describing its argument
        keys.insert(QByteArrayLiteral("do"), true); // Starts a block
        keys.insert(QByteArrayLiteral("else"), true); // The unhandled condition in case, if and unless expressions
        keys.insert(QByteArrayLiteral("elsif"), true); // An alternate condition for an if expression
        keys.insert(QByteArrayLiteral("end"), true); // The end of a syntax block. Used by classes, modules, methods, exception handling and control expressions
        keys.insert(QByteArrayLiteral("ensure"), true); // Starts a section of code that is always run when an exception is raised
        keys.insert(QByteArrayLiteral("extend"), true);
        keys.insert(QByteArrayLiteral("false"), true); // Boolean false
        keys.insert(QByteArrayLiteral("for"), true); // A loop that is similar to using the each method
        keys.insert(QByteArrayLiteral("if"), true); // Used for if and modifier if expressions
        keys.insert(QByteArrayLiteral("in"), true); // Used to separate the iterable object and iterator variable in a for loop
        keys.insert(QByteArrayLiteral("include"), true);
        keys.insert(QByteArrayLiteral("lambda"), true);
        keys.insert(QByteArrayLiteral("module"), true); // Creates or opens a module
        keys.insert(QByteArrayLiteral("next"), true); // Skips the rest of the block
        keys.insert(QByteArrayLiteral("new"), true);
        keys.insert(QByteArrayLiteral("nil"), true); // A false value usually indicating “no value” or “unknown”
        keys.insert(QByteArrayLiteral("not"), true); // Inverts the following boolean expression
        keys.insert(QByteArrayLiteral("or"), true); // Boolean or with lower precedence than ||
        keys.insert(QByteArrayLiteral("private"), true);
        keys.insert(QByteArrayLiteral("protected"), true);
        keys.insert(QByteArrayLiteral("raise"), true);
        keys.insert(QByteArrayLiteral("redo"), true); // Restarts execution in the current block
        keys.insert(QByteArrayLiteral("require"), true);
        keys.insert(QByteArrayLiteral("rescue"), true); // Starts an exception section of code in a begin block
        keys.insert(QByteArrayLiteral("retry"), true); // Retries an exception block
        keys.insert(QByteArrayLiteral("return"), true); // Exits a method
        keys.insert(QByteArrayLiteral("self"), true); // The object the current method is attached to
        keys.insert(QByteArrayLiteral("super"), true); // Calls the current method in a superclass
        keys.insert(QByteArrayLiteral("then"), true); // Indicates the end of conditional blocks in control structures
        keys.insert(QByteArrayLiteral("true"), true); // Boolean true
        keys.insert(QByteArrayLiteral("undef"), true); // Prevents a class or module from responding to a method call
        keys.insert(QByteArrayLiteral("unless"), true); // Used for unless and modifier unless expressions
        keys.insert(QByteArrayLiteral("until"), true); // Creates a loop that executes until the condition is true
        keys.insert(QByteArrayLiteral("when"), true); // A condition in a case expression
        keys.insert(QByteArrayLiteral("while"), true); // Creates a loop that executes while the condition is true
        keys.insert(QByteArrayLiteral("yield"), true); // Starts execution of the block sent to the current method



//        keys.insert(QByteArrayLiteral("attr"), true);
//        keys.insert(QByteArrayLiteral("attr_accessor"), true);
//        keys.insert(QByteArrayLiteral("attr_reader"), true);
//        keys.insert(QByteArrayLiteral("attr_writer"), true);

        keys.insert(QByteArrayLiteral("proc"), true);
    }
public:
    inline bool hasKey(const QByteArray & key) { return keys.contains(key); }
};

#endif // KEYWORDS_RUBY_H
