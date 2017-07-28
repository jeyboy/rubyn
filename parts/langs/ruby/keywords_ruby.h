#ifndef KEYWORDS_RUBY_H
#define KEYWORDS_RUBY_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"

//https://ruby-doc.org
//http://www.rubymagic.org/posts/ruby-and-rails-reserved-words
//https://www.tutorialspoint.com/ruby/ruby_regular_expressions.htm



///// overloadable operators
// :: 	Constant resolution operator
// [ ] [ ]= 	Element reference, element set
// ** 	Exponentiation (raise to the power)
// ! ~ + - 	Not, complement, unary plus and minus (method names for the last two are +@ and -@)
// * / % 	Multiply, divide, and modulo
// + - 	Addition and subtraction
// >> << 	Right and left bitwise shift
// & 	Bitwise 'AND'
// ^ | 	Bitwise exclusive `OR' and regular `OR'
// <= < > >= 	Comparison operators
// <=> == === != =~ !~



class KeywordsRuby : public SingletonPtr<KeywordsRuby> {
    QHash<QByteArray, bool> keys;

    // $! // The last exception object raised. The exception object can also be accessed using => in rescue clause.
    // $@ // The stack backtrace for the last exception raised. The stack backtrace information can retrieved by Exception#backtrace method of the last exception.
    // $/ // The input record separator (newline by default). gets, readline, etc., take their input record separator as optional argument.
    // $\ // The output record separator (nil by default).
    // $, // The output separator between the arguments to print and Array#join (nil by default). You can specify separator explicitly to Array#join.
    // $; // The default separator for split (nil by default). You can specify separator explicitly for String#split.
    // $. // The number of the last line read from the current input file. Equivalent to ARGF.lineno.
    // $< // Synonym for ARGF.
    // $> // Synonym for $defout.
    // $0 // The name of the current Ruby program being executed.
    // $$ // The process pid of the current Ruby program being executed.
    // $? // The exit status of the last process terminated.
    // $: // Synonym for $LOAD_PATH.
    // $DEBUG // True if the -d or --debug command-line option is specified.
    // $defout // The destination output for print and printf ($stdout by default).
    // $F //  The variable that receives the output from split when -a is specified. This variable is set if the -a command-line option is specified along with the -p or -n option.
    // $FILENAME // The name of the file currently being read from ARGF. Equivalent to ARGF.filename.
    // $LOAD_PATH // An array holding the directories to be searched when loading files with the load and require methods.
    // $SAFE // The security level
    //    0 → No checks are performed on externally supplied (tainted) data. (default)
    //    1 → Potentially dangerous operations using tainted data are forbidden.
    //    2 → Potentially dangerous operations on processes and files are forbidden.
    //    3 → All newly created objects are considered tainted.
    //    4 → Modification of global data is forbidden.

    // $stdin // Standard input (STDIN by default).
    // $stdout // Standard output (STDOUT by default).
    // $stderr // Standard error (STDERR by default).
    // $VERBOSE // True if the -v, -w, or --verbose command-line option is specified.
    // $- x // The value of interpreter option -x (x=0, a, d, F, i, K, l, p, v). These options are listed below
    // $-0 // The value of interpreter option -x and alias of $/.
    // $-a // The value of interpreter option -x and true if option -a is set. Read-only.
    // $-d // The value of interpreter option -x and alias of $DEBUG
    // $-F // The value of interpreter option -x and alias of $;.
    // $-i // The value of interpreter option -x and in in-place-edit mode, holds the extension, otherwise nil. Can enable or disable in-place-edit mode.
    // $-I // The value of interpreter option -x and alias of $:.
    // $-l // The value of interpreter option -x and true if option -lis set. Read-only.
    // $-p // The value of interpreter option -x and true if option -pis set. Read-only.
    // $_ // The local variable, last string read by gets or readline in the current scope.
    // $~ // The local variable, MatchData relating to the last match. Regex#match method returns the last match information.
    // $ n ($1, $2, $3...) // The string matched in the nth group of the last pattern match. Equivalent to m[n], where m is a MatchData object.
    // $& // The string matched in the last pattern match. Equivalent to m[0], where m is a MatchData object.
    // $` // The string preceding the match in the last pattern match. Equivalent to m.pre_match, where m is a MatchData object.
    // $' // The string following the match in the last pattern match. Equivalent to m.post_match, where m is a MatchData object.
    // $+ // The string corresponding to the last successfully matched group in the last pattern match.


    KeywordsRuby() {
        keys.insert(QByteArrayLiteral("__ENCODING__"), true); // The script encoding of the current file
        keys.insert(QByteArrayLiteral("__LINE__"), true); // The line number of this keyword in the current file
        keys.insert(QByteArrayLiteral("__FILE__"), true); // The path to the current file.
        keys.insert(QByteArrayLiteral("__END__"), true); // Denotes the end of the regular source code section of a program file. Lines below __END__ will not be executed
        keys.insert(QByteArrayLiteral("__method__"), true); // Name of current method


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
        keys.insert(QByteArrayLiteral("proc"), true);
        keys.insert(QByteArrayLiteral("protected"), true);
        keys.insert(QByteArrayLiteral("public"), true);
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
    }
public:
    inline bool hasKey(const QByteArray & key) { return keys.contains(key); }
};

#endif // KEYWORDS_RUBY_H
