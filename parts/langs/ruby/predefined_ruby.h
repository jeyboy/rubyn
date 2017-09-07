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
        keys.insert(QByteArrayLiteral("#{"), lex_block_start);
        keys.insert(QByteArrayLiteral("{"), lex_block_start);
        keys.insert(QByteArrayLiteral("}"), lex_block_end);

        keys.insert(QByteArrayLiteral("["), lex_array_start);
        keys.insert(QByteArrayLiteral("]"), lex_array_end);

        keys.insert(QByteArrayLiteral("("), lex_wrap_start);
        keys.insert(QByteArrayLiteral(")"), lex_wrap_end);

        keys.insert(QByteArrayLiteral("->"), lex_def_lambda);

        keys.insert(QByteArrayLiteral("."), lex_access);
        keys.insert(QByteArrayLiteral(","), lex_comma);
        keys.insert(QByteArrayLiteral("="), lex_binary_operator /*lex_var_chain_end*/);

        keys.insert(QByteArrayLiteral(";"), lex_end_line);
        keys.insert(QByteArrayLiteral("\r"), lex_end_line);
        keys.insert(QByteArrayLiteral("\n"), lex_end_line);
        keys.insert(QByteArrayLiteral("\v"), lex_end_line);
        keys.insert(QByteArrayLiteral("\t"), lex_ignore);
        keys.insert(QByteArrayLiteral(" "), lex_ignore);


        keys.insert(QByteArrayLiteral("__ENCODING__"), lex_const); // The script encoding of the current file
        keys.insert(QByteArrayLiteral("__LINE__"), lex_const); // The line number of this keyword in the current file
        keys.insert(QByteArrayLiteral("__FILE__"), lex_const); // The path to the current file.
        keys.insert(QByteArrayLiteral("__END__"), lex_none); // Denotes the end of the regular source code section of a program file. Lines below __END__ will not be executed
        keys.insert(QByteArrayLiteral("__method__"), lex_const); // Name of current method


        keys.insert(QByteArrayLiteral("=begin"), lex_multiline_commentary_start); // Start of multiline comment
        keys.insert(QByteArrayLiteral("=end"), lex_multiline_commentary_end); // End of multiline comment

        keys.insert(QByteArrayLiteral("BEGIN"), lex_block_requred); // Runs before any other code in the current file
        keys.insert(QByteArrayLiteral("END"), lex_block_requred); // Runs after any other code in the current file

        keys.insert(QByteArrayLiteral("alias"), lex_method_with_params); // Creates an alias between two methods (and other things)
        keys.insert(QByteArrayLiteral("and"), lex_binary_operator); // Short-circuit Boolean and with lower precedence than &&

        keys.insert(QByteArrayLiteral("begin"), lex_block_start); // Starts an exception handling block
        keys.insert(QByteArrayLiteral("break"), lex_method); // Leaves a block early
        keys.insert(QByteArrayLiteral("case"), lex_method_with_params); // Starts a case expression
        keys.insert(QByteArrayLiteral("class"), lex_def_class); // Creates or opens a class
        keys.insert(QByteArrayLiteral("def"), les_def_method); // Defines a method
        keys.insert(QByteArrayLiteral("defined?"), lex_method_with_params); // Returns a string describing its argument
        keys.insert(QByteArrayLiteral("do"), lex_block_start); // Starts a block
        keys.insert(QByteArrayLiteral("else"), lex_chain_level); // The unhandled condition in case, if and unless expressions
        keys.insert(QByteArrayLiteral("elsif"), lex_conditional_chain_level); // An alternate condition for an if expression
        keys.insert(QByteArrayLiteral("end"), lex_block_end); // The end of a syntax block. Used by classes, modules, methods, exception handling and control expressions
        keys.insert(QByteArrayLiteral("ensure"), lex_block_start); // Starts a section of code that is always run when an exception is raised
        keys.insert(QByteArrayLiteral("extend"), lex_method_with_params);
        keys.insert(QByteArrayLiteral("false"), lex_var); // Boolean false
        keys.insert(QByteArrayLiteral("for"), lex_method_with_params); // A loop that is similar to using the each method
        keys.insert(QByteArrayLiteral("if"), lex_chain_poly_start); // Used for if and modifier if expressions
        keys.insert(QByteArrayLiteral("in"), lex_method_with_params); // Used to separate the iterable object and iterator variable in a for loop
        keys.insert(QByteArrayLiteral("include"), lex_method_with_params);
        keys.insert(QByteArrayLiteral("lambda"), lex_param_block_requred);
        keys.insert(QByteArrayLiteral("module"), lex_def_module); // Creates or opens a module
        keys.insert(QByteArrayLiteral("next"), lex_method); // Skips the rest of the block
        keys.insert(QByteArrayLiteral("new"), lex_method);
        keys.insert(QByteArrayLiteral("nil"), lex_var); // A false value usually indicating “no value” or “unknown”
        keys.insert(QByteArrayLiteral("not"), lex_unary_operator); // Inverts the following boolean expression
        keys.insert(QByteArrayLiteral("or"), lex_binary_operator); // Boolean or with lower precedence than ||
        keys.insert(QByteArrayLiteral("private"), lex_scope_visibility);
        keys.insert(QByteArrayLiteral("proc"), lex_param_block_requred);
        keys.insert(QByteArrayLiteral("protected"), lex_scope_visibility);
        keys.insert(QByteArrayLiteral("public"), lex_scope_visibility);
        keys.insert(QByteArrayLiteral("raise"), lex_method);
        keys.insert(QByteArrayLiteral("redo"), lex_method); // Restarts execution in the current block
        keys.insert(QByteArrayLiteral("require"), lex_method_with_params);
        keys.insert(QByteArrayLiteral("rescue"), lex_method); // Starts an exception section of code in a begin block
        keys.insert(QByteArrayLiteral("retry"), lex_method); // Retries an exception block
        keys.insert(QByteArrayLiteral("return"), lex_method); // Exits a method
        keys.insert(QByteArrayLiteral("self"), lex_method); // The object the current method is attached to
        keys.insert(QByteArrayLiteral("super"), lex_method); // Calls the current method in a superclass
        keys.insert(QByteArrayLiteral("then"), lex_ignore); // Indicates the end of conditional blocks in control structures
        keys.insert(QByteArrayLiteral("true"), lex_var); // Boolean true
        keys.insert(QByteArrayLiteral("undef"), lex_method_with_params); // Prevents a class or module from responding to a method call
        keys.insert(QByteArrayLiteral("unless"), lex_chain_unary_start); // Used for unless and modifier unless expressions
        keys.insert(QByteArrayLiteral("until"), lex_param_block_start); // Creates a loop that executes until the condition is true
        keys.insert(QByteArrayLiteral("when"), lex_method_with_params); // A condition in a case expression
        keys.insert(QByteArrayLiteral("while"), lex_param_block_start); // Creates a loop that executes while the condition is true
        keys.insert(QByteArrayLiteral("yield"), lex_method); // Starts execution of the block sent to the current method


        keys.insert(QByteArrayLiteral("+"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("-"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("*"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("/"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("%"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("**"), lex_binary_operator);

        keys.insert(QByteArrayLiteral("+="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("-="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("*="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("/="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("%="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("**="), lex_binary_operator);

        keys.insert(QByteArrayLiteral("=="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("!="), lex_binary_operator);
        keys.insert(QByteArrayLiteral(">"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("<"), lex_binary_operator);
        keys.insert(QByteArrayLiteral(">="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("<="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("=="), lex_binary_operator);
        keys.insert(QByteArrayLiteral("<=>"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("==="), lex_binary_operator);
        keys.insert(QByteArrayLiteral(".."), lex_binary_operator);
        keys.insert(QByteArrayLiteral("..."), lex_binary_operator);

        keys.insert(QByteArrayLiteral("&"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("|"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("^"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("~"), lex_unary_operator);
        keys.insert(QByteArrayLiteral("<<"), lex_binary_operator);
        keys.insert(QByteArrayLiteral(">>"), lex_binary_operator);

        keys.insert(QByteArrayLiteral("=>"), lex_binary_operator);
        keys.insert(QByteArrayLiteral(":"), lex_binary_operator);

        keys.insert(QByteArrayLiteral("!"), lex_unary_operator);
        keys.insert(QByteArrayLiteral("&&"), lex_binary_operator);
        keys.insert(QByteArrayLiteral("||"), lex_binary_operator);

        keys.insert(QByteArrayLiteral("||="), lex_binary_operator);

        keys.insert(QByteArrayLiteral("::"), lex_class_or_module_required);


        keys.insert(QByteArrayLiteral("TRUE"), lex_const); // Synonym for true
        keys.insert(QByteArrayLiteral("FALSE"), lex_const); // Synonym for false
        keys.insert(QByteArrayLiteral("NIL"), lex_const); // Synonym for nil
        keys.insert(QByteArrayLiteral("ARGF"), lex_const); // An object providing access to virtual concatenation of files passed as command-line arguments or standard input if there are no command-line arguments. A synonym for $<
        keys.insert(QByteArrayLiteral("ARGV"), lex_const); // An array containing the command-line arguments passed to the program. A synonym for $*
        keys.insert(QByteArrayLiteral("DATA"), lex_const); // An input stream for reading the lines of code following the __END__ directive. Not defined if __END__ isn't present in code.
        keys.insert(QByteArrayLiteral("ENV"), lex_const); // A hash-like object containing the program's environment variables. ENV can be handled as a hash
        keys.insert(QByteArrayLiteral("RUBY_PLATFORM"), lex_const); // A string indicating the platform of the Ruby interpreter.
        keys.insert(QByteArrayLiteral("RUBY_RELEASE_DATE"), lex_const); // A string indicating the release date of the Ruby interpreter
        keys.insert(QByteArrayLiteral("RUBY_VERSION"), lex_const); // A string indicating the version of the Ruby interpreter
        keys.insert(QByteArrayLiteral("STDERR"), lex_const); // Standard error output stream. Default value of $stderr
        keys.insert(QByteArrayLiteral("STDIN"), lex_const); // Standard input stream. Default value of $stdin
        keys.insert(QByteArrayLiteral("STDOUT"), lex_const); // Standard output stream. Default value of $stdout
        keys.insert(QByteArrayLiteral("TOPLEVEL_BINDING"), lex_const); // A binding object at Ruby's top level.

        keys.insert(QByteArrayLiteral("$!"), lex_var); // The last exception object raised. The exception object can also be accessed using => in rescue clause.
        keys.insert(QByteArrayLiteral("$@"), lex_var); // The stack backtrace for the last exception raised. The stack backtrace information can retrieved by Exception#backtrace method of the last exception.
        keys.insert(QByteArrayLiteral("$/"), lex_var); // The input record separator (newline by default). gets, readline, etc., take their input record separator as optional argument.
        keys.insert(QByteArrayLiteral("$\\"), lex_var); // The output record separator (nil by default).
        keys.insert(QByteArrayLiteral("$,"), lex_var); // The output separator between the arguments to print and Array#join (nil by default). You can specify separator explicitly to Array#join.
        keys.insert(QByteArrayLiteral("$;"), lex_var); // The default separator for split (nil by default). You can specify separator explicitly for String#split.
        keys.insert(QByteArrayLiteral("$."), lex_var); // The number of the last line read from the current input file. Equivalent to ARGF.lineno.
        keys.insert(QByteArrayLiteral("$<"), lex_var); // Synonym for ARGF.
        keys.insert(QByteArrayLiteral("$>"), lex_var); // Synonym for $defout.
        keys.insert(QByteArrayLiteral("$0"), lex_var); // The name of the current Ruby program being executed.

        keys.insert(QByteArrayLiteral("$$"), lex_var); // The process pid of the current Ruby program being executed.
        keys.insert(QByteArrayLiteral("$?"), lex_var); // The exit status of the last process terminated.
        keys.insert(QByteArrayLiteral("$:"), lex_var); // Synonym for $LOAD_PATH.
        keys.insert(QByteArrayLiteral("$DEBUG"), lex_var); // True if the -d or --debug command-line option is specified.
        keys.insert(QByteArrayLiteral("$defout"), lex_var); // The destination output for print and printf ($stdout by default).
        keys.insert(QByteArrayLiteral("$F"), lex_var); // The variable that receives the output from split when -a is specified. This variable is set if the -a command-line option is specified along with the -p or -n option.
        keys.insert(QByteArrayLiteral("$FILENAME"), lex_var); // The name of the file currently being read from ARGF. Equivalent to ARGF.filename.
        keys.insert(QByteArrayLiteral("$LOAD_PATH"), lex_var); // An array holding the directories to be searched when loading files with the load and require methods.
        keys.insert(QByteArrayLiteral("$SAFE"), lex_var); // The security level
        //    0 → No checks are performed on externally supplied (tainted) data. (default)
        //    1 → Potentially dangerous operations using tainted data are forbidden.
        //    2 → Potentially dangerous operations on processes and files are forbidden.
        //    3 → All newly created objects are considered tainted.
        //    4 → Modification of global data is forbidden.

        keys.insert(QByteArrayLiteral("$stdin"), lex_var); // Standard input (STDIN by default).
        keys.insert(QByteArrayLiteral("$stdout"), lex_var); // Standard output (STDOUT by default).
        keys.insert(QByteArrayLiteral("$stderr"), lex_var); // Standard error (STDERR by default).
        keys.insert(QByteArrayLiteral("$VERBOSE"), lex_var); // True if the -v, -w, or --verbose command-line option is specified.

        // $- x // The value of interpreter option -x (x=0, a, d, F, i, K, l, p, v). These options are listed below
        keys.insert(QByteArrayLiteral("$-0"), lex_var); // The value of interpreter option -x and alias of $/.
        keys.insert(QByteArrayLiteral("$-a"), lex_var); // The value of interpreter option -x and true if option -a is set. Read-only.
        keys.insert(QByteArrayLiteral("$-d"), lex_var); // The value of interpreter option -x and alias of $DEBUG
        keys.insert(QByteArrayLiteral("$-F"), lex_var); // The value of interpreter option -x and alias of $;.
        keys.insert(QByteArrayLiteral("$-i"), lex_var); // The value of interpreter option -x and in in-place-edit mode, holds the extension, otherwise nil. Can enable or disable in-place-edit mode.
        keys.insert(QByteArrayLiteral("$-K"), lex_var); // The value of interpreter option -x and alias of $:.
        keys.insert(QByteArrayLiteral("$-l"), lex_var); // The value of interpreter option -x and true if option -lis set. Read-only.
        keys.insert(QByteArrayLiteral("$-p"), lex_var); // The value of interpreter option -x and true if option -pis set. Read-only.
        keys.insert(QByteArrayLiteral("$-v"), lex_var); //

        keys.insert(QByteArrayLiteral("$_"), lex_var); // The local variable, last string read by gets or readline in the current scope.
        keys.insert(QByteArrayLiteral("$~"), lex_var); // The local variable, MatchData relating to the last match. Regex#match method returns the last match information.

        // $ n ($1, $2, $3...) // The string matched in the nth group of the last pattern match. Equivalent to m[n], where m is a MatchData object.
        for(int i = 1; i < 100; i++)
            keys.insert('$' + QByteArray::number(i), lex_var);

        keys.insert(QByteArrayLiteral("$&"), lex_var); // The string matched in the last pattern match. Equivalent to m[0], where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$`"), lex_var); // The string preceding the match in the last pattern match. Equivalent to m.pre_match, where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$'"), lex_var); // The string following the match in the last pattern match. Equivalent to m.post_match, where m is a MatchData object.
        keys.insert(QByteArrayLiteral("$+"), lex_var); // The string corresponding to the last successfully matched group in the last pattern match.

        //        keys.insert(QByteArrayLiteral("attr"), true);
        //        keys.insert(QByteArrayLiteral("attr_accessor"), true);
        //        keys.insert(QByteArrayLiteral("attr_reader"), true);
        //        keys.insert(QByteArrayLiteral("attr_writer"), true);
    }


//    PredefinedRuby() {
//        keys.insert(QByteArrayLiteral(";"), lex_end_line);
//        keys.insert(QByteArrayLiteral("\r"), lex_end_line);
//        keys.insert(QByteArrayLiteral("\n"), lex_end_line);
//        keys.insert(QByteArrayLiteral("\v"), lex_end_line);
//        keys.insert(QByteArrayLiteral("\t"), lex_ignore);
//        keys.insert(QByteArrayLiteral(" "), lex_ignore);


//        keys.insert(QByteArrayLiteral("#{"), lex_block);
//        keys.insert(QByteArrayLiteral("{"), lex_block);
//        keys.insert(QByteArrayLiteral("}"), lex_block_end);

//        keys.insert(QByteArrayLiteral("["), lex_array);
//        keys.insert(QByteArrayLiteral("]"), lex_array_end);

//        keys.insert(QByteArrayLiteral("("), lex_wrap);
//        keys.insert(QByteArrayLiteral(")"), lex_wrap_end);

//        keys.insert(QByteArrayLiteral("->"), lex_def_lambda);

//        keys.insert(QByteArrayLiteral("."), lex_access);
//        keys.insert(QByteArrayLiteral(","), lex_comma);
//        keys.insert(QByteArrayLiteral("="), lex_binary_operator);


//        keys.insert(QByteArrayLiteral("__ENCODING__"), lex_const); // The script encoding of the current file
//        keys.insert(QByteArrayLiteral("__LINE__"), lex_const); // The line number of this keyword in the current file
//        keys.insert(QByteArrayLiteral("__FILE__"), lex_const); // The path to the current file.
//        keys.insert(QByteArrayLiteral("__END__"), lex_const); // Denotes the end of the regular source code section of a program file. Lines below __END__ will not be executed
//        keys.insert(QByteArrayLiteral("__method__"), lex_const); // Name of current method


//        keys.insert(QByteArrayLiteral("=begin"), lex_multiline_commentary_start); // Start of multiline comment
//        keys.insert(QByteArrayLiteral("=end"), lex_multiline_commentary_end); // End of multiline comment

//        keys.insert(QByteArrayLiteral("BEGIN"), lex_key); // Runs before any other code in the current file
//        keys.insert(QByteArrayLiteral("END"), lex_key); // Runs after any other code in the current file

//        keys.insert(QByteArrayLiteral("alias"), lex_method); // Creates an alias between two methods (and other things)
//        keys.insert(QByteArrayLiteral("and"), lex_binary_operator); // Short-circuit Boolean and with lower precedence than &&

//        keys.insert(QByteArrayLiteral("begin"), LEX(lex_block, lex_key)); // Starts an exception handling block
//        keys.insert(QByteArrayLiteral("break"), lex_key); // Leaves a block early
//        keys.insert(QByteArrayLiteral("case"), lex_key); // Starts a case expression
//        keys.insert(QByteArrayLiteral("class"), lex_def_class); // Creates or opens a class
//        keys.insert(QByteArrayLiteral("def"), lex_def_method); // Defines a method
//        keys.insert(QByteArrayLiteral("defined?"), lex_method); // Returns a string describing its argument
//        keys.insert(QByteArrayLiteral("do"), lex_block); // Starts a block
//        keys.insert(QByteArrayLiteral("else"), lex_branch_last_level); // The unhandled condition in case, if and unless expressions
//        keys.insert(QByteArrayLiteral("elsif"), lex_poly_branch_level); // An alternate condition for an if expression
//        keys.insert(QByteArrayLiteral("end"), lex_block_end); // The end of a syntax block. Used by classes, modules, methods, exception handling and control expressions
//        keys.insert(QByteArrayLiteral("ensure"), LEX(lex_key, lex_block)); // Starts a section of code that is always run when an exception is raised
//        keys.insert(QByteArrayLiteral("extend"), lex_extend);
//        keys.insert(QByteArrayLiteral("false"), lex_expression); // Boolean false
//        keys.insert(QByteArrayLiteral("for"), lex_key); // A loop that is similar to using the each method
//        keys.insert(QByteArrayLiteral("if"), lex_poly_branch); // Used for if and modifier if expressions
//        keys.insert(QByteArrayLiteral("in"), lex_key); // Used to separate the iterable object and iterator variable in a for loop
//        keys.insert(QByteArrayLiteral("include"), lex_include);
//        keys.insert(QByteArrayLiteral("lambda"), lex_def_lambda);
//        keys.insert(QByteArrayLiteral("module"), lex_def_module); // Creates or opens a module
//        keys.insert(QByteArrayLiteral("next"), lex_key); // Skips the rest of the block
//        keys.insert(QByteArrayLiteral("new"), lex_key);
//        keys.insert(QByteArrayLiteral("nil"), lex_expression); // A false value usually indicating “no value” or “unknown”
//        keys.insert(QByteArrayLiteral("not"), lex_unary_operator); // Inverts the following boolean expression
//        keys.insert(QByteArrayLiteral("or"), lex_binary_operator); // Boolean or with lower precedence than ||
//        keys.insert(QByteArrayLiteral("private"), lex_scope);
//        keys.insert(QByteArrayLiteral("proc"), lex_def_proc);
//        keys.insert(QByteArrayLiteral("protected"), lex_scope);
//        keys.insert(QByteArrayLiteral("public"), lex_scope);
//        keys.insert(QByteArrayLiteral("raise"), lex_key);
//        keys.insert(QByteArrayLiteral("redo"), lex_key); // Restarts execution in the current block
//        keys.insert(QByteArrayLiteral("require"), lex_require);
//        keys.insert(QByteArrayLiteral("rescue"), lex_key); // Starts an exception section of code in a begin block
//        keys.insert(QByteArrayLiteral("retry"), lex_key); // Retries an exception block
//        keys.insert(QByteArrayLiteral("return"), lex_key); // Exits a method
//        keys.insert(QByteArrayLiteral("self"), lex_expression); // The object the current method is attached to
//        keys.insert(QByteArrayLiteral("super"), lex_expression); // Calls the current method in a superclass
//        keys.insert(QByteArrayLiteral("then"), lex_ignore); // Indicates the end of conditional blocks in control structures
//        keys.insert(QByteArrayLiteral("true"), lex_expression); // Boolean true
//        keys.insert(QByteArrayLiteral("undef"), lex_key); // Prevents a class or module from responding to a method call
//        keys.insert(QByteArrayLiteral("unless"), lex_unary_branch); // Used for unless and modifier unless expressions
//        keys.insert(QByteArrayLiteral("until"), lex_key); // Creates a loop that executes until the condition is true
//        keys.insert(QByteArrayLiteral("when"), lex_key); // A condition in a case expression
//        keys.insert(QByteArrayLiteral("while"), lex_key); // Creates a loop that executes while the condition is true
//        keys.insert(QByteArrayLiteral("yield"), lex_expression); // Starts execution of the block sent to the current method


//        keys.insert(QByteArrayLiteral("+"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("-"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("*"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("/"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("%"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("**"), lex_binary_operator);

//        keys.insert(QByteArrayLiteral("+="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("-="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("*="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("/="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("%="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("**="), lex_binary_operator);

//        keys.insert(QByteArrayLiteral("=="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("!="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral(">"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("<"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral(">="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("<="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("=="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("<=>"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("==="), lex_binary_operator);
//        keys.insert(QByteArrayLiteral(".."), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("..."), lex_binary_operator);

//        keys.insert(QByteArrayLiteral("&"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("|"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("^"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("~"), lex_unary_operator);
//        keys.insert(QByteArrayLiteral("<<"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral(">>"), lex_binary_operator);

//        keys.insert(QByteArrayLiteral("=>"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral(":"), lex_binary_operator);

//        keys.insert(QByteArrayLiteral("!"), lex_unary_operator);
//        keys.insert(QByteArrayLiteral("&&"), lex_binary_operator);
//        keys.insert(QByteArrayLiteral("||"), lex_binary_operator);

//        keys.insert(QByteArrayLiteral("||="), lex_binary_operator);

//        keys.insert(QByteArrayLiteral("::"), lex_resolution);


//        keys.insert(QByteArrayLiteral("TRUE"), lex_const); // Synonym for true
//        keys.insert(QByteArrayLiteral("FALSE"), lex_const); // Synonym for false
//        keys.insert(QByteArrayLiteral("NIL"), lex_const); // Synonym for nil
//        keys.insert(QByteArrayLiteral("ARGF"), lex_const); // An object providing access to virtual concatenation of files passed as command-line arguments or standard input if there are no command-line arguments. A synonym for $<
//        keys.insert(QByteArrayLiteral("ARGV"), lex_const); // An array containing the command-line arguments passed to the program. A synonym for $*
//        keys.insert(QByteArrayLiteral("DATA"), lex_const); // An input stream for reading the lines of code following the __END__ directive. Not defined if __END__ isn't present in code.
//        keys.insert(QByteArrayLiteral("ENV"), lex_const); // A hash-like object containing the program's environment variables. ENV can be handled as a hash
//        keys.insert(QByteArrayLiteral("RUBY_PLATFORM"), lex_const); // A string indicating the platform of the Ruby interpreter.
//        keys.insert(QByteArrayLiteral("RUBY_RELEASE_DATE"), lex_const); // A string indicating the release date of the Ruby interpreter
//        keys.insert(QByteArrayLiteral("RUBY_VERSION"), lex_const); // A string indicating the version of the Ruby interpreter
//        keys.insert(QByteArrayLiteral("STDERR"), lex_const); // Standard error output stream. Default value of $stderr
//        keys.insert(QByteArrayLiteral("STDIN"), lex_const); // Standard input stream. Default value of $stdin
//        keys.insert(QByteArrayLiteral("STDOUT"), lex_const); // Standard output stream. Default value of $stdout
//        keys.insert(QByteArrayLiteral("TOPLEVEL_BINDING"), lex_const); // A binding object at Ruby's top level.

//        keys.insert(QByteArrayLiteral("$!"), lex_expression); // The last exception object raised. The exception object can also be accessed using => in rescue clause.
//        keys.insert(QByteArrayLiteral("$@"), lex_expression); // The stack backtrace for the last exception raised. The stack backtrace information can retrieved by Exception#backtrace method of the last exception.
//        keys.insert(QByteArrayLiteral("$/"), lex_expression); // The input record separator (newline by default). gets, readline, etc., take their input record separator as optional argument.
//        keys.insert(QByteArrayLiteral("$\\"), lex_expression); // The output record separator (nil by default).
//        keys.insert(QByteArrayLiteral("$,"), lex_expression); // The output separator between the arguments to print and Array#join (nil by default). You can specify separator explicitly to Array#join.
//        keys.insert(QByteArrayLiteral("$;"), lex_expression); // The default separator for split (nil by default). You can specify separator explicitly for String#split.
//        keys.insert(QByteArrayLiteral("$."), lex_expression); // The number of the last line read from the current input file. Equivalent to ARGF.lineno.
//        keys.insert(QByteArrayLiteral("$<"), lex_expression); // Synonym for ARGF.
//        keys.insert(QByteArrayLiteral("$>"), lex_expression); // Synonym for $defout.
//        keys.insert(QByteArrayLiteral("$0"), lex_expression); // The name of the current Ruby program being executed.

//        keys.insert(QByteArrayLiteral("$$"), lex_expression); // The process pid of the current Ruby program being executed.
//        keys.insert(QByteArrayLiteral("$?"), lex_expression); // The exit status of the last process terminated.
//        keys.insert(QByteArrayLiteral("$:"), lex_expression); // Synonym for $LOAD_PATH.
//        keys.insert(QByteArrayLiteral("$DEBUG"), lex_expression); // True if the -d or --debug command-line option is specified.
//        keys.insert(QByteArrayLiteral("$defout"), lex_expression); // The destination output for print and printf ($stdout by default).
//        keys.insert(QByteArrayLiteral("$F"), lex_expression); // The variable that receives the output from split when -a is specified. This variable is set if the -a command-line option is specified along with the -p or -n option.
//        keys.insert(QByteArrayLiteral("$FILENAME"), lex_expression); // The name of the file currently being read from ARGF. Equivalent to ARGF.filename.
//        keys.insert(QByteArrayLiteral("$LOAD_PATH"), lex_expression); // An array holding the directories to be searched when loading files with the load and require methods.
//        keys.insert(QByteArrayLiteral("$SAFE"), lex_expression); // The security level
//        //    0 → No checks are performed on externally supplied (tainted) data. (default)
//        //    1 → Potentially dangerous operations using tainted data are forbidden.
//        //    2 → Potentially dangerous operations on processes and files are forbidden.
//        //    3 → All newly created objects are considered tainted.
//        //    4 → Modification of global data is forbidden.

//        keys.insert(QByteArrayLiteral("$stdin"), lex_expression); // Standard input (STDIN by default).
//        keys.insert(QByteArrayLiteral("$stdout"), lex_expression); // Standard output (STDOUT by default).
//        keys.insert(QByteArrayLiteral("$stderr"), lex_expression); // Standard error (STDERR by default).
//        keys.insert(QByteArrayLiteral("$VERBOSE"), lex_expression); // True if the -v, -w, or --verbose command-line option is specified.

//        // $- x // The value of interpreter option -x (x=0, a, d, F, i, K, l, p, v). These options are listed below
//        keys.insert(QByteArrayLiteral("$-0"), lex_expression); // The value of interpreter option -x and alias of $/.
//        keys.insert(QByteArrayLiteral("$-a"), lex_expression); // The value of interpreter option -x and true if option -a is set. Read-only.
//        keys.insert(QByteArrayLiteral("$-d"), lex_expression); // The value of interpreter option -x and alias of $DEBUG
//        keys.insert(QByteArrayLiteral("$-F"), lex_expression); // The value of interpreter option -x and alias of $;.
//        keys.insert(QByteArrayLiteral("$-i"), lex_expression); // The value of interpreter option -x and in in-place-edit mode, holds the extension, otherwise nil. Can enable or disable in-place-edit mode.
//        keys.insert(QByteArrayLiteral("$-K"), lex_expression); // The value of interpreter option -x and alias of $:.
//        keys.insert(QByteArrayLiteral("$-l"), lex_expression); // The value of interpreter option -x and true if option -lis set. Read-only.
//        keys.insert(QByteArrayLiteral("$-p"), lex_expression); // The value of interpreter option -x and true if option -pis set. Read-only.
//        keys.insert(QByteArrayLiteral("$-v"), lex_expression); //

//        keys.insert(QByteArrayLiteral("$_"), lex_expression); // The local variable, last string read by gets or readline in the current scope.
//        keys.insert(QByteArrayLiteral("$~"), lex_expression); // The local variable, MatchData relating to the last match. Regex#match method returns the last match information.

//        // $ n ($1, $2, $3...) // The string matched in the nth group of the last pattern match. Equivalent to m[n], where m is a MatchData object.
//        for(int i = 1; i < 100; i++)
//            keys.insert('$' + QByteArray::number(i), lex_expression);

//        keys.insert(QByteArrayLiteral("$&"), lex_expression); // The string matched in the last pattern match. Equivalent to m[0], where m is a MatchData object.
//        keys.insert(QByteArrayLiteral("$`"), lex_expression); // The string preceding the match in the last pattern match. Equivalent to m.pre_match, where m is a MatchData object.
//        keys.insert(QByteArrayLiteral("$'"), lex_expression); // The string following the match in the last pattern match. Equivalent to m.post_match, where m is a MatchData object.
//        keys.insert(QByteArrayLiteral("$+"), lex_expression); // The string corresponding to the last successfully matched group in the last pattern match.

//        //        keys.insert(QByteArrayLiteral("attr"), true);
//        //        keys.insert(QByteArrayLiteral("attr_accessor"), true);
//        //        keys.insert(QByteArrayLiteral("attr_reader"), true);
//        //        keys.insert(QByteArrayLiteral("attr_writer"), true);
//    }

    friend class SingletonPtr<PredefinedRuby>;
public:
    inline bool hasKey(const QByteArray & key) { return keys.contains(key); }
    inline Lexem lexem(const QByteArray & key) { return keys.value(key, lex_undefined); }
};

#endif // PREDEFINED_RUBY_H
