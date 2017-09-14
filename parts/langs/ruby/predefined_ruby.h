#ifndef PREDEFINED_RUBY_H
#define PREDEFINED_RUBY_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"
#include "parts/lexer/lexems.h"

//https://ruby-doc.org
//http://www.rubymagic.org/posts/ruby-and-rails-reserved-words
//https://www.tutorialspoint.com/ruby/ruby_regular_expressions.htm

class PredefinedRuby : public SingletonPtr<PredefinedRuby> {
    QHash<QByteArray, Lexem> keys;

    PredefinedRuby() {
        keys.insert(QByteArrayLiteral("#{"), lex_interpolation);
        keys.insert(QByteArrayLiteral("{"), lex_open_curly_bracket);
        keys.insert(QByteArrayLiteral("}"), lex_close_curly_bracket);

        keys.insert(QByteArrayLiteral("["), lex_open_square_bracket);
        keys.insert(QByteArrayLiteral("]"), lex_close_square_bracket);

        keys.insert(QByteArrayLiteral("("), lex_wrap_start);
        keys.insert(QByteArrayLiteral(")"), lex_wrap_end);

        keys.insert(QByteArrayLiteral("->"), lex_lambda_def);

        keys.insert(QByteArrayLiteral("."), lex_dot);
        keys.insert(QByteArrayLiteral(","), lex_comma);

        keys.insert(QByteArrayLiteral(";"), lex_end_line);
        keys.insert(QByteArrayLiteral("\r"), lex_end_line);
        keys.insert(QByteArrayLiteral("\n"), lex_end_line);
        keys.insert(QByteArrayLiteral("\v"), lex_end_line);
        keys.insert(QByteArrayLiteral("\t"), lex_blanks);
        keys.insert(QByteArrayLiteral(" "), lex_blank);


        keys.insert(QByteArrayLiteral("__ENCODING__"), lex_predefined_method_call_name); // The script encoding of the current file
        keys.insert(QByteArrayLiteral("__LINE__"), lex_predefined_method_call_name); // The line number of this keyword in the current file
        keys.insert(QByteArrayLiteral("__FILE__"), lex_predefined_method_call_name); // The path to the current file.
        keys.insert(QByteArrayLiteral("__END__"), lex_end_of_code); // Denotes the end of the regular source code section of a program file. Lines below __END__ will not be executed
        keys.insert(QByteArrayLiteral("__method__"), lex_predefined_method_call_name); // Name of current method


        keys.insert(QByteArrayLiteral("=begin"), lex_commentary_start); // Start of multiline comment
        keys.insert(QByteArrayLiteral("=end"), lex_commentary_end); // End of multiline comment

        keys.insert(QByteArrayLiteral("BEGIN"), lex_global_pre_hook); // Runs before any other code in the current file
        keys.insert(QByteArrayLiteral("END"), lex_global_post_hook); // Runs after any other code in the current file

        keys.insert(QByteArrayLiteral("alias"), lex_alias); // Creates an alias between two methods (and other things)
        keys.insert(QByteArrayLiteral("and"), lex_operator_and); // Short-circuit Boolean and with lower precedence than &&

        keys.insert(QByteArrayLiteral("begin"), lex_block_start); // Starts an exception handling block
        keys.insert(QByteArrayLiteral("break"), lex_loop_break); // Leaves a block early
        keys.insert(QByteArrayLiteral("case"), lex_case); // Starts a case expression
        keys.insert(QByteArrayLiteral("class"), lex_class_def); // Creates or opens a class
        keys.insert(QByteArrayLiteral("def"), lex_method_def); // Defines a method
        keys.insert(QByteArrayLiteral("defined?"), lex_predefined_method_call_name); // Returns a string describing its argument
        keys.insert(QByteArrayLiteral("do"), lex_block_start); // Starts a block
        keys.insert(QByteArrayLiteral("else"), lex_else); // The unhandled condition in case, if and unless expressions
        keys.insert(QByteArrayLiteral("elsif"), lex_elsif); // An alternate condition for an if expression
        keys.insert(QByteArrayLiteral("end"), lex_block_end); // The end of a syntax block. Used by classes, modules, methods, exception handling and control expressions
        keys.insert(QByteArrayLiteral("ensure"), lex_block_ensure); // Starts a section of code that is always run when an exception is raised

        keys.insert(QByteArrayLiteral("eql?"), lex_operator_comparison); // receiver and argument have both the same type and equal values
        keys.insert(QByteArrayLiteral("equal?"), lex_operator_equality); // receiver and argument have the same object id

        keys.insert(QByteArrayLiteral("extend"), lex_extend);
        keys.insert(QByteArrayLiteral("false"), lex_predefined_expression); // Boolean false
        keys.insert(QByteArrayLiteral("for"), lex_for); // A loop that is similar to using the each method
        keys.insert(QByteArrayLiteral("if"), lex_if); // Used for if and modifier if expressions
        keys.insert(QByteArrayLiteral("in"), lex_for_in); // Used to separate the iterable object and iterator variable in a for loop
        keys.insert(QByteArrayLiteral("include"), lex_include);

        keys.insert(QByteArrayLiteral("lambda"), lex_lambda_def);
        keys.insert(QByteArrayLiteral("module"), lex_module_def); // Creates or opens a module
        keys.insert(QByteArrayLiteral("next"), lex_loop_next); // Skips the rest of the block
        keys.insert(QByteArrayLiteral("new"), lex_predefined_method_call_name);
        keys.insert(QByteArrayLiteral("nil"), lex_predefined_expression); // A false value usually indicating “no value” or “unknown”
        keys.insert(QByteArrayLiteral("not"), lex_operator_not); // Inverts the following boolean expression
        keys.insert(QByteArrayLiteral("or"), lex_operator_or); // Boolean or with lower precedence than ||
        keys.insert(QByteArrayLiteral("private"), lex_visibility_scope_name);
        keys.insert(QByteArrayLiteral("proc"), lex_proc_def);
        keys.insert(QByteArrayLiteral("protected"), lex_visibility_scope_name);
        keys.insert(QByteArrayLiteral("public"), lex_visibility_scope_name);
        keys.insert(QByteArrayLiteral("raise"), lex_predefined_method_call_name);
        keys.insert(QByteArrayLiteral("redo"), lex_loop_redo); // Restarts execution in the current block
        keys.insert(QByteArrayLiteral("require"), lex_require);
        keys.insert(QByteArrayLiteral("rescue"), lex_block_rescue); // Starts an exception section of code in a begin block
        keys.insert(QByteArrayLiteral("retry"), lex_block_retry); // Retries an exception block
        keys.insert(QByteArrayLiteral("return"), lex_return); // Exits a method
        keys.insert(QByteArrayLiteral("self"), lex_self); // The object the current method is attached to
        keys.insert(QByteArrayLiteral("super"), lex_super); // Calls the current method in a superclass
        keys.insert(QByteArrayLiteral("then"), lex_then); // Indicates the end of conditional blocks in control structures
        keys.insert(QByteArrayLiteral("true"), lex_predefined_expression); // Boolean true
        keys.insert(QByteArrayLiteral("undef"), lex_undef); // Prevents a class or module from responding to a method call
        keys.insert(QByteArrayLiteral("unless"), lex_unless); // Used for unless and modifier unless expressions
        keys.insert(QByteArrayLiteral("until"), lex_until); // Creates a loop that executes until the condition is true
        keys.insert(QByteArrayLiteral("when"), lex_when); // A condition in a case expression
        keys.insert(QByteArrayLiteral("while"), lex_while); // Creates a loop that executes while the condition is true
        keys.insert(QByteArrayLiteral("yield"), lex_predefined_method_call_name); // Starts execution of the block sent to the current method


        keys.insert(QByteArrayLiteral("+"), lex_operator_addition);
        keys.insert(QByteArrayLiteral("-"), lex_operator_substraction);
        keys.insert(QByteArrayLiteral("*"), lex_operator_multiplication);
        keys.insert(QByteArrayLiteral("/"), lex_operator_division);
        keys.insert(QByteArrayLiteral("%"), lex_operator_modulus);
        keys.insert(QByteArrayLiteral("**"), lex_operator_exponentiation);

        keys.insert(QByteArrayLiteral("+="), lex_operator_addition_assigment);
        keys.insert(QByteArrayLiteral("-="), lex_operator_substraction_assigment);
        keys.insert(QByteArrayLiteral("*="), lex_operator_multiplication_assigment);
        keys.insert(QByteArrayLiteral("/="), lex_operator_division_assigment);
        keys.insert(QByteArrayLiteral("%="), lex_operator_modulus_assigment);
        keys.insert(QByteArrayLiteral("**="), lex_operator_exponentiation_assigment);

        keys.insert(QByteArrayLiteral("="), lex_operator_assigment);
        keys.insert(QByteArrayLiteral("=="), lex_operator_comparison);
        keys.insert(QByteArrayLiteral("!="), lex_operator_not_equal);
        keys.insert(QByteArrayLiteral(">"), lex_operator_great);
        keys.insert(QByteArrayLiteral("<"), lex_operator_less);
        keys.insert(QByteArrayLiteral(">="), lex_operator_great_eql);
        keys.insert(QByteArrayLiteral("<="), lex_operator_less_eql);
        keys.insert(QByteArrayLiteral("=="), lex_operator_comparison);
        keys.insert(QByteArrayLiteral("<=>"), lex_operator_sort);
        keys.insert(QByteArrayLiteral("==="), lex_operator_equality);
        keys.insert(QByteArrayLiteral(".."), lex_dot_dot);
        keys.insert(QByteArrayLiteral("..."), lex_dot_dot_dot);

        keys.insert(QByteArrayLiteral("&"), lex_operator_bit_and);
        keys.insert(QByteArrayLiteral("|"), lex_operator_bit_or);
        keys.insert(QByteArrayLiteral("^"), lex_operator_bit_exclusive_or);
        keys.insert(QByteArrayLiteral("~"), lex_operator_bit_not);
        keys.insert(QByteArrayLiteral("<<"), lex_operator_bit_left_shift);
        keys.insert(QByteArrayLiteral(">>"), lex_operator_bit_right_shift);

        keys.insert(QByteArrayLiteral("=>"), lex_rocket);
        keys.insert(QByteArrayLiteral(":"), lex_colon);

        keys.insert(QByteArrayLiteral("!"), lex_operator_not);
        keys.insert(QByteArrayLiteral("&&"), lex_operator_and);
        keys.insert(QByteArrayLiteral("||"), lex_operator_or);

        keys.insert(QByteArrayLiteral("||="), lex_operator_or_assigment);

        keys.insert(QByteArrayLiteral("::"), lex_resolution);


        keys.insert(QByteArrayLiteral("TRUE"), lex_predefined_expression); // Synonym for true
        keys.insert(QByteArrayLiteral("FALSE"), lex_predefined_expression); // Synonym for false
        keys.insert(QByteArrayLiteral("NIL"), lex_predefined_expression); // Synonym for nil
        keys.insert(QByteArrayLiteral("ARGF"), lex_predefined_expression); // An object providing access to virtual concatenation of files passed as command-line arguments or standard input if there are no command-line arguments. A synonym for $<
        keys.insert(QByteArrayLiteral("ARGV"), lex_predefined_expression); // An array containing the command-line arguments passed to the program. A synonym for $*
        keys.insert(QByteArrayLiteral("DATA"), lex_predefined_expression); // An input stream for reading the lines of code following the __END__ directive. Not defined if __END__ isn't present in code.
        keys.insert(QByteArrayLiteral("ENV"), lex_predefined_expression); // A hash-like object containing the program's environment variables. ENV can be handled as a hash
        keys.insert(QByteArrayLiteral("RUBY_PLATFORM"), lex_predefined_expression); // A string indicating the platform of the Ruby interpreter.
        keys.insert(QByteArrayLiteral("RUBY_RELEASE_DATE"), lex_predefined_expression); // A string indicating the release date of the Ruby interpreter
        keys.insert(QByteArrayLiteral("RUBY_VERSION"), lex_predefined_expression); // A string indicating the version of the Ruby interpreter
        keys.insert(QByteArrayLiteral("STDERR"), lex_predefined_expression); // Standard error output stream. Default value of $stderr
        keys.insert(QByteArrayLiteral("STDIN"), lex_predefined_expression); // Standard input stream. Default value of $stdin
        keys.insert(QByteArrayLiteral("STDOUT"), lex_predefined_expression); // Standard output stream. Default value of $stdout
        keys.insert(QByteArrayLiteral("TOPLEVEL_BINDING"), lex_predefined_expression); // A binding object at Ruby's top level.

        keys.insert(QByteArrayLiteral("$!"), lex_predefined_method_call_name); // The last exception object raised. The exception object can also be accessed using => in rescue clause.
        keys.insert(QByteArrayLiteral("$@"), lex_predefined_method_call_name); // The stack backtrace for the last exception raised. The stack backtrace information can retrieved by Exception#backtrace method of the last exception.
        keys.insert(QByteArrayLiteral("$/"), lex_predefined_method_call_name); // The input record separator (newline by default). gets, readline, etc., take their input record separator as optional argument.
        keys.insert(QByteArrayLiteral("$\\"), lex_predefined_method_call_name); // The output record separator (nil by default).
        keys.insert(QByteArrayLiteral("$,"), lex_predefined_method_call_name); // The output separator between the arguments to print and Array#join (nil by default). You can specify separator explicitly to Array#join.
        keys.insert(QByteArrayLiteral("$;"), lex_predefined_method_call_name); // The default separator for split (nil by default). You can specify separator explicitly for String#split.
        keys.insert(QByteArrayLiteral("$."), lex_predefined_method_call_name); // The number of the last line read from the current input file. Equivalent to ARGF.lineno.
        keys.insert(QByteArrayLiteral("$<"), lex_predefined_method_call_name); // Synonym for ARGF.
        keys.insert(QByteArrayLiteral("$>"), lex_predefined_method_call_name); // Synonym for $defout.
        keys.insert(QByteArrayLiteral("$0"), lex_predefined_method_call_name); // The name of the current Ruby program being executed.

        keys.insert(QByteArrayLiteral("$$"), lex_predefined_method_call_name); // The process pid of the current Ruby program being executed.
        keys.insert(QByteArrayLiteral("$?"), lex_predefined_method_call_name); // The exit status of the last process terminated.
        keys.insert(QByteArrayLiteral("$:"), lex_predefined_method_call_name); // Synonym for $LOAD_PATH.
        keys.insert(QByteArrayLiteral("$DEBUG"), lex_predefined_method_call_name); // True if the -d or --debug command-line option is specified.
        keys.insert(QByteArrayLiteral("$defout"), lex_predefined_method_call_name); // The destination output for print and printf ($stdout by default).
        keys.insert(QByteArrayLiteral("$F"), lex_predefined_method_call_name); // The variable that receives the output from split when -a is specified. This variable is set if the -a command-line option is specified along with the -p or -n option.
        keys.insert(QByteArrayLiteral("$FILENAME"), lex_predefined_method_call_name); // The name of the file currently being read from ARGF. Equivalent to ARGF.filename.
        keys.insert(QByteArrayLiteral("$LOAD_PATH"), lex_predefined_method_call_name); // An array holding the directories to be searched when loading files with the load and require methods.
        keys.insert(QByteArrayLiteral("$SAFE"), lex_predefined_method_call_name); // The security level
        //    0 → No checks are performed on externally supplied (tainted) data. (default)
        //    1 → Potentially dangerous operations using tainted data are forbidden.
        //    2 → Potentially dangerous operations on processes and files are forbidden.
        //    3 → All newly created objects are considered tainted.
        //    4 → Modification of global data is forbidden.

        keys.insert(QByteArrayLiteral("$stdin"), lex_predefined_method_call_name); // Standard input (STDIN by default).
        keys.insert(QByteArrayLiteral("$stdout"), lex_predefined_method_call_name); // Standard output (STDOUT by default).
        keys.insert(QByteArrayLiteral("$stderr"), lex_predefined_method_call_name); // Standard error (STDERR by default).
        keys.insert(QByteArrayLiteral("$VERBOSE"), lex_predefined_method_call_name); // True if the -v, -w, or --verbose command-line option is specified.

        // $- x // The value of interpreter option -x (x=0, a, d, F, i, K, l, p, v). These options are listed below
        keys.insert(QByteArrayLiteral("$-0"), lex_predefined_method_call_name); // The value of interpreter option -x and alias of $/.
        keys.insert(QByteArrayLiteral("$-a"), lex_predefined_method_call_name); // The value of interpreter option -x and true if option -a is set. Read-only.
        keys.insert(QByteArrayLiteral("$-d"), lex_predefined_method_call_name); // The value of interpreter option -x and alias of $DEBUG
        keys.insert(QByteArrayLiteral("$-F"), lex_predefined_method_call_name); // The value of interpreter option -x and alias of $;.
        keys.insert(QByteArrayLiteral("$-i"), lex_predefined_method_call_name); // The value of interpreter option -x and in in-place-edit mode, holds the extension, otherwise nil. Can enable or disable in-place-edit mode.
        keys.insert(QByteArrayLiteral("$-K"), lex_predefined_method_call_name); // The value of interpreter option -x and alias of $:.
        keys.insert(QByteArrayLiteral("$-l"), lex_predefined_method_call_name); // The value of interpreter option -x and true if option -lis set. Read-only.
        keys.insert(QByteArrayLiteral("$-p"), lex_predefined_method_call_name); // The value of interpreter option -x and true if option -pis set. Read-only.
        keys.insert(QByteArrayLiteral("$-v"), lex_predefined_method_call_name); //

        keys.insert(QByteArrayLiteral("$_"), lex_predefined_method_call_name); // The local variable, last string read by gets or readline in the current scope.
        keys.insert(QByteArrayLiteral("$~"), lex_predefined_method_call_name); // The local variable, MatchData relating to the last match. Regex#match method returns the last match information.

        // $ n ($1, $2, $3...) // The string matched in the nth group of the last pattern match. Equivalent to m[n], where m is a MatchData object.
        for(int i = 1; i < 100; i++)
            keys.insert('$' + QByteArray::number(i), lex_predefined_method_call_name);

        keys.insert(QByteArrayLiteral("$&"), lex_predefined_method_call_name); // The string matched in the last pattern match. Equivalent to m[0], where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$`"), lex_predefined_method_call_name); // The string preceding the match in the last pattern match. Equivalent to m.pre_match, where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$'"), lex_predefined_method_call_name); // The string following the match in the last pattern match. Equivalent to m.post_match, where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$+"), lex_predefined_method_call_name); // The string corresponding to the last successfully matched group in the last pattern match.



//        keys.insert(QByteArrayLiteral("Class"), lex_operator_addition);



        //        keys.insert(QByteArrayLiteral("attr"), true);
        //        keys.insert(QByteArrayLiteral("attr_accessor"), true);
        //        keys.insert(QByteArrayLiteral("attr_reader"), true);
        //        keys.insert(QByteArrayLiteral("attr_writer"), true);
    }

    friend class SingletonPtr<PredefinedRuby>;
public:
    inline bool hasKey(const QByteArray & key) { return keys.contains(key); }
    inline Lexem lexem(const QByteArray & key) { return keys.value(key, lex_undefined); }
};

#endif // PREDEFINED_RUBY_H
