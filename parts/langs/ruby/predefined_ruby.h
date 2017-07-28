#ifndef PREDEFINED_RUBY_H
#define PREDEFINED_RUBY_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"

class PredefinedRuby : public SingletonPtr<PredefinedRuby> {
    QHash<QByteArray, bool> keys;

    PredefinedRuby() {
        keys.insert(QByteArrayLiteral("TRUE"), true); // Synonym for true
        keys.insert(QByteArrayLiteral("FALSE"), true); // Synonym for false
        keys.insert(QByteArrayLiteral("NIL"), true); // Synonym for nil
        keys.insert(QByteArrayLiteral("ARGF"), true); // An object providing access to virtual concatenation of files passed as command-line arguments or standard input if there are no command-line arguments. A synonym for $<
        keys.insert(QByteArrayLiteral("ARGV"), true); // An array containing the command-line arguments passed to the program. A synonym for $*
        keys.insert(QByteArrayLiteral("DATA"), true); // An input stream for reading the lines of code following the __END__ directive. Not defined if __END__ isn't present in code.
        keys.insert(QByteArrayLiteral("ENV"), true); // A hash-like object containing the program's environment variables. ENV can be handled as a hash
        keys.insert(QByteArrayLiteral("RUBY_PLATFORM"), true); // A string indicating the platform of the Ruby interpreter.
        keys.insert(QByteArrayLiteral("RUBY_RELEASE_DATE"), true); // A string indicating the release date of the Ruby interpreter
        keys.insert(QByteArrayLiteral("RUBY_VERSION"), true); // A string indicating the version of the Ruby interpreter
        keys.insert(QByteArrayLiteral("STDERR"), true); // Standard error output stream. Default value of $stderr
        keys.insert(QByteArrayLiteral("STDIN"), true); // Standard input stream. Default value of $stdin
        keys.insert(QByteArrayLiteral("STDOUT"), true); // Standard output stream. Default value of $stdout
        keys.insert(QByteArrayLiteral("TOPLEVEL_BINDING"), true); // A binding object at Ruby's top level.

        keys.insert(QByteArrayLiteral("$!"), true); // The last exception object raised. The exception object can also be accessed using => in rescue clause.
        keys.insert(QByteArrayLiteral("$@"), true); // The stack backtrace for the last exception raised. The stack backtrace information can retrieved by Exception#backtrace method of the last exception.
        keys.insert(QByteArrayLiteral("$/"), true); // The input record separator (newline by default). gets, readline, etc., take their input record separator as optional argument.
        keys.insert(QByteArrayLiteral("$\\"), true); // The output record separator (nil by default).
        keys.insert(QByteArrayLiteral("$,"), true); // The output separator between the arguments to print and Array#join (nil by default). You can specify separator explicitly to Array#join.
        keys.insert(QByteArrayLiteral("$;"), true); // The default separator for split (nil by default). You can specify separator explicitly for String#split.
        keys.insert(QByteArrayLiteral("$."), true); // The number of the last line read from the current input file. Equivalent to ARGF.lineno.
        keys.insert(QByteArrayLiteral("$<"), true); // Synonym for ARGF.
        keys.insert(QByteArrayLiteral("$>"), true); // Synonym for $defout.
        keys.insert(QByteArrayLiteral("$0"), true); // The name of the current Ruby program being executed.

        keys.insert(QByteArrayLiteral("$$"), true); // The process pid of the current Ruby program being executed.
        keys.insert(QByteArrayLiteral("$?"), true); // The exit status of the last process terminated.
        keys.insert(QByteArrayLiteral("$:"), true); // Synonym for $LOAD_PATH.
        keys.insert(QByteArrayLiteral("$DEBUG"), true); // True if the -d or --debug command-line option is specified.
        keys.insert(QByteArrayLiteral("$defout"), true); // The destination output for print and printf ($stdout by default).
        keys.insert(QByteArrayLiteral("$F"), true); // The variable that receives the output from split when -a is specified. This variable is set if the -a command-line option is specified along with the -p or -n option.
        keys.insert(QByteArrayLiteral("$FILENAME"), true); // The name of the file currently being read from ARGF. Equivalent to ARGF.filename.
        keys.insert(QByteArrayLiteral("$LOAD_PATH"), true); // An array holding the directories to be searched when loading files with the load and require methods.
        keys.insert(QByteArrayLiteral("$SAFE"), true); // The security level
        //    0 → No checks are performed on externally supplied (tainted) data. (default)
        //    1 → Potentially dangerous operations using tainted data are forbidden.
        //    2 → Potentially dangerous operations on processes and files are forbidden.
        //    3 → All newly created objects are considered tainted.
        //    4 → Modification of global data is forbidden.

        keys.insert(QByteArrayLiteral("$stdin"), true); // Standard input (STDIN by default).
        keys.insert(QByteArrayLiteral("$stdout"), true); // Standard output (STDOUT by default).
        keys.insert(QByteArrayLiteral("$stderr"), true); // Standard error (STDERR by default).
        keys.insert(QByteArrayLiteral("$VERBOSE"), true); // True if the -v, -w, or --verbose command-line option is specified.

        // $- x // The value of interpreter option -x (x=0, a, d, F, i, K, l, p, v). These options are listed below
        keys.insert(QByteArrayLiteral("$-0"), true); // The value of interpreter option -x and alias of $/.
        keys.insert(QByteArrayLiteral("$-a"), true); // The value of interpreter option -x and true if option -a is set. Read-only.
        keys.insert(QByteArrayLiteral("$-d"), true); // The value of interpreter option -x and alias of $DEBUG
        keys.insert(QByteArrayLiteral("$-F"), true); // The value of interpreter option -x and alias of $;.
        keys.insert(QByteArrayLiteral("$-i"), true); // The value of interpreter option -x and in in-place-edit mode, holds the extension, otherwise nil. Can enable or disable in-place-edit mode.
        keys.insert(QByteArrayLiteral("$-K"), true); // The value of interpreter option -x and alias of $:.
        keys.insert(QByteArrayLiteral("$-l"), true); // The value of interpreter option -x and true if option -lis set. Read-only.
        keys.insert(QByteArrayLiteral("$-p"), true); // The value of interpreter option -x and true if option -pis set. Read-only.
        keys.insert(QByteArrayLiteral("$-v"), true); //

        keys.insert(QByteArrayLiteral("$_"), true); // The local variable, last string read by gets or readline in the current scope.
        keys.insert(QByteArrayLiteral("$~"), true); // The local variable, MatchData relating to the last match. Regex#match method returns the last match information.

        // $ n ($1, $2, $3...) // The string matched in the nth group of the last pattern match. Equivalent to m[n], where m is a MatchData object.
        for(int i = 1; i <= 100; i++)
            keys.insert('$' + QByteArray::number(i), true);

        keys.insert(QByteArrayLiteral("$&"), true); // The string matched in the last pattern match. Equivalent to m[0], where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$`"), true); // The string preceding the match in the last pattern match. Equivalent to m.pre_match, where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$'"), true); // The string following the match in the last pattern match. Equivalent to m.post_match, where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$+"), true); // The string corresponding to the last successfully matched group in the last pattern match.
    }
public:
    inline bool hasKey(const QByteArray & key) { return keys.contains(key); }
};

#endif // PREDEFINED_RUBY_H
